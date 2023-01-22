/*
 * Copyright 2021 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <memory>

#include "object_test_helper_jni.h"
#include "jni_bind.h"

using jni::Array;
using jni::ArrayView;
using jni::Class;
using jni::LocalArray;
using jni::LocalObject;
using jni::Method;
using jni::Params;
using jni::Rank;
using jni::Return;

static std::unique_ptr<jni::JvmRef<jni::kDefaultJvm>> jvm;

// clang-format off
static constexpr Class kArrayTest {
    "com/jnibind/test/ArrayTest",

    // 1D Tests.
    Method {"rJniBooleanArray", Return<void>{}, Params{jboolean{}, Array<jboolean>{}}},
    Method {"rJniByteArray", Return<void>{}, Params{jbyte{}, Array<jbyte>{}}},
    Method {"rJniCharArray", Return<void>{}, Params{jchar{}, Array<jchar>{}}},
    Method {"rJniShortArray", Return<void>{}, Params{jshort{}, Array<jshort>{}}},
    Method {"rJniIntArray", Return<void>{}, Params{int{}, Array<jint>{}}},
    Method {"rJniLongArray", Return<void>{}, Params{jlong{}, Array<jlong>{}}},
    Method {"rJniFloatArray", Return<void>{}, Params{float{}, Array<jfloat>{}}},
    Method {"rJniDoubleArray", Return<void>{}, Params{jdouble{}, Array<jdouble>{}}},
    Method {"rJniObjectArray", Return<void>{}, Params{int{}, Array{kObjectTestHelperClass}}},

    // 2D Tests.
    Method {"rJniBooleanArray2D", Return<void>{}, Params{jboolean{}, Array<jboolean, 2>{}}},
    Method {"rJniByteArray2D", Return<void>{}, Params{jbyte{}, Array<jbyte, 2>{}}},
    Method {"rJniCharArray2D", Return<void>{}, Params{jchar{}, Array<jchar, 2>{}}},
    Method {"rJniShortArray2D", Return<void>{}, Params{jshort{}, Array<jshort, 2>{}}},
    Method {"rJniIntArray2D", Return<void>{}, Params{int{}, Array<jint, 2>{}}},
    Method {"rJniLongArray2D", Return<void>{}, Params{jlong{}, Array<jlong, 2>{}}},
    Method {"rJniFloatArray2D", Return<void>{}, Params{float{}, Array<jfloat, 2>{}}},
    Method {"rJniDoubleArray2D", Return<void>{}, Params{jdouble{}, Array<jdouble, 2>{}}},
    Method {"rJniObjectArray2D", Return<void>{}, Params{int{}, Array{kObjectTestHelperClass, Rank<2>{}}}},

};

static constexpr Class kArrayTestHelper {
    "com/jnibind/test/ArrayTest",

};

// clang-format on

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* pjvm, void* reserved) {
  jvm.reset(new jni::JvmRef<jni::kDefaultJvm>(pjvm));
  return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
Java_com_jnibind_test_ArrayTest_jniTearDown(JavaVM* pjvm, void* reserved) {
  jvm = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// 1D Array Tests.
////////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeBooleanTests(
    JNIEnv* env, jclass, jobject test_fixture, jbooleanArray boolean_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jboolean> local_arr{boolean_array};
  rjni_test_helper("rJniBooleanArray", false, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniBooleanArray", false,
                   LocalArray<jboolean>{boolean_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jboolean> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = true;
    }
  }
  rjni_test_helper("rJniBooleanArray", true, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = true;
    }
  }

  // And it can be iterated over.
  for (jboolean& val : new_array.Pin(true)) {
    // Below we modify the value 2 times but with a bool there's no way,
    // so we instead just set it back.
    val = false;
  }

  rjni_test_helper("rJniBooleanArray", false, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeByteTests(
    JNIEnv* env, jclass, jobject test_fixture, jbyteArray byte_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jbyte> local_arr{byte_array};
  rjni_test_helper("rJniByteArray", jbyte{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniByteArray", jbyte{0}, LocalArray<jbyte>{byte_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jbyte> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jbyte>(i);
    }
  }
  rjni_test_helper("rJniByteArray", jbyte{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jbyte& val : new_array.Pin(true)) {
    val += 5;
  }
  rjni_test_helper("rJniByteArray", jbyte{5 + 5}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeCharTests(
    JNIEnv* env, jclass, jobject test_fixture, jcharArray char_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jchar> local_arr{char_array};
  rjni_test_helper("rJniCharArray", jchar{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniCharArray", jchar{0}, LocalArray<jchar>{char_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jchar> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jchar>(i);
    }
  }
  rjni_test_helper("rJniCharArray", jchar{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jchar& val : new_array.Pin(true)) {
    val += 5;
  }

  rjni_test_helper("rJniCharArray", jchar{5 + 5}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeShortTests(
    JNIEnv* env, jclass, jobject test_fixture, jshortArray short_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jshort> local_arr{short_array};
  rjni_test_helper("rJniShortArray", jshort{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniShortArray", jshort{0},
                   LocalArray<jshort>{short_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jshort> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jshort>(i);
    }
  }
  rjni_test_helper("rJniShortArray", jshort{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jshort& val : new_array.Pin(true)) {
    val += 5;
  }

  rjni_test_helper("rJniShortArray", jshort{5 + 5}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeIntTests(
    JNIEnv* env, jclass, jobject test_fixture, jintArray int_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jint> local_arr{int_array};
  rjni_test_helper("rJniIntArray", 0, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniIntArray", 0, LocalArray<jint>{int_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jint> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = i;
    }
  }
  rjni_test_helper("rJniIntArray", 0, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (int& val : new_array.Pin(true)) {
    val += 5;
  }

  rjni_test_helper("rJniIntArray", 5 * 2, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeLongTests(
    JNIEnv* env, jclass, jobject test_fixture, jlongArray long_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jlong> local_arr{long_array};
  rjni_test_helper("rJniLongArray", jlong{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniLongArray", jlong{0}, LocalArray<jlong>{long_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jlong> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jlong>(i);
    }
  }
  rjni_test_helper("rJniLongArray", jlong{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jlong& val : new_array.Pin(true)) {
    val += 5;
  }

  rjni_test_helper("rJniLongArray", jlong{5 * 2}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeFloatTests(
    JNIEnv* env, jclass, jobject test_fixture, jfloatArray float_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  LocalArray<jfloat> local_arr{float_array};
  rjni_test_helper("rJniFloatArray", 0.f, local_arr);

  {
    ArrayView array_view{local_arr.Pin(true)};
    for (int i = 0; i < local_arr.Length(); ++i) {
      array_view.ptr()[i] += 2.5f;
    }
  }
  rjni_test_helper("rJniFloatArray", 2.5f, local_arr);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeDoubleTests(
    JNIEnv* env, jclass, jobject test_fixture, jdoubleArray double_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jdouble> local_arr{double_array};
  rjni_test_helper("rJniDoubleArray", jdouble{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniDoubleArray", jdouble{0},
                   LocalArray<jdouble>{double_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jdouble> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jdouble>(i);
    }
  }
  rjni_test_helper("rJniDoubleArray", jdouble{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jdouble& val : new_array.Pin(true)) {
    val += 5;
  }
  rjni_test_helper("rJniDoubleArray", jdouble{5 * 2}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeObjectTests(
    JNIEnv* env, jclass, jobject test_fixture, jobjectArray object_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jobject, 1, kObjectTestHelperClass> local_arr{object_array};
  rjni_test_helper("rJniObjectArray", 0, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniObjectArray", 5,
                   LocalArray<jobject, 1, kObjectTestHelperClass>{
                       1, LocalObject<kObjectTestHelperClass>{5, 5, 5}});

  // Building a new array, and setting all the values by hand works.
  LocalObject<kObjectTestHelperClass> obj{0, 0, 0};
  LocalArray<jobject, 1, kObjectTestHelperClass> new_array{8, obj};
  {
    for (int i = 0; i < new_array.Length(); ++i) {
      new_array.Set(
          i, LocalObject<kObjectTestHelperClass>{jint{i}, jint{i}, jint{i}});
    }
  }
  rjni_test_helper("rJniObjectArray", 0, new_array);

  // You can pull the view multiple times.
  {
    for (int i = 0; i < new_array.Length(); ++i) {
      new_array.Set(i,
                    LocalObject<kObjectTestHelperClass>{2, 2, 2}(
                        "returnNewObjectWithFieldSetToSum", new_array.Get(i)));
    }
  }

  // And it can be iterated over.
  // Note: LocalObject is not a reference here, instead, the underlying jobject
  //  is being iterated over, and upcast to a LocalObject.
  // Also note: Pin is not to contiguous memory, so no copyback bool either.
  for (LocalObject<kObjectTestHelperClass> val : new_array.Pin()) {
    val["intVal1"].Set(val["intVal1"].Get() + 3);
    val["intVal2"].Set(val["intVal2"].Get() + 3);
    val["intVal3"].Set(val["intVal3"].Get() + 3);
  }

  rjni_test_helper("rJniObjectArray", 2 + 3, new_array);
}

////////////////////////////////////////////////////////////////////////////////
// 2D Array Tests.
////////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeBooleanTests2D(
    JNIEnv* env, jclass, jobject test_fixture, jobjectArray boolean_array_2D) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jboolean, 2> local_arr{boolean_array_2D};
  rjni_test_helper("rJniBooleanArray2D", true, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniBooleanArray2D", true,
                   LocalArray<jboolean, 2>{boolean_array_2D});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jboolean, 2> new_array{3, LocalArray<jboolean>{3}};
  int i = 0;
  int j = 0;
  // for (LocalArray<jboolean> arr_1d : local_arr.Pin()) {
  for (LocalArray<jboolean> arr_1d : new_array.Pin()) {
    for (jboolean& val : arr_1d.Pin()) {
      //   val = (i + j) % 2 == 0;
      LOG(ERROR) << "jif val " << val;
      j++;
    }
    i++;
  }
  // rjni_test_helper("rJniBooleanArray2D", true, new_array);

  /*
  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = true;
    }
  }

  // And it can be iterated over.
  for (jboolean& val : new_array.Pin(true)) {
    // Below we modify the value 2 times but with a bool there's no way,
    // so we instead just set it back.
    val = false;
  }

  rjni_test_helper("rJniBooleanArray", false, new_array);
  */
}

/*
JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeByteTests(
    JNIEnv* env, jclass, jobject test_fixture, jbyteArray byte_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jbyte> local_arr{byte_array};
  rjni_test_helper("rJniByteArray", jbyte{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniByteArray", jbyte{0}, LocalArray<jbyte>{byte_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jbyte> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jbyte>(i);
    }
  }
  rjni_test_helper("rJniByteArray", jbyte{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jbyte& val : new_array.Pin(true)) {
    val += 5;
  }
  rjni_test_helper("rJniByteArray", jbyte{5 + 5}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeCharTests(
    JNIEnv* env, jclass, jobject test_fixture, jcharArray char_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jchar> local_arr{char_array};
  rjni_test_helper("rJniCharArray", jchar{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniCharArray", jchar{0}, LocalArray<jchar>{char_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jchar> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jchar>(i);
    }
  }
  rjni_test_helper("rJniCharArray", jchar{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jchar& val : new_array.Pin(true)) {
    val += 5;
  }

  rjni_test_helper("rJniCharArray", jchar{5 + 5}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeShortTests(
    JNIEnv* env, jclass, jobject test_fixture, jshortArray short_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jshort> local_arr{short_array};
  rjni_test_helper("rJniShortArray", jshort{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniShortArray", jshort{0},
                   LocalArray<jshort>{short_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jshort> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jshort>(i);
    }
  }
  rjni_test_helper("rJniShortArray", jshort{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jshort& val : new_array.Pin(true)) {
    val += 5;
  }

  rjni_test_helper("rJniShortArray", jshort{5 + 5}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeIntTests(
    JNIEnv* env, jclass, jobject test_fixture, jintArray int_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jint> local_arr{int_array};
  rjni_test_helper("rJniIntArray", 0, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniIntArray", 0, LocalArray<jint>{int_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jint> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = i;
    }
  }
  rjni_test_helper("rJniIntArray", 0, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (int& val : new_array.Pin(true)) {
    val += 5;
  }

  rjni_test_helper("rJniIntArray", 5 * 2, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeLongTests(
    JNIEnv* env, jclass, jobject test_fixture, jlongArray long_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jlong> local_arr{long_array};
  rjni_test_helper("rJniLongArray", jlong{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniLongArray", jlong{0}, LocalArray<jlong>{long_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jlong> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jlong>(i);
    }
  }
  rjni_test_helper("rJniLongArray", jlong{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jlong& val : new_array.Pin(true)) {
    val += 5;
  }

  rjni_test_helper("rJniLongArray", jlong{5 * 2}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeFloatTests(
    JNIEnv* env, jclass, jobject test_fixture, jfloatArray float_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  LocalArray<jfloat> local_arr{float_array};
  rjni_test_helper("rJniFloatArray", 0.f, local_arr);

  {
    ArrayView array_view{local_arr.Pin(true)};
    for (int i = 0; i < local_arr.Length(); ++i) {
      array_view.ptr()[i] += 2.5f;
    }
  }
  rjni_test_helper("rJniFloatArray", 2.5f, local_arr);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeDoubleTests(
    JNIEnv* env, jclass, jobject test_fixture, jdoubleArray double_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jdouble> local_arr{double_array};
  rjni_test_helper("rJniDoubleArray", jdouble{0}, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniDoubleArray", jdouble{0},
                   LocalArray<jdouble>{double_array});

  // Building a new array, and setting all the values by hand works.
  LocalArray<jdouble> new_array{8};
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] = static_cast<jdouble>(i);
    }
  }
  rjni_test_helper("rJniDoubleArray", jdouble{0}, new_array);

  // You can pull the view multiple times.
  {
    ArrayView array_view{new_array.Pin(true)};
    for (int i = 0; i < new_array.Length(); ++i) {
      array_view.ptr()[i] += 5;
    }
  }

  // And it can be iterated over.
  for (jdouble& val : new_array.Pin(true)) {
    val += 5;
  }
  rjni_test_helper("rJniDoubleArray", jdouble{5 * 2}, new_array);
}

JNIEXPORT void JNICALL Java_com_jnibind_test_ArrayTest_nativeObjectTests(
    JNIEnv* env, jclass, jobject test_fixture, jobjectArray object_array) {
  LocalObject<kArrayTest> rjni_test_helper{test_fixture};

  // Simple lvalue pass through works as expected.
  LocalArray<jobject, 1, kObjectTestHelperClass> local_arr{object_array};
  rjni_test_helper("rJniObjectArray", 0, local_arr);

  // Simple rvalue pass through works as expected.
  rjni_test_helper("rJniObjectArray", 5,
                   LocalArray<jobject, 1, kObjectTestHelperClass>{
                       1, LocalObject<kObjectTestHelperClass>{5, 5, 5}});

  // Building a new array, and setting all the values by hand works.
  LocalObject<kObjectTestHelperClass> obj{0, 0, 0};
  LocalArray<jobject, 1, kObjectTestHelperClass> new_array{8, obj};
  {
    for (int i = 0; i < new_array.Length(); ++i) {
      new_array.Set(
          i, LocalObject<kObjectTestHelperClass>{jint{i}, jint{i}, jint{i}});
    }
  }
  rjni_test_helper("rJniObjectArray", 0, new_array);

  // You can pull the view multiple times.
  {
    for (int i = 0; i < new_array.Length(); ++i) {
      new_array.Set(i,
                    LocalObject<kObjectTestHelperClass>{2, 2, 2}(
                        "returnNewObjectWithFieldSetToSum", new_array.Get(i)));
    }
  }

  // And it can be iterated over.
  // Note: LocalObject is not a reference here, instead, the underlying jobject
  //  is being iterated over, and upcast to a LocalObject.
  // Also note: Pin is not to contiguous memory, so no copyback bool either.
  for (LocalObject<kObjectTestHelperClass> val : new_array.Pin()) {
    val["intVal1"].Set(val["intVal1"].Get() + 3);
    val["intVal2"].Set(val["intVal2"].Get() + 3);
    val["intVal3"].Set(val["intVal3"].Get() + 3);
  }

  rjni_test_helper("rJniObjectArray", 2 + 3, new_array);
}
*/

}  // extern "C"
