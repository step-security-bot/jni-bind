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

#include "constructor.h"

#include "mock_jni_env.h"
#include <gtest/gtest.h>
#include "class.h"
#include "jni_dep.h"
#include "jni_test.h"
#include "local_object.h"
#include "params.h"
#include "return.h"

namespace {

using jni::Class;
using jni::Constructor;
using jni::LocalObject;
using jni::test::JniTest;
using jni::test::MockJniEnv;
using testing::_;
using testing::StrEq;

TEST_F(JniTest, Constructor_LeavesEmptyStringForNoArgs) {
  static constexpr Class c{
      "LeavesEmptyStringForNoArgs",
  };
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("()V")));
  LocalObject<c> obj{};
}

TEST_F(JniTest, Constructor_TakesIntAsParameter) {
  static constexpr Class c{"TakesIntAsParameter", Constructor<jint>{}};
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(I)V")));
  LocalObject<c> obj{1};
}

TEST_F(JniTest, Constructor_TakesFloatAsParameter) {
  static constexpr Class c{"TakesIntAsParameter", Constructor<jfloat>{}};
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(F)V")));

  LocalObject<c> obj{1.f};
}

TEST_F(JniTest, Constructor_Takes3IntsAsParameter) {
  static constexpr Class c{"Takes3IntsAsParameter",
                           Constructor<jint, jint, jint>{}};
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(III)V")));

  LocalObject<c> obj{1, 2, 3};
}

TEST_F(JniTest, Constructor_TakesIntOrFloat) {
  static constexpr Class c{
      "TakesIntOrFloat",
      Constructor<jint>{},
      Constructor<jfloat>{},
  };

  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(I)V")));
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(F)V")));

  LocalObject<c> obj{jint{1}};
  LocalObject<c> obj2{jfloat{2.f}};
}

TEST_F(JniTest, Constructor_TakesObject) {
  static constexpr Class c1{
      "Argument",
  };

  static constexpr Class c2{
      "TakesObject",
      Constructor{c1},
  };

  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("()V")));
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(LArgument;)V")));

  LocalObject<c1> arg{};
  LocalObject<c2> obj{arg};
}

TEST_F(JniTest, Constructor_TakesDifferentTypes) {
  static constexpr Class c{
      "TakesDifferentTypes", Constructor<>{},     Constructor<jboolean>{},
      Constructor<jchar>{},  Constructor<jint>{},
  };

  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("()V")));
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(Z)V")));
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(C)V")));
  EXPECT_CALL(*env_, GetMethodID(_, StrEq("<init>"), StrEq("(I)V")));

  // Note, these explicit types are needed to avoid unintended conversion.
  // (See ImbueConstructor for details).
  LocalObject<c> obj1{};
  LocalObject<c> obj2{jboolean{'a'}};
  LocalObject<c> obj3{jchar{4}};
  LocalObject<c> obj4{jint{5}};
}

}  // namespace