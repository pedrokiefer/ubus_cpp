licenses(["notice"])

cc_library(
  name = "libubox",
  srcs = [
    "libubox/avl.c",
    "libubox/avl-cmp.c",
    "libubox/blob.c",
    "libubox/blobmsg.c",
    "libubox/uloop.c",
    "libubox/usock.c",
    "libubox/ustream.c",
    "libubox/ustream-fd.c",
    "libubox/vlist.c",
    "libubox/utils.c",
    "libubox/safe_list.c",
    "libubox/runqueue.c",
    "libubox/md5.c",
    "libubox/kvlist.c",
    "libubox/ulog.c",
    "libubox/base64.c",
    ],
  hdrs = [
    "libubox/avl.h",
    "libubox/avl-cmp.h",
    "libubox/blob.h",
    "libubox/blobmsg.h",
    "libubox/uloop.h",
    "libubox/usock.h",
    "libubox/ustream.h",
    "libubox/vlist.h",
    "libubox/utils.h",
    "libubox/safe_list.h",
    "libubox/runqueue.h",
    "libubox/md5.h",
    "libubox/list.h",
    "libubox/kvlist.h",
    "libubox/ulog.h",
    ],
  textual_hdrs = [
    "libubox/uloop-epoll.c",
    "libubox/uloop-kqueue.c",
    ],
  includes = [
    ".",
    ],
  copts = [
    "--std=gnu99",
    ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "blobmsg_json",
  srcs = [
    "libubox/blobmsg_json.c",
    ],
  hdrs = [
    "libubox/blobmsg_json.h",
    ],
  deps = [
    ":libubox",
    "//third_party/json:json-c",
    ],
  copts = [
    "--std=gnu99",
    "-DJSONC",
    ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "jshn",
  srcs = [
    "libubox/jshn.c",
  ],
  deps = [
    ":blobmsg_json",
  ],
  copts = [
    "--std=gnu99",
    "-DJSONC",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "json_script",
  srcs = [
    "libubox/json_script.c",
    ],
  hdrs = [
    "libubox/json_script.h",
    ],
  deps = [
    ":libubox",
    "//json:json-c",
    ],
  copts = [
    "--std=gnu99",
    "-DJSONC",
    ],
  visibility = ["//visibility:public"],
)

filegroup(
  name = "jshn_script",
  srcs = ["libubox/sh/jshn.sh"],
  visibility = ["//visibility:public"],
)

