#pragma once

#include "client-session.h"

class ClientManager
{
	private:
		std::vector<ClientSession> client_vector;	
	public:
		ClientManager();
		void Add(std::string username, grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream);
		void Remove(std::string username);
		void Broadcast(Chat::UserMessage msg);

};
