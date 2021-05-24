// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "proxy.h"

#include <tuple>
#include <type_traits>

#include "class.h"
#include "class_loader.h"
#include "jni_test.h"
#include "jvm.h"
#include "local_object.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "class.h"
#include "class_loader.h"
#include "global_object.h"
#include "jni_dep.h"
#include "local_string.h"
#include "metaprogramming/concatenate.h"
#include "method.h"
#include "method_selection.h"
#include "params.h"
#include "supported_class_set.h"

using jni::AsDecl_t;
using jni::Class;
using jni::ClassLoader;
using jni::GlobalObject;
using jni::LocalObject;
using jni::Proxy_t;
using jni::Return_t;
using jni::metaprogramming::TypeToTypeMapQuery_t;
using jni::test::JniTest;

namespace jni {

static constexpr Class kClass{
    "kClass", jni::Method{"Bar", jni::Return<void>{}, jni::Params{}}};
static constexpr Class kClass2{
    "kClass2", jni::Method{"Foo", jni::Return{kClass}, jni::Params{}}};
static constexpr ClassLoader kClassLoader{kDefaultClassLoader,
                                          SupportedClassSet{kClass}};

// CDecls of primitive types.
static_assert(std::is_same_v<Proxy_t<void>::CDecl, void>);
static_assert(std::is_same_v<Proxy_t<jint>::CDecl, jint>);
static_assert(std::is_same_v<Proxy_t<jfloat>::CDecl, jfloat>);
static_assert(std::is_same_v<Proxy_t<jbyte>::CDecl, jbyte>);
static_assert(std::is_same_v<Proxy_t<jchar>::CDecl, jchar>);
static_assert(std::is_same_v<Proxy_t<jshort>::CDecl, jshort>);
static_assert(std::is_same_v<Proxy_t<jlong>::CDecl, jlong>);
static_assert(std::is_same_v<Proxy_t<jdouble>::CDecl, jdouble>);

// CDecls of non-primitive types.
// Multiple types map to single index.
static_assert(std::is_same_v<Proxy_t<const char*>::CDecl, jstring>);
static_assert(std::is_same_v<decltype("Foo"), char const (&)[4]>);
static_assert(std::is_same_v<Proxy_t<const char (&)[4]>::CDecl, jstring>);

static_assert(std::is_same_v<Proxy_t<const char*>::CDecl, jstring>);
static_assert(std::is_same_v<Proxy_t<std::string_view>::CDecl, jstring>);
static_assert(std::is_same_v<Proxy_t<std::string>::CDecl, jstring>);

void Foo() {
  LocalObject<kClass> obj;

  static_assert(std::is_same_v<Proxy_t<decltype(kClass)>::CDecl, jobject>);
  static_assert(std::is_same_v<Proxy_t<decltype(obj)>::CDecl, jobject>);
  static_assert(
      std::is_same_v<Proxy_t<LocalObject<kClass, kClassLoader>>::CDecl,
                     jobject>);
}

////////////////////////////////////////////////////////////////////////////////
// Types as declarations.
////////////////////////////////////////////////////////////////////////////////
static_assert(std::is_same_v<AsDecl_t<void>, std::tuple<void>>);
static_assert(std::is_same_v<AsDecl_t<jint>, std::tuple<int>>);
static_assert(std::is_same_v<AsDecl_t<jfloat>, std::tuple<float>>);
static_assert(std::is_same_v<AsDecl_t<jbyte>, std::tuple<jbyte>>);
static_assert(std::is_same_v<AsDecl_t<jchar>, std::tuple<char, jchar>>);
static_assert(std::is_same_v<AsDecl_t<jshort>, std::tuple<jshort>>);
static_assert(std::is_same_v<AsDecl_t<jlong>, std::tuple<long, jlong>>);
static_assert(std::is_same_v<AsDecl_t<jdouble>, std::tuple<double>>);

// Note, sizeof these types are _not_ equal on x86.
static_assert(!std::is_same_v<AsDecl_t<jboolean>, std::tuple<bool>>);
static_assert(std::is_same_v<AsDecl_t<jboolean>, std::tuple<jboolean, bool>>);

// AsDecl of non-trivial types with multiple keys.
static_assert(std::is_same_v<AsDecl_t<const char*>, std::tuple<jstring>>);
static_assert(std::is_same_v<AsDecl_t<std::string_view>, std::tuple<jstring>>);
static_assert(std::is_same_v<AsDecl_t<std::string>, std::tuple<jstring>>);

////////////////////////////////////////////////////////////////////////////////
// Types as return values.
////////////////////////////////////////////////////////////////////////////////

// The second type for Return_t is the overload which allows for rich decoration
// of return arguments (only applicable for class return types).
struct DummyOverload {};

static_assert(std::is_same_v<Return_t<void, DummyOverload>, void>);
static_assert(std::is_same_v<Return_t<jint, DummyOverload>, jint>);
static_assert(std::is_same_v<Return_t<jfloat, DummyOverload>, jfloat>);
static_assert(std::is_same_v<Return_t<jbyte, DummyOverload>, jbyte>);
static_assert(std::is_same_v<Return_t<jchar, DummyOverload>, jchar>);
static_assert(std::is_same_v<Return_t<jshort, DummyOverload>, jshort>);
static_assert(std::is_same_v<Return_t<jlong, DummyOverload>, jlong>);
static_assert(std::is_same_v<Return_t<jdouble, DummyOverload>, jdouble>);
static_assert(
    std::is_same_v<Return_t<const char*, DummyOverload>, LocalString>);
static_assert(
    std::is_same_v<Return_t<std::string_view, DummyOverload>, LocalString>);
static_assert(
    std::is_same_v<Return_t<std::string, DummyOverload>, LocalString>);

// Objects are better tested through the convertability of their output.
TEST_F(JniTest, MaterializationTests) {
  // Objects passed in can be from plain old jobject.
  LocalObject<kClass2> obj0{jobject{nullptr}};

  // Objects passed in can be lvalues.
  LocalObject<kClass2> obj1{LocalObject<kClass2>{}};

  // Objects can be rvalues materialized in place.
  LocalObject<kClass2> local_0{LocalObject<kClass2>{}};

  // Objects can be rvalues (here an x-value).
  LocalObject<kClass2> generator_obj{};
  LocalObject<kClass> local_1{generator_obj("Foo")};

  // Objects can also be described with no actual class definition.
  // These objects won't be usable, but they are "name-safe".
  LocalObject local_2{generator_obj("Foo")};

  // doesn't compile because of invalid class (good).
  // LocalObject<kClass2> local_3 { generator_obj("Foo") }; }

  // Globals can be built from locals.
  GlobalObject<kClass> global_1{generator_obj("Foo")};
  global_1("Bar");

  // Globals can be built from expiring locals without a full type.
  GlobalObject global_2{generator_obj("Foo")};

  // But they lack sufficient definition to have any invocation!
  // global_2("Bar");

  // They can be promoted however, and thus restore their type info.
  GlobalObject<kClass> global_3{std::move(global_2)};
  global_3("Bar");
}

}  // namespace jni
