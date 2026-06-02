#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <mutex>
#include <vector>
#include <algorithm>

#include <grpcpp/grpcpp.h>
#include  "chat.grpc.pb.h"

class ServerChatService final : public Chat::ChatService::Service
{
	private:
		ClientManager client_manager;
	public:	
		grpc::Status SendUserMessage(grpc::ServerContext* context, grpc::ServerReaderWriter<Chat::UserMessage, Chat::UserMessage>* stream) override;

};

