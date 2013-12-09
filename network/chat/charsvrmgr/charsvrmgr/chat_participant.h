#pragma once
#include "chat_message.hpp"

//�������
//�����ṩ�����ҳ�Ա�Ľӿ�
class chat_participant
{
public:
	chat_participant(void);
	virtual ~chat_participant(void);
	virtual void deliver(const chat_message& msg) = 0;
	virtual void deliver_group(const chat_message& msg) = 0;
	bool get_checked();
	void set_checked();
private:
	chat_message  chat_message_last;
	DWORD dw_user_id_;
	DWORD dw_task_id_;
private:
	bool is_checked_;
};
typedef boost::shared_ptr<chat_participant> chat_participant_ptr;

