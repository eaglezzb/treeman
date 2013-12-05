#include "StdAfx.h"
#include "chat_room.h"

chat_room::chat_room(void)
{
}

chat_room::~chat_room(void)
{
}
void chat_room::join(chat_participant_ptr participant)
{
    participants_.insert(participant);
	OutputDebugString(L"chat_room::join");
	//将最近的消息全部发送给参与者
    std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
        boost::bind(&chat_participant::deliver, participant, _1));
}
void chat_room::leave(chat_participant_ptr participant)
{
	OutputDebugString(L"chat_room::leave");
	participants_.erase(participant);
}
void chat_room::deliver(const chat_message& msg)
 {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

	//向每个参与者广播
    std::for_each(participants_.begin(), participants_.end(),
        boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
}
