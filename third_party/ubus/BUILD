licenses(["notice"])

cc_inc_library(
  name = "libubus",
  hdrs = [
    "upstream/libubus.h",
    "upstream/ubusmsg.h",
    "upstream/ubus_common.h",
    ],
  prefix = "upstream",
  deps = [
    ":lubus", 
    ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "lubus",
  srcs = [
    "upstream/libubus.c",
    "upstream/libubus-io.c",
    "upstream/libubus-obj.c",
    "upstream/libubus-sub.c",
    "upstream/libubus-req.c",
    "upstream/libubus-acl.c",
    "upstream/libubus-internal.h",
    ],
  hdrs = [
    "upstream/libubus.h",
    "upstream/ubusmsg.h",
    "upstream/ubus_common.h",
    ],
  deps = [
    "//third_party/libubox:libubox",
    "//third_party/json:json-c",
    ],
  includes = [
    "upstream/",
    ],
  copts = [
    "--std=gnu99",
    "-DJSONC",
    "-DUBUS_UNIX_SOCKET=\\\"/var/run/ubus.sock\\\"",
    "-DUBUS_MAX_MSGLEN=1048576",
    ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "ubusd",
  srcs = [
    "upstream/ubusd.c",
    "upstream/ubusd.h",
    "upstream/ubusd_id.c",
    "upstream/ubusd_id.h",
    "upstream/ubusd_obj.c",
    "upstream/ubusd_obj.h",
    "upstream/ubusd_proto.c",
    "upstream/ubusd_event.c",
    "upstream/ubusd_acl.c",
    "upstream/ubusd_acl.h",
    "upstream/ubusd_monitor.c",
    "upstream/ubus_common.h",
    "upstream/ubusmsg.h",
    ],
  deps = [
    "//third_party/libubox:libubox",
    "//third_party/json:json-c",
    ],
  copts = [
    "--std=gnu99",
    "-DUBUS_UNIX_SOCKET=\\\"/var/run/ubus.sock\\\"",
    "-DUBUS_MAX_MSGLEN=1048576",
    ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "ubus",
  srcs = [
    "upstream/cli.c",
    ],
  deps = [
    ":lubus",
    ],
  copts = [
    "--std=gnu99",
    ],
  visibility = ["//visibility:public"],
)

