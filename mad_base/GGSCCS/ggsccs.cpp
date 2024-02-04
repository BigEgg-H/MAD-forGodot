#include "ggsccs.h"
#include "commands.h"

SCAllocator::SCAllocator() {
}

MADERROR SCAllocator::pack() {
	if (is_packed) {
		return MAD_ERROR_SURPLUS_CALL;
	}
	is_packed = true;
	return MAD_ERROR_OK;
}

MADERROR SCAllocator::print(const String& str) {
	if (is_packed) {
		ERR_PRINT("This SCAllocator has already beem packed!");
		return MAD_ERROR_INVALID_CALL;
	}
	Array pra;
	pra.append(str);
	commands.append(&StreamCommand(ggsccs_print, pra));
	return MAD_ERROR_OK;
}

void SCAllocator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("print", "str"), &SCAllocator::print);
	ClassDB::bind_method(D_METHOD("pack"), &SCAllocator::pack);
}

GGSCCS *GGSCCS::singleton = NULL;

void GGSCCS::thread_func(void *p_userData) {
	GGSCCS *ggsccs = reinterpret_cast<GGSCCS*>(p_userData);
	while (!ggsccs->finished) {
		if (ggsccs->mutex_commands_loop->try_lock()) {
			for (int i = 0; i < ggsccs->commands_loop_stack.size(); i++) {
				(ggsccs->commands_loop_stack.get(i)->Command)(ggsccs->commands_loop_stack.get(i)->Parameter);
			}
			ggsccs->mutex_commands_loop->unlock();
		}
		if (ggsccs->mutex_commands->try_lock()) {
			for (int i = 0; i < ggsccs->commands_stack.size(); i++) {
				(ggsccs->commands_stack.get(i)->Command)(ggsccs->commands_stack.get(i)->Parameter);
			}
			ggsccs->commands_stack.clear();
			ggsccs->mutex_commands->unlock();
		}
	}
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

MADERROR GGSCCS::excute_SC(Ref<SCAllocator> p_SCAllocator) {
	if (p_SCAllocator.is_valid() && p_SCAllocator->is_packed) {
		Vector<StreamCommand *> *_commands_buffer = &(p_SCAllocator->commands);
		for (int i = 0; i < (*_commands_buffer).size(); i++) {
			((*_commands_buffer)[i]->Command)((*_commands_buffer)[i]->Parameter);
		}
		return MAD_ERROR_OK;
	}
	return MAD_ERROR_INVALID_PAR;
}

MADERROR GGSCCS::push_SC(Ref<SCAllocator> p_SCAllocator) {
	if (p_SCAllocator.is_valid() && p_SCAllocator->is_packed) {
		mutex_commands->lock();
		for (int i = 0; i < p_SCAllocator->commands.size(); i++) {
			commands_stack.push_back(p_SCAllocator->commands.get(i));
		}
		mutex_commands->unlock();
		return MAD_ERROR_OK;
	}
	return MAD_ERROR_INVALID_PAR;
}

MADERROR GGSCCS::loop_SC(Ref<SCAllocator> p_SCAllocator) {
	if (p_SCAllocator.is_valid() && p_SCAllocator->is_packed) {
		mutex_commands_loop->lock();
		for (int i = 0; i < p_SCAllocator->commands.size(); i++) {
			commands_loop_stack.push_back(p_SCAllocator->commands.get(i));
		}
		mutex_commands_loop->unlock();
		return MAD_ERROR_OK;
	}
	return MAD_ERROR_INVALID_PAR;
}

MADERROR GGSCCS::make_game_session(bool multiplayer) {

	return MAD_ERROR_UNKNOW_ERR;
}

void GGSCCS::_bind_methods() {
	ClassDB::bind_method(D_METHOD("excute_SC", "SCAllocator"), &GGSCCS::excute_SC);
	ClassDB::bind_method(D_METHOD("push_SC", "SCAllocator"), &GGSCCS::push_SC);
	ClassDB::bind_method(D_METHOD("make_game_session", "multiplayer"), &GGSCCS::make_game_session);
}

void GGSCCS::exit() {
	finished = true;
	thread->wait_to_finish();
	memdelete(thread);
	memdelete(mutex_commands);
	memdelete(mutex_commands_loop);
}
