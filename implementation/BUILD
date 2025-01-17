# Do not depend on any targets in this package.  Instead, depend //third_party/jni_wrapper:jni_bind
package(
    default_visibility = ["//:__subpackages__"],
    licenses = ["notice"],
)

filegroup(
    name = "headers_for_export",
    srcs = glob(["**/*.h"]),
)

cc_library(
    name = "array",
    hdrs = ["array.h"],
    deps = [
        ":array_type_conversion",
        ":class",
        ":object",
        ":return",
        "//:jni_dep",
        "//metaprogramming:contains",
        "//metaprogramming:type_to_type_map",
    ],
)

cc_library(
    name = "array_ref",
    hdrs = ["array_ref.h"],
    deps = [
        ":array",
        ":array_type_conversion",
        ":array_view",
        ":class",
        ":default_class_loader",
        ":jni_type",
        ":ref_base",
        "//:jni_dep",
        "//implementation/jni_helper:jni_array_helper",
    ],
)

cc_test(
    name = "array_test",
    srcs = ["array_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "array_type_conversion",
    hdrs = ["array_type_conversion.h"],
    deps = [
        "//:jni_dep",
        "//metaprogramming:type_to_type_map",
    ],
)

cc_test(
    name = "array_type_conversion_test",
    srcs = ["array_type_conversion_test.cc"],
    deps = [
        "//:jni_bind",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "array_view",
    hdrs = ["array_view.h"],
    deps = [
        ":array_type_conversion",
        "//:jni_dep",
        "//implementation/jni_helper:jni_array_helper",
    ],
)

cc_test(
    name = "array_view_test",
    srcs = ["array_view_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "class",
    hdrs = ["class.h"],
    deps = [
        ":constructor",
        ":field",
        ":method",
        ":no_idx",
        ":object",
        ":static",
        "//:jni_dep",
        "//metaprogramming:all_unique",
        "//metaprogramming:base_filter",
    ],
)

cc_library(
    name = "class_ref",
    hdrs = ["class_ref.h"],
    deps = [
        ":class",
        ":class_loader",
        ":default_class_loader",
        ":jni_type",
        ":jvm",
        ":method",
        "//:jni_dep",
        "//class_defs:java_lang_classes",
        "//implementation/jni_helper",
        "//implementation/jni_helper:invoke",
        "//metaprogramming:double_locked_value",
    ],
)

cc_test(
    name = "class_test",
    srcs = ["class_test.cc"],
    deps = [
        "//:jni_bind",
        "//:jni_test",
        "//:mock_jni_env",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "class_loader",
    hdrs = ["class_loader.h"],
    deps = [
        ":class",
        ":default_class_loader",
        ":no_idx",
        ":object",
        ":supported_class_set",
        "//class_defs:java_lang_classes",
        "//metaprogramming:all_unique",
        "//metaprogramming:base_filter",
        "//metaprogramming:modified_max",
    ],
)

cc_test(
    name = "class_loader_test",
    srcs = ["class_loader_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "class_loader_ref",
    hdrs = [
        "class_loader_ref.h",
    ],
    deps = [
        ":class",
        ":class_loader",
        ":default_class_loader",
        ":global_object",
        ":jni_type",
        ":jvm_ref",
        ":local_object",
        ":local_string",
        ":method",
        ":method_ref",
        ":object_ref",
        ":params",
        ":return",
        "//:jni_dep",
        "//class_defs:java_lang_classes",
        "//implementation/jni_helper:jni_env",
        "//metaprogramming:contains",
        "//metaprogramming:queryable_map",
    ],
)

cc_test(
    name = "class_loader_ref_test",
    srcs = ["class_loader_ref_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "constructor",
    hdrs = ["constructor.h"],
    deps = [
        ":method",
        ":params",
        ":return",
        "//implementation/jni_helper",
    ],
)

cc_test(
    name = "constructor_test",
    srcs = ["constructor_test.cc"],
    deps = [
        "//:jni_bind",
        "//:jni_test",
        "//:mock_jni_env",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "corpus",
    hdrs = ["corpus.h"],
    deps = [
        ":corpus_tag",
        "//metaprogramming:concatenate",
        "//metaprogramming:detect",
    ],
)

cc_library(
    name = "corpus_tag",
    hdrs = ["corpus_tag.h"],
    deps = [
        "//metaprogramming:concatenate",
        "//metaprogramming:detect",
    ],
)

cc_test(
    name = "corpus_test",
    srcs = ["corpus_test.cc"],
    deps = [
        ":corpus",
        ":corpus_tag",
        "//metaprogramming:detect",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "default_class_loader",
    hdrs = ["default_class_loader.h"],
    deps = [
        ":no_idx",
        "//metaprogramming:modified_max",
    ],
)

cc_library(
    name = "fake_test_constants",
    testonly = True,
    hdrs = ["fake_test_constants.h"],
    deps = ["//:jni_dep"],
)

cc_library(
    name = "field",
    hdrs = ["field.h"],
    deps = [":params"],
)

cc_library(
    name = "field_ref",
    hdrs = ["field_ref.h"],
    deps = [
        ":class_ref",
        ":field_selection",
        ":id",
        ":id_type",
        ":proxy",
        "//:jni_dep",
        "//implementation/jni_helper",
        "//implementation/jni_helper:field_value_getter",
        "//implementation/jni_helper:static_field_value",
        "//metaprogramming:double_locked_value",
        "//metaprogramming:optional_wrap",
        "//metaprogramming:queryable_map",
    ],
)

cc_test(
    name = "field_ref_test",
    srcs = ["field_ref_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "field_selection",
    hdrs = ["field_selection.h"],
    deps = [
        ":id",
        ":name_constants",
        ":object",
        ":selector_static_info",
        "//implementation/jni_helper:jni_typename_to_string",
        "//metaprogramming:string_concatenate",
    ],
)

cc_library(
    name = "global_class_loader",
    hdrs = ["global_class_loader.h"],
    deps = [
        ":class_loader",
        ":class_loader_ref",
        ":jvm",
        "//:jni_dep",
        "//implementation/jni_helper",
    ],
)

cc_library(
    name = "global_object",
    hdrs = ["global_object.h"],
    deps = [
        ":class",
        ":jni_type",
        ":local_object",
        ":object_ref",
        ":promotion_mechanics",
        "//:jni_dep",
        "//implementation/jni_helper",
    ],
)

cc_test(
    name = "global_object_test",
    srcs = ["global_object_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "global_string",
    hdrs = ["global_string.h"],
    deps = [
        ":global_object",
        ":local_string",
        ":promotion_mechanics",
        ":ref_base",
        ":string_ref",
        "//:jni_dep",
        "//class_defs:java_lang_classes",
    ],
)

cc_library(
    name = "id",
    hdrs = ["id.h"],
    deps = [
        ":array",
        ":class",
        ":field",
        ":id_type",
        ":name_constants",
        ":no_idx",
        ":proxy_convenience_aliases",
        ":selector_static_info",
        ":signature",
    ],
)

cc_test(
    name = "id_test",
    srcs = ["id_test.cc"],
    deps = [
        "//:jni_bind",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "id_type",
    hdrs = ["id_type.h"],
)

cc_library(
    name = "jni_type",
    hdrs = ["jni_type.h"],
    deps = [
        ":array",
        ":array_type_conversion",
        ":class",
        ":class_loader",
        ":default_class_loader",
        ":jvm",
        ":no_idx",
        "//metaprogramming:vals_equal",
    ],
)

cc_test(
    name = "jni_type_test",
    srcs = ["jni_type_test.cc"],
    deps = [
        ":jni_type",
        "//:jni_bind",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "jvm",
    hdrs = ["jvm.h"],
    deps = [
        ":class",
        ":class_loader",
        "//:jni_dep",
        "//implementation/jni_helper:jni_env",
    ],
)

cc_library(
    name = "jvm_ref",
    hdrs = ["jvm_ref.h"],
    deps = [
        ":class",
        ":class_loader",
        ":class_ref",
        ":default_class_loader",
        ":field_ref",
        ":jni_type",
        ":jvm",
        ":method_ref",
        "//:jni_dep",
        "//metaprogramming:double_locked_value",
        "//metaprogramming:function_traits",
    ],
)

cc_test(
    name = "jvm_test",
    srcs = ["jvm_test.cc"],
    deps = [
        "//:jni_bind",
        "//:jni_test",
        "//implementation/jni_helper",
        "//implementation/jni_helper:jni_env",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "local_array",
    hdrs = ["local_array.h"],
    deps = [
        ":array",
        ":array_ref",
        ":class",
        ":class_ref",
        ":default_class_loader",
        ":jni_type",
        ":jvm",
        ":object",
        "//:jni_dep",
        "//implementation/jni_helper",
        "//implementation/jni_helper:jni_array_helper",
    ],
)

cc_library(
    name = "local_array_string",
    hdrs = ["local_array_string.h"],
    deps = [
        ":array",
        ":array_ref",
        ":class",
        ":class_ref",
        ":default_class_loader",
        ":jni_type",
        ":jvm",
        ":local_array",
        ":local_object",
        ":local_string",
        ":object",
        "//:jni_dep",
        "//implementation/jni_helper",
        "//implementation/jni_helper:jni_array_helper",
    ],
)

cc_test(
    name = "local_array_test",
    srcs = ["local_array_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "local_array_field_test",
    srcs = ["local_array_field_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "local_class_loader",
    hdrs = ["local_class_loader.h"],
    deps = [
        ":class_loader",
        ":class_loader_ref",
        ":jvm",
        ":jvm_ref",
        "//:jni_dep",
    ],
)

cc_library(
    name = "local_object",
    hdrs = ["local_object.h"],
    deps = [
        ":class",
        ":class_loader",
        ":jni_type",
        ":jvm",
        ":jvm_ref",
        ":object_ref",
        ":promotion_mechanics",
        "//:jni_dep",
        "//implementation/jni_helper",
    ],
)

cc_test(
    name = "local_object_test",
    srcs = ["local_object_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "local_string",
    hdrs = ["local_string.h"],
    deps = [
        ":local_object",
        ":promotion_mechanics",
        ":ref_base",
        ":string_ref",
        "//:jni_dep",
        "//class_defs:java_lang_classes",
        "//implementation/jni_helper",
    ],
)

cc_library(
    name = "method",
    hdrs = ["method.h"],
    deps = [":params"],
)

cc_library(
    name = "method_ref",
    hdrs = ["method_ref.h"],
    deps = [
        ":class_loader",
        ":class_ref",
        ":id_type",
        ":jni_type",
        ":method",
        ":params",
        ":proxy",
        ":proxy_definitions",
        ":proxy_definitions_array",
        ":proxy_definitions_string",
        ":ref_base",
        ":return",
        ":signature",
        ":void",
        "//:jni_dep",
        "//implementation/jni_helper",
        "//implementation/jni_helper:invoke",
        "//implementation/jni_helper:invoke_static",
        "//implementation/jni_helper:jni_env",
        "//metaprogramming:double_locked_value",
        "//metaprogramming:invocable_map",
        "//metaprogramming:optional_wrap",
        "//metaprogramming:string_concatenate",
    ],
)

cc_test(
    name = "method_ref_test",
    srcs = ["method_ref_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "method_selection",
    hdrs = ["method_selection.h"],
    deps = [
        ":array",
        ":array_ref",
        ":default_class_loader",
        ":id",
        ":method_ref",
        ":no_idx",
        ":proxy",
        ":selector_static_info",
        "//implementation/jni_helper:jni_typename_to_string",
        "//metaprogramming:call",
        "//metaprogramming:concatenate",
        "//metaprogramming:invoke",
        "//metaprogramming:min_max",
        "//metaprogramming:n_bit_sequence",
        "//metaprogramming:per_element",
        "//metaprogramming:reduce",
        "//metaprogramming:tuple_manipulation",
        "//metaprogramming:type_index_mask",
        "//metaprogramming:type_of_nth_element",
        "//metaprogramming:unfurl",
        "//metaprogramming:vals",
    ],
)

cc_test(
    name = "method_selection_test",
    srcs = ["method_selection_test.cc"],
    deps = [
        "//:jni_bind",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "multi_type_test",
    srcs = ["multi_type_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "name_constants",
    hdrs = ["name_constants.h"],
)

cc_test(
    name = "name_constants_test",
    srcs = ["name_constants_test.cc"],
    deps = [
        "//:jni_bind",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "no_idx",
    hdrs = ["no_idx.h"],
)

cc_library(
    name = "object",
    hdrs = ["object.h"],
)

cc_library(
    name = "object_ref",
    hdrs = ["object_ref.h"],
    deps = [
        ":array",
        ":class",
        ":class_loader",
        ":class_ref",
        ":constructor",
        ":default_class_loader",
        ":field_ref",
        ":jni_type",
        ":jvm_ref",
        ":method_ref",
        ":method_selection",
        ":proxy",
        ":ref_base",
        "//:jni_dep",
        "//implementation/jni_helper:jni_env",
        "//metaprogramming:invocable_map",
        "//metaprogramming:optional_wrap",
        "//metaprogramming:queryable_map",
        "//metaprogramming:tuple_manipulation",
    ],
)

cc_test(
    name = "overload_ref_test",
    srcs = ["overload_ref_test.cc"],
    deps = [
        "//:jni_bind",
        "//:jni_test",
        "//implementation/jni_helper",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "params",
    hdrs = ["params.h"],
    deps = [":object"],
)

cc_library(
    name = "promotion_mechanics",
    hdrs = ["promotion_mechanics.h"],
    deps = [
        "//:jni_dep",
        "//implementation/jni_helper",
    ],
)

cc_library(
    name = "proxy",
    hdrs = ["proxy.h"],
    deps = [
        ":array",
        ":class",
        ":class_loader",
        ":corpus",
        ":corpus_tag",
        ":default_class_loader",
        ":id",
        ":id_type",
        ":jvm",
        ":local_array",
        ":name_constants",
        ":object",
        ":proxy_convenience_aliases",
        ":ref_base",
        "//:jni_dep",
        "//metaprogramming:cartesian_product",
        "//metaprogramming:combine",
        "//metaprogramming:concatenate",
        "//metaprogramming:flatten",
        "//metaprogramming:invoke",
        "//metaprogramming:per_element",
        "//metaprogramming:reduce",
        "//metaprogramming:tuple_manipulation",
        "//metaprogramming:type_of_nth_element",
        "//metaprogramming:type_to_type_map",
        "//metaprogramming:unique_set",
        "//metaprogramming:unwrap",
    ],
)

cc_library(
    name = "proxy_definitions",
    hdrs = ["proxy_definitions.h"],
    deps = [
        ":array",
        ":class",
        ":class_loader",
        ":default_class_loader",
        ":id",
        ":id_type",
        ":jvm",
        ":local_array",
        ":name_constants",
        ":object",
        ":proxy",
        ":ref_base",
        "//:jni_dep",
    ],
)

cc_library(
    name = "proxy_definitions_array",
    hdrs = ["proxy_definitions_array.h"],
    deps = [
        ":default_class_loader",
        ":jvm",
        ":name_constants",
        ":proxy",
    ],
)

cc_library(
    name = "proxy_definitions_string",
    hdrs = ["proxy_definitions_string.h"],
    deps = [
        ":default_class_loader",
        ":jvm",
        ":proxy",
        ":ref_base",
        "//class_defs:java_lang_classes",
    ],
)

cc_library(
    name = "proxy_convenience_aliases",
    hdrs = ["proxy_convenience_aliases.h"],
    deps = [":id_type"],
)

cc_test(
    name = "proxy_test",
    srcs = ["proxy_test.cc"],
    deps = [
        "//:jni_bind",
        "//:jni_test",
        "//metaprogramming:concatenate",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "ref_base",
    hdrs = ["ref_base.h"],
    deps = [
        ":class",
        ":class_loader",
        "//implementation/jni_helper:jni_env",
    ],
)

cc_library(
    name = "return",
    hdrs = ["return.h"],
    deps = [":void"],
)

cc_library(
    name = "signature",
    hdrs = ["signature.h"],
    deps = [
        ":array",
        ":class",
        ":field",
        ":id_type",
        ":name_constants",
        ":no_idx",
        ":proxy_convenience_aliases",
        ":selector_static_info",
        "//metaprogramming:name_constants",
    ],
)

cc_test(
    name = "signature_test",
    srcs = ["signature_test.cc"],
    deps = [
        "//:jni_bind",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "string_ref",
    hdrs = ["string_ref.h"],
    deps = [
        ":array",
        ":class",
        ":class_loader",
        ":constructor",
        ":default_class_loader",
        ":jni_type",
        ":jvm",
        ":object_ref",
        ":ref_base",
        "//:jni_dep",
        "//class_defs:java_lang_classes",
        "//implementation/jni_helper",
        "//implementation/jni_helper:jni_env",
    ],
)

cc_library(
    name = "selector_static_info",
    hdrs = ["selector_static_info.h"],
    deps = [
        ":array",
        ":name_constants",
        ":object",
        ":return",
        ":void",
        "//implementation/jni_helper:jni_typename_to_string",
        "//metaprogramming:name_constants",
        "//metaprogramming:repeat_string",
        "//metaprogramming:string_concatenate",
    ],
)

cc_library(
    name = "static",
    hdrs = ["static.h"],
    deps = [
        ":field",
        ":method",
        ":params",
        "//metaprogramming:base_filter",
        "//metaprogramming:invocable_map",
        "//metaprogramming:queryable_map",
    ],
)

cc_library(
    name = "static_ref",
    hdrs = ["static_ref.h"],
    deps = [
        ":default_class_loader",
        ":field_ref",
        ":id",
        ":id_type",
        ":jni_type",
        ":jvm",
        ":method_selection",
        "//metaprogramming:invocable_map",
        "//metaprogramming:queryable_map",
    ],
)

cc_test(
    name = "static_ref_test",
    srcs = ["static_ref_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "string_ref_test",
    srcs = ["string_ref_test.cc"],
    deps = [
        ":fake_test_constants",
        "//:jni_bind",
        "//:jni_test",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "supported_class_set",
    hdrs = ["supported_class_set.h"],
    deps = [
        ":class",
        "//metaprogramming:all_unique",
    ],
)

cc_library(
    name = "void",
    hdrs = ["void.h"],
)
