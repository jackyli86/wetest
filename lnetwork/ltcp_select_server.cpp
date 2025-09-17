#include "pch.h"
#include "ltcp_select_server.h"
#include "lnetwork_init.h"
#include "ltcp_select_session.h"
#include "lsignal_listener.h"

ltcp_select_server::ltcp_select_server()
	: socket_server(INVALID_SOCKET)
	, m_client_sessions(nullptr)
	, m_client_session_max(FD_SETSIZE)
	, m_hash_session(m_client_session_max)
	, m_available_sessions(m_client_session_max)
{
}

ltcp_select_server::~ltcp_select_server()
{
}

void ltcp_select_server::startup(std::string ip, int port)
{
	_init_client_sessions();

	socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	u_long mode = 1;  // 1 = ·Ç×èÈû, 0 = ×èÈû
	ioctlsocket(socket_server, FIONBIO, &mode);

	sockaddr_in addr{0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (ip.empty()) {
		addr.sin_addr.s_addr = ADDR_ANY;
	}
	else {
		inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
	}
	bind(socket_server, (sockaddr*)(&addr), (int)sizeof(addr));

	listen(socket_server, 64);

	m_thread_worker = std::thread(&ltcp_select_server::_worker_thread, this);
}

void ltcp_select_server::shutdown()
{
	if (m_thread_worker.joinable()) {
		m_thread_worker.join();
	}

	closesocket(socket_server);
	m_available_sessions.clear();
	for (int i = 0; i < m_client_session_max; i++) {
		(m_client_sessions + i)->uninit();
	}
	delete[] m_client_sessions;
	m_client_sessions = nullptr;
}

void ltcp_select_server::_init_client_sessions()
{
	m_client_sessions = new ltcp_select_session[m_client_session_max]();
	ltcp_select_session* session_ptr = nullptr;
	for (int i = 0; i < m_client_session_max; i++) {
		session_ptr = &(m_client_sessions[i]);
		session_ptr->init(i + 1, this);
		m_hash_session.insert({ session_ptr->m_session_id, session_ptr });
		m_available_sessions.push_back(session_ptr);
	}
	session_ptr = nullptr;
}

void ltcp_select_server::_worker_thread()
{
	fd_set readfds;
	fd_set writefds;

	ltcp_select_session* session_ptr = nullptr;
	timeval timeout = { 0, 1000 * 100}; // 100 ºÁÃë
	for (; lsignal_listener::instance().is_running(); ) {
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);

		FD_SET(socket_server, &readfds);
		for (auto pair : m_hash_session) {
			session_ptr = pair.second;
			if (!session_ptr->_is_connected()) {
				continue;				
			}

			FD_SET(session_ptr->m_client_socket, &readfds);
			if (session_ptr->_is_writable()) {
				FD_SET(session_ptr->m_client_socket, &writefds);
			}
		}
		session_ptr = nullptr;

		int sn = select(0, &readfds, &writefds, nullptr, &timeout);
		if (sn == SOCKET_ERROR) {
			lsignal_listener::instance().force_stop();
		}
		else if (sn == 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else {
			if (FD_ISSET(socket_server, &readfds)) {
				_handle_accept();
			}

			for (int i = 0; i < m_client_session_max; i++) {
				session_ptr = &(m_client_sessions[i]);
				if (!session_ptr->_is_connected()) {
					continue;
				}

				if (FD_ISSET(session_ptr->m_client_socket, &readfds)) {
					session_ptr->_handle_recv();
				}

				if (session_ptr->_is_writable() && FD_ISSET(session_ptr->m_client_socket, &writefds)) {
					session_ptr->_handle_recv();
				}

			}
		}

	}
}

void ltcp_select_server::_handle_accept()
{
	int counter = 0;
	char clientIP[INET6_ADDRSTRLEN];
	ltcp_select_session* session_ptr = nullptr;
	sockaddr_in addr;
	int addrlen = sizeof(addr);
	while (true) {
		SOCKET socket_client = accept(socket_server, (sockaddr*)(&addr), (int*)&addr);
		DWORD last_error = WSAGetLastError();
		if (socket_client == INVALID_SOCKET) {
			if (last_error == WSAEWOULDBLOCK) {
				return;
			}

			lsignal_listener::instance().force_stop();
			return;
		}

		session_ptr = _get_available_session();
		if (session_ptr == nullptr) {
			closesocket(socket_client);
			return;
		}

		inet_ntop(AF_INET, &addr.sin_addr, clientIP, INET6_ADDRSTRLEN);
		session_ptr->_open(socket_client, clientIP, addr.sin_port);
	}
}
