#pragma once

#include <mutex>
#include "client-session.h"

class ClientManager
{
	private:
		std::vector<std::shared_ptr<ClientSession>> client_vector;
		std::mutex manager_mutex;
	public:
		ClientManager();
		void Add(std::string username, grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream);
		void Remove(std::string username);
		void Broadcast(Chat::UserMessage msg);
		std::vector<std::shared_ptr<ClientSession>> GetClientVector();
};
