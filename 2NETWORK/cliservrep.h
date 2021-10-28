#pragma once
#include <string>
enum GRANT_TYPE {
	GRANT_TYPE_ZERO,
	GRANT_TYPE_NORMAL,
	GRANT_TYPE_INCREASED,
};
struct ClientForm {
	std::string lastname;
	int grant;
	int id;
};
struct ServerForm {
	std::string lastname;
	GRANT_TYPE grant;
	int id;
};
