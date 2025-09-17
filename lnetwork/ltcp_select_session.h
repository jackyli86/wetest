#pragma once
#include "lnetwork_def.h"

class ltcp_select_server;
class ltcp_select_session
{
	friend class ltcp_select_server;

public:
	ltcp_select_session();

	~ltcp_select_session();

	void init(int session_id, ltcp_select_server* select_server);

	void uninit();

protected:
	void _open(SOCKET client_socket, std::string ip, int port);

	void _close();

	void _handle_recv();

	void _handle_send() {}
private: 
	inline bool _is_connected() {
		return m_net_status == connected && m_client_socket != INVALID_SOCKET;
	}

	inline bool _is_readable() {
		return false;
	}

	inline bool _is_writable() {
		return false;
	}

private:
	int m_session_id;
	e_net_status m_net_status;

	SOCKET m_client_socket;
	ltcp_select_server* m_select_server;

	char* m_recv_buffer;
	int m_recv_buffer_size;
	int m_write_index;
	int m_read_index;

};

