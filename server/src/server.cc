#include <iostream>
#include <memory>
#include <string>
#include <mutex>
#include <vector>
#include <algorithm>

#include <grpcpp/grpcpp.h>
#include  "chat.grpc.pb.h"

using std::string;

class ServerChatService final : public Chat::ChatService::Service
{
	grpc::Status SendUserMessage(grpc::ServerContext* context, grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream) override
	{
		//take username from metadata
		auto it = context->client_metadata().find("username");

		std::string username;

		if (it != context->client_metadata().end())
		{
    		username = std::string(it->second.data(), it->second.size());
		}
		//notify new user login
		std::cout << username << " connected." << std::endl;
		//enter message receive loop
		Chat::UserMessage msg;
		while(stream->Read(&msg))
		{
		//TODO:INSERT BROADCAST LOGIC HERE.	
		}
		//disconnect message
		std::cout << username << " disconnected." << std::endl;

		return grpc::Status::OK;
	}
};

int main() {

    string address("0.0.0.0:50051");

    ServerChatService service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "Server running on " << address << std::endl;

    server->Wait();

    return 0;
}


