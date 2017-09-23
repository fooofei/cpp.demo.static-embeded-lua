-- lua script can use variables, strings append methods
-- is better than txt config files
a = "common_value"

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
    },
    config_bool={
      config_bool1=false,
      config_bool2=true,
    }
  }
}