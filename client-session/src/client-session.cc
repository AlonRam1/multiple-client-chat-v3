#include <iostream>
#include <memory>
#include <thread>

#include "client-session.h"
#include "chat.grpc.pb.h"

ClientSession::ClientSession(std::string username)
{
	this->username = username;
}
void ClientSession::WriteToClient(Chat::UserMessage msg)
{
	stream->Write(msg);	
}

std::string ClientSession::GetUsername(){return this->username;}


