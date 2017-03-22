workspace(
  name = "ubus_cpp",
)

new_http_archive(
    name = "org_linaro_components_toolchain_gcc_6_2",
    build_file = "compilers/linaro_linux_gcc_6.2.BUILD",
    strip_prefix = "gcc-linaro-6.2.1-2016.11-x86_64_arm-linux-gnueabi",
    url = "https://releases.linaro.org/components/toolchain/binaries/6.2-2016.11/arm-linux-gnueabi/gcc-linaro-6.2.1-2016.11-x86_64_arm-linux-gnueabi.tar.xz",
)

new_git_repository(
  name = "com_github_json_c",
  remote = "https://github.com/json-c/json-c.git",
  commit = "82f5a4ab2969c9b413d53dcbe80a7a09fc05d2c9",
  build_file = "third_party/json.BUILD",
)

bind(
  name = "json_c",
  actual = "@com_github_json_c//:json_c"
)

new_git_repository(
  name = "org_openwrt_libubox",
  remote = "http://gitlab.tothtecnologia.com.br/lifetouch17/libubox.git",
  commit = "5f9f678701bd0a9f8674010ea2cdf89ac01b2aff",
#  commit = "96305a3cafcc9c0df7f189567671bb26ce3eb129",
  build_file = "third_party/libubox.BUILD",
)

bind(
  name = "libubox",
  actual = "@org_openwrt_libubox//:libubox",
)

new_git_repository(
  name = "org_openwrt_ubus",
  remote = "https://git.openwrt.org/project/ubus.git",
  commit = "34c6e818e431cc53478a0f7c7c1eca07d194d692",
  build_file = "third_party/ubus.BUILD",
)

bind(
  name = "libubus",
  actual = "@org_openwrt_ubus//:libubus",
)

