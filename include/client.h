#include <mutex>
#include <iostream>
#include <memory>

#include <grpcpp/grpcpp.h>
#include "chat.grpc.pb.h"


class ClientChatService
{
	private:
		std::string username;
		std::unique_ptr<Chat::ChatService::Stub> stub;
		std::mutex client_mutex;
	public:
		ClientChatService(std::string username);
		void ReadLoop(grpc::ClientReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream);
		void Write(Chat::UserMessage msg, grpc::ClientReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream);
		void WriteLoop(grpc::ClientReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream);
		void Run();
};
