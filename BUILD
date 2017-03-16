licenses(["notice"])

cc_library(
  name = "ubus++",
  srcs = [
    "src/UBus.cpp",
    ],
  hdrs = [
    "src/UBus.h",
    "src/json.hpp",
    ],
  includes = [
    "src/",
    ],
  deps = [
    "//external:libubox",
    "//external:libubus",
    ],
  copts = [
    "--std=c++11",
    ],
  linkopts = [
    "-lm",
    "-lpthread",
    ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "main",
  srcs = [
    "src/main.cpp",
    ],
  deps = [
    ":ubus++",
    ],
  copts = [
    "--std=c++11",
    ],
  visibility = ["//visibility:public"],
)
