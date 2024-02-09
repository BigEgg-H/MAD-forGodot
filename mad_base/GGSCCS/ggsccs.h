#ifndef GGSCCS_H
#define GGSCCS_H

#include "../../madstdlib.h"
#include "../TIGAS/tigas.h"

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/os/thread.h"
#include "core/os/mutex.h"
#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"

const static MADVersion MAD_VERSION_GGSCCS(0,1,0,204);

class GGSCCS : public Object {
	GDCLASS(GGSCCS, Object);

	static GGSCCS *singleton;
	static void thread_func(void* p_userData);

private:
	Thread *thread;
	Mutex *mutex_commands;
	Mutex *mutex_commands_loop;

	bool finished;

public:
	GGSCCS();
	static GGSCCS *get_singleton();
	void exit();

public:
	MADERROR make_game_session(bool multiplayer = false);

protected:
	static void _bind_methods();
};

#endif
