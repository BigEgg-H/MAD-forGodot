/* register_types.h */

#include "modules/register_module_types.h"

void initialize_mad_module(ModuleInitializationLevel p_level);
void uninitialize_mad_module(ModuleInitializationLevel p_level);

void register_lua_types();
void unregister_lua_types();
