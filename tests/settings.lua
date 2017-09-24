-- lua script can use variables, strings append methods
-- is better than txt config files
a = "common_value"

-- this can get path in execute by lua <script>,
-- but cannot get path in embeded c as file
function script_path()
   local str = debug.getinfo(2, "S").source:sub(2)
   return str:match("(.*/)")
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
