licenses(["notice"])

cc_library(
  name = "libubus",
  hdrs = [
    "libubus.h",
    "ubusmsg.h",
    "ubus_common.h",
    ],
  deps = [
    ":lubus", 
    ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "lubus",
  srcs = [
    "libubus.c",
    "libubus-io.c",
    "libubus-obj.c",
    "libubus-sub.c",
    "libubus-req.c",
    "libubus-acl.c",
    "libubus-internal.h",
    ],
  hdrs = [
    "libubus.h",
    "ubusmsg.h",
    "ubus_common.h",
    ],
  deps = [
    "@org_openwrt_libubox//:libubox",
    "@com_github_json_c//:json_c",
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
    "ubusd.c",
    "ubusd.h",
    "ubusd_id.c",
    "ubusd_id.h",
    "ubusd_obj.c",
    "ubusd_obj.h",
    "ubusd_proto.c",
    "ubusd_event.c",
    "ubusd_acl.c",
    "ubusd_acl.h",
    "ubusd_monitor.c",
    "ubus_common.h",
    "ubusmsg.h",
    ],
  deps = [
    "@org_openwrt_libubox//:libubox",
    "@com_github_json_c//:json_c",
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
    "cli.c",
    ],
  deps = [
    ":lubus",
    ],
  copts = [
    "--std=gnu99",
    ],
  visibility = ["//visibility:public"],
)

