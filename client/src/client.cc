#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

#include "client.h"

#include <grpcpp/grpcpp.h>
#include "chat.grpc.pb.h"





ClientChatService::ClientChatService(std::string username)
{
	this->username = username;

	auto channel = grpc::CreateChannel("localhost:50051",grpc::InsecureChannelCredentials());

	stub = Chat::ChatService::NewStub(channel);
}
void ClientChatService::ReadLoop(grpc::ClientReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream)
{
	Chat::UserMessage msg;
	while (stream->Read(&msg))
	{
		std::cout << msg.user() << ": " << msg.text() <<std::endl;	
	}
}

void ClientChatService::Write(Chat::UserMessage msg, grpc::ClientReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream)
{
	std::lock_guard<std::mutex> lock(client_mutex);
	if (!stream->Write(msg)) 
	{
	    std::cout << "Write failed\n";
	}
}

void ClientChatService::WriteLoop(grpc::ClientReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream)

{
	while(true)
	{
		std::string str;
		std::getline(std::cin, str);
		Chat::UserMessage msg;
		msg.set_text(str);
		msg.set_user(username);
		Write(msg, stream);
	}
}
void ClientChatService::Run()
{
	//add user metadata that will be sent along with the stream
	grpc::ClientContext stream_context;
	stream_context.AddMetadata("username", username);
	//open bi-directional stream
	auto stream = stub->SendUserMessage(&stream_context);
	//get users list to display for user
	Chat::UserListRequest user_list_request;
	user_list_request.add_excluded_users(username);
	Chat::UserList user_list;
	grpc::ClientContext list_context;
	stub->SendUserList(&list_context, user_list_request, &user_list);
	//display connect message
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "CONNECTED AS USER " << username << std::endl;
	std::cout << "on chat with: ";
	for(std::string user : user_list.usernames())
	{
		std::cout << user << " ";
	}
	std::cout << "\n-----------------------------------------------------------" << std::endl;

	//start read-write loop
	std::thread reader(&ClientChatService::ReadLoop, this, stream.get());
	std::thread writer(&ClientChatService::WriteLoop, this, stream.get());
	reader.join();
	writer.join();
	//disconnect from server
	std::cout << "Disconnected from server." << std::endl;
}


int main(int argc, char* argv[])
{
	//give client name
	std::string username;
	if(argc < 2)
	{
		std::cout << "Username: ";
		std::getline(std::cin, username);
	}
	else
		{
		username = argv[1];
	}
	//connect to chat and start read-write loop
	ClientChatService service = ClientChatService(username);
	service.Run();

	return 0;
}
