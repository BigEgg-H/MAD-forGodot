#ifndef GGSCCS_H
#define GGSCCS_H

#include "../../madstdlib.h"

#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/os/thread.h"
#include "core/os/mutex.h"
#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/templates/rid.h"
#include "core/variant/variant.h"

typedef void (*MADCommand());

class SC : public RefCounted{
	GDCLASS(SC, RefCounted);

	Vector<MADCommand*> commands;

	bool packed;

public:
	SC();

public:
	bool is_packed;

	MADERROR pack();
	

protected:
	static void _bind_methods();
};

class GGSCCS : public Object {
	GDCLASS(GGSCCS, Object);

	static GGSCCS *singleton;
	static void thread_func(void* p_userData);

private:
	Thread *thread;
	Mutex *mutex;

public:
	GGSCCS();
	static GGSCCS *get_singleton();

public:
	MADERROR excute_SC(SC *p_SC);
	MADERROR push_SC(SC *p_SC);

protected:
	static void _bind_methods();
};

#endif
