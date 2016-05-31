licenses(["notice"])

cc_library(
  name = "json-c",
  srcs = [
    "upstream/arraylist.c",
    "upstream/debug.c",
    "upstream/json_c_version.c",
    "upstream/json_object.c",
    "upstream/json_object_iterator.c",
    "upstream/json_object_private.h",
    "upstream/json_tokener.c",
    "upstream/json_util.c",
    "upstream/linkhash.c",
    "upstream/printbuf.c",
    "upstream/random_seed.c",
    ],
  hdrs = [
    "linux/config.h",
    "linux/json_config.h",
    "upstream/bits.h",
    "upstream/arraylist.h",
    "upstream/debug.h",
    "upstream/json.h",
    "upstream/json_c_version.h",
    "upstream/json_inttypes.h",
    "upstream/json_object.h",
    "upstream/json_object_iterator.h",
    "upstream/json_tokener.h",
    "upstream/json_util.h",
    "upstream/linkhash.h",
    "upstream/printbuf.h",
    "upstream/random_seed.h",
    "upstream/math_compat.h",
    ],
  includes = [
    "upstream/",
    "linux/"
    ],
  copts = [
    "--std=gnu99",
    ],
  visibility = ["//visibility:public"],
)
