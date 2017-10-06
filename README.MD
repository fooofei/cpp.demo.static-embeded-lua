
# cpp static embeded lua [![Build Status](https://travis-ci.org/fooofei/cpp_static_embeded_lua.svg?branch=master)](https://travis-ci.org/fooofei/cpp_static_embeded_lua)

A way to use config file in c++.

use lua to read the script config file.

not use executable lua, luac.

lua is static linked in c++ project.

the lua source code is download from https://www.lua.org/ftp/lua-5.3.4.tar.gz


## usage


1/3 sync the code, or up the latest version of lua

2/3 if update the lua source code, run `python make_incldues` to update include files.

3/3 include the cmake files.

how to include? 
see https://github.com/fooofei/cpp_notes/blob/master/CMakeListsDoc.txt
`## add other library for static link`


## note

- you can use dynamic insert in lua script
- you can use if in lua script
- the raw string encoding on Windows is mbcs, I supply the method string.mbcs2utf8()
to convert mbcs encoding to utf8 encoding
- you can use os.getenv() in lua script


### get current directory
```lua
is_on_platform_windows=(package.config:sub(1,1)=="\\")
-- `S` means only return source,short_src field and etc.
-- path is slash-ended, such as /media/vvv/
local path_directory_current_script = debug.getinfo(1,"S").source:match[[^@?(.*[\/])[^\/]-$]]
local path_directory_current_script_utf8=path_directory_current_script
if(is_platform_windows) then
  path_directory_current_script_utf8=string.mbcs2utf8(path_directory_current_script)
end
```