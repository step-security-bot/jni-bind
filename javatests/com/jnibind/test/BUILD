licenses(["notice"])

################################################################################
# Array Test: Methods rank 1.
################################################################################
cc_library(
    name = "array_test_method_rank_1_jni_impl",
    testonly = 1,
    srcs = ["array_test_method_rank_1_jni.cc"],
    deps = [
        ":object_test_helper_jni",
        "//:jni_bind",
    ],
    alwayslink = True,
)

cc_binary(
    name = "libarray_test_method_rank_1_jni.so",
    testonly = 1,
    linkshared = True,
    deps = [":array_test_method_rank_1_jni_impl"],
)

java_test(
    name = "ArrayTestMethodRank1",
    testonly = 1,
    srcs = ["ArrayTestMethodRank1.java"],
    data = [":libarray_test_method_rank_1_jni.so"],
    jvm_flags = ["-Djava.library.path=./javatests/com/jnibind/test"],
    deps = [
        ":object_test_helper",
        "@maven//:com_google_truth_truth_1_1",
    ],
)

################################################################################
# Context Test.
################################################################################
cc_library(
    name = "context_test_jni_impl",
    srcs = ["context_test_jni.cc"],
    deps = [
        ":object_test_helper_jni",
        "//:jni_bind",
    ],
    alwayslink = True,
)

cc_binary(
    name = "libcontext_test_jni.so",
    linkshared = True,
    deps = [":context_test_jni_impl"],
)

java_test(
    name = "ContextTest",
    testonly = 1,
    srcs = ["ContextTest.java"],
    data = [":libcontext_test_jni.so"],
    jvm_flags = ["-Djava.library.path=./javatests/com/jnibind/test"],
    deps = [
        ":object_test_helper",
        "@maven//:com_google_truth_truth_1_1",
        "@maven//:junit_junit_4_13_1",
    ],
)

################################################################################
# Field Test.
################################################################################
cc_library(
    name = "field_test_jni_impl",
    testonly = 1,
    srcs = ["field_test_jni.cc"],
    deps = [
        ":object_test_helper_jni",
        "//:jni_bind",
    ],
    alwayslink = True,
)

cc_binary(
    name = "libfield_test_jni.so",
    testonly = 1,
    linkshared = True,
    deps = [":field_test_jni_impl"],
)

java_test(
    name = "FieldTest",
    testonly = 1,
    srcs = [
        "FieldTest.java",
        "FieldTestHelper.java",
    ],
    data = [":libfield_test_jni.so"],
    jvm_flags = ["-Djava.library.path=./javatests/com/jnibind/test"],
    deps = [
        "@maven//:com_google_truth_truth_1_1",
        "@maven//:junit_junit_4_13_1",
    ],
)

################################################################################
# Global Object Tests.
################################################################################
cc_library(
    name = "global_object_test_jni_impl",
    testonly = 1,
    srcs = ["global_object_test_jni.cc"],
    deps = [
        ":object_test_helper_jni",
        "//:jni_bind",
    ],
    alwayslink = True,
)

cc_binary(
    name = "libglobal_object_test_jni.so",
    testonly = 1,
    linkshared = True,
    deps = [":global_object_test_jni_impl"],
)

java_test(
    name = "GlobalObjectTest",
    testonly = 1,
    srcs = ["GlobalObjectTest.java"],
    data = [":libglobal_object_test_jni.so"],
    jvm_flags = ["-Djava.library.path=./javatests/com/jnibind/test"],
    deps = [
        ":object_test_helper",
        "@maven//:com_google_truth_truth_1_1",
        "@maven//:junit_junit_4_13_1",
    ],
)

################################################################################
# Local Object Tests.
################################################################################
cc_library(
    name = "local_object_test_jni_impl",
    testonly = 1,
    srcs = ["local_object_test_jni.cc"],
    deps = [
        ":object_test_helper_jni",
        "//:jni_bind",
    ],
    alwayslink = True,
)

cc_binary(
    name = "liblocal_object_test_jni.so",
    testonly = 1,
    linkshared = True,
    deps = [":local_object_test_jni_impl"],
)

java_test(
    name = "LocalObjectTest",
    testonly = 1,
    srcs = ["LocalObjectTest.java"],
    data = [":liblocal_object_test_jni.so"],
    jvm_flags = ["-Djava.library.path=./javatests/com/jnibind/test"],
    deps = [
        ":object_test_helper",
        "@maven//:com_google_truth_truth_1_1",
        "@maven//:junit_junit_4_13_1",
    ],
)

################################################################################
# Method Test.
################################################################################
cc_library(
    name = "method_test_jni_impl",
    testonly = 1,
    srcs = ["method_test_jni.cc"],
    deps = [
        ":object_test_helper_jni",
        "//:jni_bind",
    ],
    alwayslink = True,
)

cc_binary(
    name = "libmethod_test_jni.so",
    testonly = 1,
    linkshared = True,
    deps = [":method_test_jni_impl"],
)

java_test(
    name = "MethodTest",
    testonly = 1,
    srcs = [
        "MethodTest.java",
        "MethodTestHelper.java",
    ],
    data = [":libmethod_test_jni.so"],
    jvm_flags = ["-Djava.library.path=./javatests/com/jnibind/test"],
    deps = [
        "@maven//:com_google_truth_truth_1_1",
        "@maven//:junit_junit_4_13_1",
        "@maven//:org_mockito_mockito_core_2_28_2",
    ],
)

################################################################################
# ObjectTestHelper (used as a return value for testing).
################################################################################
java_library(
    name = "object_test_helper",
    srcs = ["ObjectTestHelper.java"],
)

cc_library(
    name = "object_test_helper_jni",
    hdrs = ["object_test_helper_jni.h"],
    deps = ["//:jni_bind"],
)

#################################################################################
# Statics Test.
#################################################################################
cc_library(
    name = "static_test_jni_impl",
    testonly = 1,
    srcs = ["static_test_jni.cc"],
    deps = [
        ":object_test_helper_jni",
        "//:jni_bind",
    ],
    alwayslink = True,
)

cc_binary(
    name = "libstatic_test_jni.so",
    testonly = 1,
    linkshared = True,
    deps = [":static_test_jni_impl"],
)

java_test(
    name = "StaticTest",
    testonly = 1,
    srcs = [
        "StaticTest.java",
        "StaticTestHelper.java",
    ],
    data = [":libstatic_test_jni.so"],
    jvm_flags = ["-Djava.library.path=./javatests/com/jnibind/test"],
    deps = [
        ":object_test_helper",
        "@maven//:com_google_truth_truth_1_1",
        "@maven//:junit_junit_4_13_1",
    ],
)

#################################################################################
# String Test.
#################################################################################
cc_library(
    name = "string_test_jni_impl",
    testonly = 1,
    srcs = ["string_test_jni.cc"],
    deps = [
        ":object_test_helper_jni",
        "//:jni_bind",
    ],
    alwayslink = True,
)

cc_binary(
    name = "libstring_test_jni.so",
    testonly = 1,
    linkshared = True,
    deps = [":string_test_jni_impl"],
)

java_test(
    name = "StringTest",
    testonly = 1,
    srcs = [
        "StringTest.java",
        "StringTestHelper.java",
    ],
    data = [":libstring_test_jni.so"],
    jvm_flags = ["-Djava.library.path=./javatests/com/jnibind/test"],
    deps = [
        "@maven//:com_google_truth_truth_1_1",
        "@maven//:junit_junit_4_13_1",
        "@maven//:org_mockito_mockito_core_2_28_2",
    ],
)
