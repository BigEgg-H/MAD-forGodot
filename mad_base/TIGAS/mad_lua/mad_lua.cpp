#include "mad_lua.h"

void MADScript::_bind_methods() {
	ClassDB::bind_method(D_METHOD("run"), &MADScript::run);
}

MADScript::MADScript() {
	lua = luaL_newstate();

	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_table(lua);
	luaopen_math(lua);
	luaopen_utf8(lua);
	luaopen_coroutine(lua);
}

MADScript::~MADScript() {
	lua_close(lua);
}

bool MADScript::run() {
	return !(lua_pcall(lua, 0, 0, 0));
}

Error MADScript::load_file(const String &p_path) {
	Error error;
	Ref<FileAccess> file = FileAccess::open(p_path, FileAccess::READ, &error);
	if (error != OK) {
		if (!file.is_null()) {
			file->close();
		}
		return error;
	}

	script = file.ptr()->get_as_text();
	file->close();

	if (luaL_loadbufferx(lua, script.ascii().get_data(), script.ascii().length(), p_path.get_file().ascii().get_data(), NULL)) {
		return ERR_CANT_CREATE;
	}

	return OK;
}

Error MADScript::save_file(const String &p_path, const Ref<Resource> &p_resource) {
	Error error;
	Ref<FileAccess> file = FileAccess::open(p_path, FileAccess::WRITE, &error);
	if (error != OK) {
		if (!file.is_null()) {
			file->close();
		}
		return error;
	}

	file.ptr()->store_string(script);

	file->close();

	return OK;
}

Ref<Resource> ResourceFormatLoaderMADScript::load(const String &p_path, const String &p_original_path, Error *r_error, bool p_use_sub_threads, float *r_progress, CacheMode p_cache_mode) {
	Ref<MADScript> script_b = memnew(MADScript);
	Error err =  script_b->load_file(p_path);
	if (r_error != nullptr) {
		*r_error = err;
	}
	return script_b;
}

void ResourceFormatLoaderMADScript::get_recognized_extensions(List<String> *r_extensions) const {
	if (!r_extensions->find("lua")) {
		r_extensions->push_back("lua");
	}
}

bool ResourceFormatLoaderMADScript::handles_type(const String &p_type) const {
	return p_type == "MADScript";
}

String ResourceFormatLoaderMADScript::get_resource_type(const String &p_path) const {
	return "MADScript";
}

Error ResourceFormatSaverMADScript::save(const Ref<Resource> &p_resource, const String &p_path, uint32_t p_flags) {
	Ref<MADScript> script_b = p_resource;
	Error error = script_b->save_file(p_path, p_resource);
	return error;
}

bool ResourceFormatSaverMADScript::recognize(const Ref<Resource> &p_resource) const {
	return Object::cast_to<MADScript>(*p_resource) != NULL;
}

void ResourceFormatSaverMADScript::get_recognized_extensions(const Ref<Resource> &p_resource, List<String> *r_extensions) const {
	if (Object::cast_to<MADScript>(*p_resource)) {
		r_extensions->push_back("lua");
	}
}
