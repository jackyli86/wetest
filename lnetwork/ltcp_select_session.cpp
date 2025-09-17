#include "pch.h"
#include "ltcp_select_session.h"
#include "ltcp_select_server.h"

ltcp_select_session::ltcp_select_session()
	: m_session_id(0)
	, m_net_status(e_net_status::none)
	, m_client_socket(INVALID_SOCKET)
{
}

ltcp_select_session::~ltcp_select_session()
{
}

void ltcp_select_session::init(int session_id, ltcp_select_server* select_server)
{
	m_session_id = session_id;
	m_select_server = select_server;

	m_recv_buffer_size = 1024;
	m_recv_buffer = new char[m_recv_buffer_size];
	m_write_index = 0;
	m_read_index = 0;
}

void ltcp_select_session::uninit()
{
}

void ltcp_select_session::_open(SOCKET client_socket, std::string ip, int port)
{
	m_client_socket = client_socket;
	m_net_status = e_net_status::connected;

	m_write_index = 0;
	m_read_index = 0;

	u_long mode = 1;  // 1 = ·Ç×èÈû, 0 = ×èÈû
	ioctlsocket(m_client_socket, FIONBIO, &mode);

	m_select_server->_on_connect(m_session_id, ip, port);
}

void ltcp_select_session::_close()
{
	if (m_client_socket != INVALID_SOCKET) {
		closesocket(m_client_socket);
	}
	m_client_socket = INVALID_SOCKET;
	m_net_status = e_net_status::none;
}

void ltcp_select_session::_handle_recv()
{
	int bytes_received = recv(m_client_socket, m_recv_buffer + m_write_index, m_recv_buffer_size - m_write_index, 0);
	DWORD last_error = WSAGetLastError();
	if (bytes_received > 0) {
		m_write_index += bytes_received;
	}
	else if (bytes_received == 0 || last_error != WSAEWOULDBLOCK) {
		_close();
		m_select_server->_return_available_session(this);
		return;
	}
}
