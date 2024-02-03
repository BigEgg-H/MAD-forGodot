#include "ggsccs.h"

SC::SC() {
}

MADERROR SC::pack() {
	return MAD_ERROR_UNKNOW_ERR;
}

void SC::_bind_methods() {
}

void GGSCCS::thread_func(void *p_userData) {
}

GGSCCS::GGSCCS() {
	singleton = this;
	print_line("GGSCCS load done!GGSCCS version:");
	print_line(MAD_VERSION_GGSCCS);
}

GGSCCS *GGSCCS::singleton = NULL;

GGSCCS *GGSCCS::get_singleton() {
	return singleton;
}

MADERROR GGSCCS::excute_SC(SC *p_SC) {
	return MAD_ERROR_UNKNOW_ERR;
}

MADERROR GGSCCS::push_SC(SC *p_SC) {
	return MAD_ERROR_UNKNOW_ERR;
}

MADERROR GGSCCS::make_game_session(bool multiplayer) {

	return MAD_ERROR_UNKNOW_ERR;
}

void GGSCCS::_bind_methods() {
	ClassDB::bind_method(D_METHOD("excute_SC", "SC"), &GGSCCS::excute_SC);
	ClassDB::bind_method(D_METHOD("push_SC", "SC"), &GGSCCS::push_SC);
	ClassDB::bind_method(D_METHOD("make_game_session", "multiplayer"), &GGSCCS::make_game_session);
}

void GGSCCS::exit() {
}
