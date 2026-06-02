#pragma once

#include "client-session.h"

class ClientManager
{
	private:
		std::vector<ClientSession> client_vector;	
	public:
		ClientManager();
		void Add(ClientSession c);
		void Remove(std::string username);
		void Broadcast(Chat::UserMessage msg);

};
