#pragma once
#include "message_protocol.h"

class TestMethod 
{
public:
	virtual void HandleMessage(RequestBufferPtr msg);

};

void TestMethod::HandleMessage(RequestBufferPtr msg)
{
	if (!msg)
	{
		return;
	}

	std::cout << __FUNCTION__ << "receive data "<< msg->body_;
	ResponseBufferPtr res(new ResponseBuffer);
	res->body_ = msg->body_;
	msg->conn_->sendBundleMessage(res);
}



