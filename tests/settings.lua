-- lua script can use variables, strings append methods
-- is better than txt config files
a = "common_value"
is_on_platform_windows=false
if(package.config:sub(1,1)=="\\") then
  is_on_platform_windows=true
end

-- in c code, if we give luaL_dofile() a relative path, then the 
-- path_directory_current_script is a relative path, not abspath.
path_directory_current_script = debug.getinfo(1,"S").source:match[[^@?(.*[\/])[^\/]-$]]
path_directory_current_script_utf8=""
if(is_on_platform_windows) then
  path_directory_current_script_utf8=string.mbcs2utf8(path_directory_current_script)
else
  path_directory_current_script_utf8 = path_directory_current_script
end

function function_return()
  return "string_returned_from_function"
end

settings = {
  resolution = {
    width = 800,
    height = 600,
    fullscreen = true,
    --comment=""
  },
  images = {
    "C:\\carrot你好.bmp",
    "C:\\apple.bmp",
    "C:\\banana.bmp"
  },
  enum_configs={
    config_string={
      config_string1="config_string1_value",
      config_string2="config_string2_value",
      config_string_common1=a.."_append1", --append string
      config_string_common2=a.."_append2",
      config_string_format=string.format("from_string_format"),
      config_string_returned=function_return(),
    },
    config_bool={
      config_bool1=false,
      config_bool2=true,
    }
  }
}

table.insert(settings.images,"c:\\this_file_is_table_append")
