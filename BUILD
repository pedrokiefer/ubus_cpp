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
    "//third_party/libubox:libubox",
    "//third_party/libubox:blobmsg_json",
    "//third_party/ubus:libubus",
    ],
  copts = [
    "--std=c++11",
    ],
  linkopts = [
    "-lm",
    ],
  visibility = ["//visibility:public"],
)
