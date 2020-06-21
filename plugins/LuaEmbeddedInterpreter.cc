extern "C"
{
#include <lualib.h>
#include <lauxlib.h>
}


#include "mcl.h"
#include "Pipe.h"
#include "Interpreter.h"
#include "LuaEmbeddedInterpreter.h"

// Exported functions
extern "C" EmbeddedInterpreter *createInterpreter() {
    return new LuaEmbeddedInterpreter();
}

extern "C" const char* initFunction(const char*) {
    return NULL;
}

extern "C" const char* versionFunction() {
    return "Lua embedded interpreter (" __DATE__ ")";
}


LuaEmbeddedInterpreter::LuaEmbeddedInterpreter()
{
  L = luaL_newstate();

  luaL_openlibs(L); /* Load Lua libraries */
 
  set("default_var", "");
}

LuaEmbeddedInterpreter::~LuaEmbeddedInterpreter() {
    lua_close(L);   /* Cya, Lua */
}

bool LuaEmbeddedInterpreter::load_file(const char *file, bool suppress)
{
  FILE *script= nullptr;
  const char *fullname = findFile(file, ".lua");

  if (!(fullname) || (!(script = fopen(fullname, "r")))) {
      if (config->getOption(opt_interpdebug) && !suppress)
          report("@@ Loading %s = %m", file);
      return false;
  }

  int status = luaL_loadfile(L, (char*)fullname);

  fclose(script);

  if(status) {
    if(config->getOption(opt_interpdebug) && !suppress) {
        const char *msg;
        msg = lua_tostring(L, -1);
        if (msg == nullptr) msg = "(error with no message)";
        report("<LUA ERRROR> Status=%d, %s\n", status, msg);
        lua_pop(L, 1);
    }
    return false;
  }
  return true;
}

void LuaEmbeddedInterpreter::eval(const char *expression, char *result)
{
    if(result) *result = '\0';
    if(expression && !*expression) return;

    int error = luaL_loadbuffer(L, expression, strlen(expression), "eval code") ||
            lua_pcall(L, 0, 0, 0);
    if (error) {
        report("%s", lua_tostring(L, -1));
        lua_pop(L, 1);  /* pop error message from the stack */
    }
}

bool LuaEmbeddedInterpreter::run(const char *function, const char *args,
                                    char *result)
{
//  PyObject *func = get_function(function);
//  PyObject *func_args, *res;
//  char *str;
//
//  set("default_var", args);
//
//  if (!isEnabled(function))
//      return false;
//
//  if(!func) {
//    char str[strlen(function)+4];
//    sprintf(str, "%s.py", function);
//    if(!load_file(str) && !(func = get_function(function))) {
//        report("@@ Could not find function '%s' anywhere", function);
//        disable_function(function);
//        return false;
//    }
//  }
//
//  func_args = Py_BuildValue("()");
//  if(!func_args) return false;
//  res = PyEval_CallObject(func, func_args);
//  if(!res) {
//    PyErr_Print();
//    return false;
//  }
//  Py_DECREF(func_args);
//  Py_DECREF(res);
//
//  if(result) {
//    str = get_string("default_var");
//    strcpy(result, str);
//  }
  return false;
}

bool LuaEmbeddedInterpreter::run_quietly(const char *file, const char *args,
                                          char *result, bool suppress)
{
//  char *func = strrchr((char *)file, '/');
//  char buf[256];
//
//  if(func) func++;
//  else func = (char*)file;
//
//  if(!(get_function(func))) {
//    sprintf(buf, "%s.py", file);
//    if(!load_file(buf, suppress)) {
//        disable_function(func);
//        return false;
//    }
//  }
//
//  return run(func, args, result);
    return false;
}

void *LuaEmbeddedInterpreter::match_prepare(const char *pattern,
                                               const char *commands)
{
//  char buf[2048];
//  char *tmp;
//
//  match(regexp_fixer, commands, tmp);
//  sprintf(buf, "tmp_re = re.compile(r\"%s\")\n"
//               "tmp_match = tmp_re.search(default_var)\n"
//               "if tmp_match:\n"
//               "  default_var = \"%s\"\n"
//               "else:\n"
//               "  default_var = \"\"\n", pattern, tmp);
//
//  return code_compile(buf);
    return nullptr;
}

void *LuaEmbeddedInterpreter::substitute_prepare(const char *pattern,
                                                    const char *replacement)
{
//  char buf[2048];
//  char *tmp;
//
//  match(regexp_fixer, replacement, tmp);
//  sprintf(buf, "tmp_re = re.compile(r\"%s\")\n"
//               "tmp_match = tmp_re.search(default_var)\n"
//               "if tmp_match:\n"
//               "  default_var = tmp_re.sub(\"%s\", default_var)\n"
//               "else:\n"
//               "  default_var = \"\"\n", pattern, tmp);
//
//  return code_compile(buf);
    return nullptr;
}

bool LuaEmbeddedInterpreter::match(void *code, const char *match_str,
                                      char *&result)
{
//  char *str;
//
//  set("default_var", match_str);
//
//  ///ALKIS change for python3
//#if PY_MAJOR_VERSION >= 3
//  if(!(PyEval_EvalCode((PyObject*)code, globals, globals))) {
//#else
//  if(!(PyEval_EvalCode((PyCodeObject*)code, globals, globals))) {
//#endif
//    report("@@ Error evaluating match or substitute code:\n");
//    PyErr_Print();
//    return false;
//  }
//  else {
//    str = get_string("default_var");
//    result = str;
//
//    return (*str) ? true : false;
//  }
    return false;
}

void LuaEmbeddedInterpreter::set(const char *name, int value)
{
//    char buf[2048];
//    snprintf(buf, sizeof(buf), "%s=%d", name, value);
//    if (luaL_dostring(L, buf) != 0) {
//        report("lua: %s\n", lua_tostring(L, -1));
//        return;
//    }
    lua_pushinteger(L,value);
    lua_setglobal(L,name);
}

void LuaEmbeddedInterpreter::set(const char *name, const char *value)
{
//    char buf[2048];
//    snprintf(buf, sizeof(buf), "%s='%s'", name, value);
//    if (luaL_dostring(L, buf) != 0) {
//        report("lua: %s\n", lua_tostring(L, -1));
//        return;
//    }
    lua_pushstring(L,value);
    lua_setglobal(L,name);
}

int LuaEmbeddedInterpreter::get_int(const char *name)
{
    bool found;
    int val = 0;

    lua_getglobal(L, name);
    found = lua_isnumber(L, -1);
    if(!found) {
        report("LUA: can't find variable %s\n", name);
        return val;
    }
    // Fetch value
    val = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return val;
}

char *LuaEmbeddedInterpreter::get_string(const char *name)
{
    bool found;
    char *val = (char *) "";

    // Check if value is in file
    lua_getglobal(L, name);
    found = lua_isnumber(L, -1);
    if(!found) {
        report("LUA: can't find variable %s\n", name);
        return val;
    }
    // Fetch value
    val = (char *) lua_tostring(L, -1);
    lua_pop(L, 1);
    return val;
}

/*
PyObject *LuaEmbeddedInterpreter::get_function(const char *name)
{
  return PyDict_GetItemString(globals, (char*)name);
}

PyObject *LuaEmbeddedInterpreter::code_compile(const char *code)
{
  PyObject *code_obj;

  if(!(code_obj = Py_CompileString((char*)code, "<string>", Py_file_input)))
    PyErr_Print();
  return code_obj;
}
*/