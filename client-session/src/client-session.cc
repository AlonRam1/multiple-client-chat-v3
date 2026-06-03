#include <iostream>
#include <memory>
#include <thread>

#include "client-session.h"
#include "chat.grpc.pb.h"

ClientSession::ClientSession(std::string username, grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream)
{
	this->username = username;
	this->stream = stream;
}
void ClientSession::WriteToClient(Chat::UserMessage msg)
{
	std::lock_guard<std::mutex> lock(client_mutex);
	stream->Write(msg);	
}

std::string ClientSession::GetUsername(){return this->username;}

void ClientSession::SetUsername(std::string username)
{
	this->username = username;
}

void ClientSession::SetStream(grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream)
{
	this->stream = stream;
}

