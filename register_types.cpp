/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "core/config/engine.h"

#include "madstdlib.h"
#include "mad_base/madbase.h"
#include "mad_servers_2d/madservers2d.h"
#include "mad_servers_3d/madservers3d.h"

static GGSCCS* g_ggsccs_singleton = NULL;

static Ref<ResourceFormatLoaderMADScript> mad_script_loader;
static Ref<ResourceFormatSaverMADScript> mad_script_saver;

void register_lua_types() {
	ClassDB::register_class<MADScript>();

	mad_script_loader.instantiate();
	ResourceLoader::add_resource_format_loader(mad_script_loader);

	mad_script_saver.instantiate();
	ResourceSaver::add_resource_format_saver(mad_script_saver);
}

void unregister_lua_types() {
	ResourceLoader::remove_resource_format_loader(mad_script_loader);
	mad_script_loader.unref();

	ResourceSaver::remove_resource_format_saver(mad_script_saver);
	mad_script_saver.unref();
}

void initialize_mad_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_CORE) {
		register_lua_types();
	}
	if (p_level == MODULE_INITIALIZATION_LEVEL_SERVERS) {
		g_ggsccs_singleton = memnew(GGSCCS);
		ClassDB::register_class<GGSCCS>();
		Engine::get_singleton()->add_singleton(Engine::Singleton("GGSCCS", g_ggsccs_singleton->get_singleton()));
	}

}

void uninitialize_mad_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_CORE) {
		unregister_lua_types();
	}
	if (p_level == MODULE_INITIALIZATION_LEVEL_SERVERS) {
		g_ggsccs_singleton->exit();
		memdelete(g_ggsccs_singleton);
	}
}
