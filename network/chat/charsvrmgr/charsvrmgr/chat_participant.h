#pragma once
#include "chat_message.hpp"
class chat_participant
{
public:
	chat_participant(void);
	virtual ~chat_participant(void);
	virtual void deliver(const chat_message& msg) = 0;
};
typedef boost::shared_ptr<chat_participant> chat_participant_ptr;

