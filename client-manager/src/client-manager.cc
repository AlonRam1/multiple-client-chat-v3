#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>

#include "client-manager.h"
#include "client-session.h"
#include "chat.grpc.pb.h"

ClientManager::ClientManager(){}

void ClientManager::Add(std::string username, grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream)
{
	std::lock_guard<std::mutex> lock(manager_mutex);
	client_vector.push_back(std::make_shared<ClientSession>(username, stream));
}

void ClientManager::Remove(std::string username)
{
	std::lock_guard<std::mutex> lock(manager_mutex);
	client_vector.erase(std::remove_if(client_vector.begin(), client_vector.end(), [&username](std::shared_ptr<ClientSession>& client) {return client->GetUsername() == username;}), client_vector.end());
}
void ClientManager::Broadcast(Chat::UserMessage msg)
{
	std::lock_guard<std::mutex> manager_lock(manager_mutex);
	for(auto& client : client_vector)
	{
		client->WriteToClient(msg);
	}
}

std::vector<std::shared_ptr<ClientSession>> ClientManager::GetClientVector()
{
	return client_vector;
}






