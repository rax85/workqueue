cc_library(
    name = "workqueue",
    srcs = ["workqueue.cc"],
    hdrs = ["workqueue.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "workqueue_test",
    srcs = ["workqueue_test.cc"],
    deps = [
        ":workqueue",
        "@com_google_googletest//:gtest_main",
    ]
)