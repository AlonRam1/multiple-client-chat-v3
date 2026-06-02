#pragma once

#include <string>
#include "chat.grpc.pb.h"

class ClientSession
{
	private:
		std::string username;
		grpc::ServerWriter<Chat::UserMessage>* stream;
	public:	
		ClientSession(std::string username);
		void WriteToClient(Chat::UserMessage);
		std::string GetUsername();
};
