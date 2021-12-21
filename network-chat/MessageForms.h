#include <string>
enum MSG_TYPE {
	MSG_TYPE_ALL,
	MSG_TYPE_PRIVATE,
	MSG_TYPE_LEAVE,
	MSG_TYPE_TEST,
	MSG_TYPE_NULL,
};
struct MessageForm {
	char nick[1024];
	char target_nick[1024];
	char msgbody[1024];
};
#pragma once
