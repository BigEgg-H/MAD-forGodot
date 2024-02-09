#ifndef MAD_LUA_H
#define MAD_LUA_H

#include "../../../madstdlib.h"
#include "core/variant/variant_parser.h"
#include "core/io/resource_loader.h"
#include "core/io/resource_saver.h"

#include "lua_src/lua.hpp"

class MADScript : public Resource {
	GDCLASS(MADScript, Resource);

protected:
	static void _bind_methods();

public:
	MADScript();
	~MADScript();

	bool run();

private:
	String script;

	lua_State *lua;

public:
	Error load_file(const String &p_path);
	Error save_file(const String &p_path, const Ref<Resource> &p_resource);
};

class ResourceFormatLoaderMADScript : public ResourceFormatLoader {
	GDCLASS(ResourceFormatLoaderMADScript, ResourceFormatLoader);

public:
	virtual Ref<Resource> load(const String &p_path, const String &p_original_path = "", Error *r_error = nullptr, bool p_use_sub_threads = false, float *r_progress = nullptr, CacheMode p_cache_mode = CACHE_MODE_REUSE);
	virtual void get_recognized_extensions(List<String> *r_extensions) const;
	virtual bool handles_type(const String &p_type) const;
	virtual String get_resource_type(const String &p_path) const;
};

class ResourceFormatSaverMADScript : public ResourceFormatSaver {
	GDCLASS(ResourceFormatSaverMADScript, ResourceFormatSaver);

public:
	virtual Error save(const Ref<Resource> &p_resource, const String &p_path, uint32_t p_flags = 0);
	virtual bool recognize(const Ref<Resource> &p_resource) const;
	virtual void get_recognized_extensions(const Ref<Resource> &p_resource, List<String> *r_extensions) const;
};

#endif
