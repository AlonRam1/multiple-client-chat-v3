#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "client-manager.h"
#include "chat.grpc.pb.h"

ClientManager::ClientManager(){}

void ClientManager::Add(ClientSession c)
{
	client_vector.push_back(c);
}

void ClientManager::Remove(std::string username)
{
	client_vector.erase(std::remove_if(client_vector.begin(), client_vector.end(), [&username](ClientSession& client) {return client.GetUsername() == username;}), client_vector.end());
}
void ClientManager::Broadcast(Chat::UserMessage msg)
{
	for(auto& client : client_vector)
	{
		client.WriteToClient(msg);
	}
}


