#include <iostream>
#include <memory>
#include <thread>

#include <grpcpp/grpcpp.h>
#include "chat.grpc.pb.h"

using std::string;

class ClientChatService
{
	private:
		string username;
		std::unique_ptr<Chat::ChatService::Stub> stub;
	public:	
		ClientChatService(string username)
		{
			this->username = username;

			auto channel = grpc::CreateChannel("localhost:50051",grpc::InsecureChannelCredentials());

    stub = Chat::ChatService::NewStub(channel);
		}
		void ReadLoop()
		{
			while(true){}
		}
		void WriteLoop()
		{
			while(true){}
		}
		void Run()
		{
			//add user metadata that will be sent along with the stream
			grpc::ClientContext context;
			context.AddMetadata("username", username);
			//open bi-directional stream
			auto stream = stub->SendUserMessage(&context);
			//start read-write loop
			std::thread reader(&ClientChatService::ReadLoop, this);
			std::thread writer(&ClientChatService::WriteLoop, this);
			reader.join();
			writer.join();
			//disconnect from server
			std::cout << "Disconnected from server." << std::endl;
		}
};

int main(int argc, char* argv[])
{
	//give client name
	string username;
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
