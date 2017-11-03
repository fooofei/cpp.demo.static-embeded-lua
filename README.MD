
# cpp static embeded lua [![Build Status](https://travis-ci.org/fooofei/cpp_static_embeded_lua.svg?branch=master)](https://travis-ci.org/fooofei/cpp_static_embeded_lua)

A way to use config file in c++, also you can use `.ini` as config file.

Use lua script language to read the config file.

This solution not use the executable `lua`, `luac`.

The lua source code is static linked into C++ project, not have the binary compatible problem, it will be compile/link with the source code everytime.

The lua source code is download from https://www.lua.org/ftp/lua-5.3.4.tar.gz

Here is an article for why use embeded script language lua for parse config file [Embedded Scripting Languages](https://accu.org/index.php/journals/351)https://accu.org/index.php/journals/351

## usage


1/3 sync(download) the code, and you can up the latest version of lua

2/3 if you update the lua source code, run `python make_incldues.py` to update lua include files.

3/3 include the cmake files.

how to include? 
see https://github.com/fooofei/cpp_notes/blob/master/CMakeListsDoc.txt
`## add other library for static link`


## note

- the advantage of use lua script as config file is you can use dynamic insert
- the advantage of use lua script as config file is you can use `if` statement
- the raw string encoding on Windows is mbcs, I supply the method string.mbcs2utf8()
to convert mbcs encoding to utf8 encoding
- the advantage of use lua script as config file is you can use built-in function such as  `os.getenv()` in lua script


### how to get current directory in lua script ?
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

## the risk of security
not checked