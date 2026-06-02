#pragma once

#include <string>
#include "chat.grpc.pb.h"

class ClientSession
{
	private:
		std::string username;
		grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream;
	public:	
		ClientSession(std::string username, grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream);
		void WriteToClient(Chat::UserMessage);
		std::string GetUsername();
		void SetUsername(std::string username);
		void SetStream(grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream);
};
