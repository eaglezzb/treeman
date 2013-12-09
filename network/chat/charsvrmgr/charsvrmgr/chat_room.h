#pragma once
#include "stdafx.h"
#include "commonmgrtypedef.h"
#include "chat_participant.h"

//������
class chat_room
{
public:
	chat_room(void);
	virtual ~chat_room(void);
	 void deliver(const chat_message& msg);  //�㲥��Ϣ
	 void deliver_group(const chat_message& msg); //���鷢����Ϣ
	 void leave(chat_participant_ptr participant);  //���뿪
	 void join(chat_participant_ptr participant);  //�м���
private:
  std::set<chat_participant_ptr> participants_; //������
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;  //��¼�������Ϣ
};

