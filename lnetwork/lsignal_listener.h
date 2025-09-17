#pragma once
class lsignal_listener
{
private:
	lsignal_listener() 
		: running(true)
	{
		SetConsoleCtrlHandler(lsignal_listener::_handler_routine, TRUE);
	}

	~lsignal_listener() {

	}

	// Delete copy constructor and assignment operator to prevent duplication
	lsignal_listener(const lsignal_listener&) = delete;
	lsignal_listener& operator=(const lsignal_listener&) = delete;

	static BOOL _handler_routine(DWORD ctrl_type) {
		switch (ctrl_type)
		{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT: {
			instance().running = false;
		}
		default:
			break;
		}
		return TRUE;
	}

public:
	static lsignal_listener& instance() {
		static lsignal_listener listener;
		return listener;
	}

	bool is_running() const {
		return running;
	}

	void force_stop() {
		running = false;
	}

private:
	std::atomic<bool> running;
};

