#ifndef GGSCCS_H
#define GGSCCS_H

#include "../../madstdlib.h"

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/os/thread.h"
#include "core/os/mutex.h"
#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"

const static MADVersion MAD_VERSION_GGSCCS(0,1,0,204);

typedef void(*MADCommand)(Array& Parameter);

struct StreamCommand {
	MADCommand Command;
	Array Parameter;
	StreamCommand() {
		Command = nullptr;
		Parameter = Array();
	}
	StreamCommand(const StreamCommand& _from) {
		Command = _from.Command;
		Parameter = _from.Parameter;
	}
	StreamCommand(const MADCommand& _Command,const Array& _Parameter) {
		Command = _Command;
		Parameter = _Parameter;
	}
};

class SCAllocator : public RefCounted {
	GDCLASS(SCAllocator, RefCounted);

private:


public:
	Vector<StreamCommand*> commands;
	bool packed;

public:
	SCAllocator();

public:
	bool is_packed;

	MADERROR pack();

public:
	MADERROR print(const String &str);

protected:
	static void _bind_methods();
};

class GGSCCS : public Object {
	GDCLASS(GGSCCS, Object);

	static GGSCCS *singleton;
	static void thread_func(void* p_userData);

private:
	Thread *thread;
	Mutex *mutex_commands;
	Mutex *mutex_commands_loop;

	bool finished;

	Vector<StreamCommand *> commands_stack;
	Vector<StreamCommand *> commands_loop_stack;

public:
	GGSCCS();
	static GGSCCS *get_singleton();
	void exit();

public:
	MADERROR excute_SC(Ref<SCAllocator> p_SCAllocator);
	MADERROR push_SC(Ref<SCAllocator> p_SCAllocator);
	MADERROR loop_SC(Ref<SCAllocator> p_SCAllocator);
	MADERROR make_game_session(bool multiplayer = false);

protected:
	static void _bind_methods();
};
#endif
