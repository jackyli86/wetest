#pragma once
#include <thread>

class ltcp_select_session;

class ltcp_select_server
{
	friend class ltcp_select_session;
public:
	ltcp_select_server();

	~ltcp_select_server();

	void startup(std::string ip, int port);

	void shutdown();

private:
	void _init_client_sessions();

	void _worker_thread();

	inline void _return_available_session(ltcp_select_session* session_ptr) {
		m_available_sessions.push_back(session_ptr);
	}

	inline ltcp_select_session* _get_available_session() {
		ltcp_select_session* session_ptr = m_available_sessions.front();
		if (session_ptr == nullptr) {
			return nullptr;
		}

		m_available_sessions.pop_front();
		return session_ptr;
	}

	void _handle_accept();

	void _on_connect(int session_id, std::string ip, int port) {}

private:
	SOCKET socket_server;

	ltcp_select_session* m_client_sessions;
	int m_client_session_max;
	std::unordered_map<int, ltcp_select_session*> m_hash_session;
	std::list<ltcp_select_session*> m_available_sessions;

	std::thread m_thread_worker;
};

