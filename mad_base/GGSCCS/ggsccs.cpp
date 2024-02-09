#include "ggsccs.h"

GGSCCS *GGSCCS::singleton = NULL;

void GGSCCS::thread_func(void *p_userData) {
	GGSCCS *ggsccs = reinterpret_cast<GGSCCS*>(p_userData);
}

GGSCCS::GGSCCS() {
	if (singleton != NULL) {
		ERR_PRINT("GGSCCS initialized twice!");
		return;
	}
	singleton = this;
	finished = false;
	thread = memnew(Thread);
	mutex_commands = memnew(Mutex);
	mutex_commands_loop = memnew(Mutex);
	thread->start(GGSCCS::thread_func, this);
	{
		String _str = "GGSCCS[";
		_str += MAD_VER_TO_STR(MAD_VERSION_GGSCCS);
		_str += "]\nGGSCCS load done!";
		print_line(_str);
	}
}

GGSCCS *GGSCCS::get_singleton() {
	return singleton;
}

MADERROR GGSCCS::make_game_session(bool multiplayer) {

	return MAD_ERROR_UNKNOW_ERR;
}

void GGSCCS::_bind_methods() {
	ClassDB::bind_method(D_METHOD("make_game_session", "multiplayer"), &GGSCCS::make_game_session);
}

void GGSCCS::exit() {
	finished = true;
	thread->wait_to_finish();
	memdelete(thread);
	memdelete(mutex_commands);
	memdelete(mutex_commands_loop);
}

