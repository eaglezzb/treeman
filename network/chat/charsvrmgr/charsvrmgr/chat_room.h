#pragma once
#include "stdafx.h"
#include "commonmgrtypedef.h"
#include "chat_participant.h"

//聊天室
class chat_room
{
public:
	chat_room(void);
	virtual ~chat_room(void);
	 void deliver(const chat_message& msg);  //聊天室广播消息
	 void deliver_group(const chat_message& msg); //分组发送消息
	 void leave(chat_participant_ptr participant);  //有参与者离开
	 void join(chat_participant_ptr participant);  //有参与者加入
private:
  std::set<chat_participant_ptr> participants_; //记录参与者
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;  //记录最近的消息
};

