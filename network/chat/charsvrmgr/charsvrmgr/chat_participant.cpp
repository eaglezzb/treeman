#include "StdAfx.h"
#include "chat_participant.h"


chat_participant::chat_participant(void)
{
	is_checked_ = FALSE;
}


chat_participant::~chat_participant(void)
{
}

bool chat_participant::get_checked()
{
	return is_checked_;
}
void chat_participant::set_checked()
{
	is_checked_ = TRUE;
}