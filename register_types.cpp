/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "core/config/engine.h"

#include "madstdlib.h"
#include "mad_base/madbase.h"
#include "mad_servers_2d/madservers2d.h"
#include "mad_servers_3d/madservers3d.h"

static GGSCCS* g_ggsccs_singleton = NULL;

void initialize_mad_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SERVERS) {
		g_ggsccs_singleton = memnew(GGSCCS);
		ClassDB::register_class<SCAllocator>();
		ClassDB::register_class<GGSCCS>();
		Engine::get_singleton()->add_singleton(Engine::Singleton("GGSCCS", g_ggsccs_singleton->get_singleton()));
	}
}

void uninitialize_mad_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SERVERS) {
		g_ggsccs_singleton->exit();
		memdelete(g_ggsccs_singleton);
	}
}
