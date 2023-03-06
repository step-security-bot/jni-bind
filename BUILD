package(licenses = ["notice"])

filegroup(
    name = "headers_for_export",
    srcs = glob(
        ["**/*.h"],
        exclude = [
            "jni_bind_release.h",
            "jni_bind_release_for_testing.h",
            ":jni_bind_release_target",
        ],
    ),
)

exports_files(["LICENSE"])

################################################################################
# JNI Bind
#
# Depend on this target to include JNI Bind in your own target.
# For further documentation see https://github.com/google/jni-bind.
################################################################################
cc_library(
    name = "jni_bind",
    hdrs = ["jni_bind.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":jni_dep",
        "//class_defs:java_lang_classes",
        "//class_defs:java_util_classes",
        "//implementation:array",
        "//implementation:array_type_conversion",
        "//implementation:array_view",
        "//implementation:class",
        "//implementation:class_loader",
        "//implementation:constructor",
        "//implementation:corpus",
        "//implementation:corpus_tag",
        "//implementation:field",
        "//implementation:global_class_loader",
        "//implementation:global_object",
        "//implementation:global_string",
        "//implementation:id",
        "//implementation:jni_type",
        "//implementation:jvm",
        "//implementation:jvm_ref",
        "//implementation:local_array",
        "//implementation:local_array_string",
        "//implementation:local_class_loader",
        "//implementation:local_object",
        "//implementation:local_string",
        "//implementation:method",
        "//implementation:no_idx",
        "//implementation:params",
        "//implementation:promotion_mechanics",
        "//implementation:return",
        "//implementation:selector_static_info",
        "//implementation:static",
        "//implementation:static_ref",
        "//implementation:string_ref",
        "//implementation:supported_class_set",
    ],
)

# Intentionally placed at root because of issues in Bazel.
cc_library(
    name = "jni_dep",
    srcs = [
        "@local_jdk//:jni_header",
        "@local_jdk//:jni_md_header-linux",
    ],
    hdrs = ["jni_dep.h"],
    includes = [
        "external/local_jdk/include",
        "external/local_jdk/include/linux",
    ],
    visibility = [":__subpackages__"],
)

################################################################################
# Testing Targets.
################################################################################
cc_library(
    name = "jni_test",
    testonly = 1,
    hdrs = ["jni_test.h"],
    visibility = [":__subpackages__"],
    deps = [
        ":jni_bind",
        ":jni_dep",
        ":mock_jni_env",
        ":mock_jvm",
        "//implementation:fake_test_constants",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "mock_jni_env",
    testonly = 1,
    hdrs = ["mock_jni_env.h"],
    visibility = [":__subpackages__"],
    deps = [
        "//:jni_dep",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "mock_jvm",
    testonly = 1,
    hdrs = ["mock_jvm.h"],
    visibility = [":__subpackages__"],
    deps = [
        "//:jni_dep",
        "@googletest//:gtest_main",
    ],
)

################################################################################
# Release targets.
################################################################################

filegroup(
    name = "jni_bind_decorative_text",
    srcs = [
        "jni_bind_release_leader.inc",
        "jni_bind_release_trailer.inc",
    ],
    data = [
        "jni_bind_release_leader.inc",
        "jni_bind_release_trailer.inc",
    ],
)
