
#include "luautils.hpp"
#include <sstream>

int
lua_stringexpr(lua_State* L, const char* expr, std::string & out)
{
  int err;
  std::ostringstream oss;
  size_t l;
  const char * p;
  
  if (!L) {
    return -1;
  }
  if (!expr) {
    return -1;
  }

  oss << "evalExpr=";
  oss << expr;

  /* return  LUA_OK=0 for success */
  err = luaL_dostring(L, oss.str().c_str());
  if (err) {
    return err;
  }
  /* no check the return value */
  lua_getglobal(L, "evalExpr");
  err = -1;
  if (lua_isstring(L, -1))
  {
    l = 0;
    p = lua_tolstring(L, -1, &l);
    if ((p && l)) {
      out.clear();
      out.assign(p, l);
      err = 0;
    }
  }
  /* remove lua_getglobal value */
  lua_pop(L, 1);
  return err;
}

/**
Evaluates a Lua expression that results in a number.
The number is stored in out.
*/
int
lua_numberexpr(lua_State* L, const char* expr, double* out)
{
  int err;
  std::ostringstream oss;

  if (!L) {
    return -1;
  }
  if (!expr) {
    return -1;
  }
  if (!out) {
    return -1;
  }

  oss << "evalExpr=";
  oss << expr;

  /* return  LUA_OK=0 for success */
  err = luaL_dostring(L, oss.str().c_str());
  if (err) {
    return err;
  }
  /* no check the return value */
  lua_getglobal(L, "evalExpr");
  err = -1;
  if (lua_isnumber(L, -1))
  {
    *out = lua_tonumber(L, -1);
    err = 0;
  }
  /* remove lua_getglobal value */
  lua_pop(L, 1);
  return err;
}

/**
Evaluates a Lua expression that results in a number and cast to an int.
*/
int
lua_intexpr(lua_State* L, const char* expr, int32_t * out)
{
  double d;
  int err;
  
  err = lua_numberexpr(L, expr, &d);
  if (err) {
    return err;
    
  }
  *out = (int32_t)d;
  return 0;
}

/**
Evaluates a Lua expression that results in a number.
*/
int
lua_boolexpr(lua_State* L, const char* expr, bool * out)
{

  int err;
  std::ostringstream oss;

  if (!L) {
    return -1;
  }
  if (!expr) {
    return -1;
  }
  if (!out) {
    return -1;
  }

  oss << "evalExpr=";
  oss << expr;

  /* return  LUA_OK=0 for success */
  err = luaL_dostring(L, oss.str().c_str());
  if (err) {
    return err;
  }
  /* no check the return value */
  lua_getglobal(L, "evalExpr");
  err = -1;
  if (lua_isboolean(L, -1))
  {
    *out = (bool)lua_toboolean(L, -1);
    err = 0;
  }
  /* remove lua_getglobal value */
  lua_pop(L, 1);
  return err;
}