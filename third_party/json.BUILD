licenses(["notice"])

genrule(
    name = "json_config",
    outs = ["json_config.h"],
    cmd = """
cat > $@ <<"EOF"
/* json_config.h.  Generated from json_config.h.in by configure.  */

/* Define to 1 if you have the <inttypes.h> header file. */
#define JSON_C_HAVE_INTTYPES_H 1
EOF"""
)

genrule(
    name = "config",
    outs = ["config.h"],
    cmd = """
cat > $@ <<"EOF"
#define HAVE_DECL_INFINITY 1
#define HAVE_DECL_ISINF 1
#define HAVE_DECL_ISNAN 1
#define HAVE_DECL_NAN 1
#define HAVE_DECL__FINITE 0
#define HAVE_DECL__ISNAN 0
#define HAVE_DLFCN_H 1
#define HAVE_ENDIAN_H 1
#define HAVE_FCNTL_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIMITS_H 1
#define HAVE_LOCALE_H 1
#define HAVE_MEMORY_H 1
#define HAVE_OPEN 1
#define HAVE_REALLOC 1
#define HAVE_SETLOCALE 1
#define HAVE_SNPRINTF 1
#define HAVE_STDARG_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRCASECMP 1
#define HAVE_STRDUP 1
#define HAVE_STRERROR 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_STRNCASECMP 1
#define HAVE_SYSLOG_H 1
#define HAVE_SYS_CDEFS_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define __USE_MISC 1
#define HAVE_UNISTD_H 1
#define HAVE_VASPRINTF 1
#define HAVE_VPRINTF 1
#define HAVE_VSNPRINTF 1
#define HAVE_VSYSLOG 1
#define JSON_C_HAVE_INTTYPES_H 1
#define PACKAGE "json-c"
#define PACKAGE_BUGREPORT "json-c@googlegroups.com"
#define PACKAGE_NAME "json-c"
#define PACKAGE_STRING "json-c 0.12.99"
#define PACKAGE_TARNAME "json-c"
#define PACKAGE_URL ""
#define PACKAGE_VERSION "0.12.99"
#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define SIZEOF_SIZE_T 8
#define STDC_HEADERS 1
#define VERSION "0.12.99"
#include <stdint.h>
EOF"""
)

cc_library(
    name = "hdrs",
    hdrs = [
        "arraylist.h",
        "bits.h",
        "debug.h",
        "json.h",
        "json_c_version.h",
        "json_inttypes.h",
        "json_object.h",
        "json_object_iterator.h",
        "json_pointer.h",
        "json_tokener.h",
        "json_util.h",
        "linkhash.h",
        "vasprintf_compat.h",
        "strdup_compat.h",
        "math_compat.h",
        "printbuf.h",
        "random_seed.h",
    ],
)

cc_library(
    name = "json_c",
    srcs = [
        "arraylist.c",
        "debug.c",
        "json_c_version.c",
        "json_object.c",
        "json_object_iterator.c",
        "json_object_private.h",
        "json_tokener.c",
        "json_util.c",
        "linkhash.c",
        "printbuf.c",
        "random_seed.c",
    ],
    hdrs = [
        "arraylist.h",
        "bits.h",
        "debug.h",
        "json.h",
        "json_c_version.h",
        "json_inttypes.h",
        "json_object.h",
        "json_object_iterator.h",
        "json_tokener.h",
        "json_util.h",
        "json_pointer.h",
        "linkhash.h",
        "math_compat.h",
        "printbuf.h",
        "strdup_compat.h",
        "vasprintf_compat.h",
        "random_seed.h",
        ":config",
        ":json_config",
    ],
    copts = [
        "-std=c99",
        "-D_GNU_SOURCE",
        "-D_REENTRANT",
        "-DHAVE_CONFIG_H",
    ],
    linkopts = [ "-lc" ],
    deps = [ ":hdrs" ],
    visibility = ["//visibility:public"],
)
