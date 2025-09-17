#pragma once

class lnetwork_init {
public:
	lnetwork_init() {
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2,2), &wsa) != 0
			|| WSAStartup(MAKEWORD(2, 1), &wsa) != 0
			|| WSAStartup(MAKEWORD(2, 0), &wsa) != 0
			|| WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
		{ }
	}

	~lnetwork_init() {
		WSACleanup();
	}
};

static lnetwork_init g_lnetwork_init;