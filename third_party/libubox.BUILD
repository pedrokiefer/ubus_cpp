licenses(["notice"])

cc_library(
    name = "libubox",
    hdrs = [
        "avl.h",
        "avl-cmp.h",
        "blob.h",
        "blobmsg.h",
        "blobmsg_json.h",
        "json_script.h",
        "kvlist.h",
        "list.h",
        "md5.h",
        "runqueue.h",
        "safe_list.h",
        "ulog.h",
        "uloop.h",
        "usock.h",
        "ustream.h",
        "utils.h",
        "vlist.h",
    ],
    deps = [
        ":blobmsg_json",
        ":libubox_impl",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libubox_impl",
    srcs = [
        "avl.c",
        "avl.h",
        "avl-cmp.c",
        "avl-cmp.h",
        "base64.c",
        "blob.c",
        "blob.h",
        "blobmsg.c",
        "blobmsg.h",
        "kvlist.c",
        "kvlist.h",
        "list.h",
        "md5.c",
        "md5.h",
        "runqueue.c",
        "runqueue.h",
        "safe_list.c",
        "safe_list.h",
        "ulog.c",
        "ulog.h",
        "uloop.c",
        "uloop.h",
        "usock.c",
        "usock.h",
        "ustream.c",
        "ustream.h",
        "ustream-fd.c",
        "utils.c",
        "utils.h",
        "vlist.c",
        "vlist.h",
    ],
    copts = [
        "--std=gnu99",
    ],
    textual_hdrs = [
        "uloop-epoll.c",
        "uloop-kqueue.c",
    ],
    visibility = ["//visibility:private"],
)

cc_library(
    name = "blobmsg_json",
    srcs = [
        "blobmsg_json.c",
    ],
    hdrs = [
        "blobmsg_json.h",
    ],
    copts = [
        "--std=gnu99",
        "-DJSONC",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":libubox_impl",
        "@com_github_json_c//:json_c",
    ],
)

cc_binary(
    name = "jshn",
    srcs = [
        "jshn.c",
    ],
    copts = [
        "--std=gnu99",
        "-DJSONC",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":blobmsg_json",
    ],
)

cc_library(
    name = "json_script",
    srcs = [
        "json_script.c",
    ],
    hdrs = [
        "json_script.h",
    ],
    copts = [
        "--std=gnu99",
        "-DJSONC",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":libubox_impl",
        "@com_github_json_c//:json_c",
    ],
)

filegroup(
    name = "jshn_script",
    srcs = ["sh/jshn.sh"],
    visibility = ["//visibility:public"],
)
