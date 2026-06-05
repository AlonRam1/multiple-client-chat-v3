#include <iostream>
#include <memory>
#include <string>
#include <mutex>
#include <vector>
#include <algorithm>

#include <grpcpp/grpcpp.h>
#include  "chat.grpc.pb.h"
#include "client-manager.h"
#include "server.h"


grpc::Status ServerChatService::SendUserMessage(grpc::ServerContext* context, grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream)
{
	//take username from metadata
	auto it = context->client_metadata().find("username");

	std::string username;

	if (it != context->client_metadata().end())
	{
    		username = std::string(it->second.data(), it->second.size());
	}
	//notify new user login and add to client manager.
	std::cout << username << " connected." << std::endl;
	client_manager.Add(username, stream);
	//enter message receive loop
	Chat::UserMessage msg;
	while(stream->Read(&msg))
	{
		client_manager.Broadcast(msg);	
	}
	//remove user from clients vector and display disconnect message
	std::cout << username << " disconnected." << std::endl;
	client_manager.Remove(username);
	return grpc::Status::OK;
}

grpc::Status ServerChatService::SendUserList(grpc::ServerContext* context, const Chat::UserListRequest* request, Chat::UserList* response)
{
	bool flag = true;
	for(auto& client_session : client_manager.GetClientVector())
	{
		flag = true;
		for(auto& username : request->excluded_users())
		{
			if(username == client_session->GetUsername())
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{
			response->add_usernames(client_session->GetUsername());
		}
	}
	return grpc::Status::OK;
}


int main() {

	std::string address("0.0.0.0:50051");

	ServerChatService service;

    	grpc::ServerBuilder builder;

    	builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    	builder.RegisterService(&service);

    	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    	std::cout << "Server running on " << address << std::endl;

    	server->Wait();

    	return 0;
}


