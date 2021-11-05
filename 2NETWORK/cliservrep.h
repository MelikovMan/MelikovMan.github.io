#pragma once
#include <string>
enum GRANT_TYPE {
	GRANT_TYPE_ZERO,
	GRANT_TYPE_NORMAL,
	GRANT_TYPE_INCREASED,
};
struct ClientForm {
	int grant;
};
struct ServerForm {
	GRANT_TYPE grant;
};