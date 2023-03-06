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

#ifndef JNI_BIND_GLOBAL_STRING_H_
#define JNI_BIND_GLOBAL_STRING_H_

#include "implementation/global_object.h"
#include "implementation/local_string.h"
#include "implementation/promotion_mechanics.h"
#include "implementation/ref_base.h"
#include "implementation/string_ref.h"
#include "jni_dep.h"

namespace jni {

class GlobalString : public StringRefBase<GlobalString> {
 public:
  using StringRefBase<GlobalString>::StringRefBase;
  friend class StringRefBase<GlobalString>;

  // jstring ctors.
  GlobalString(PromoteToGlobal, jstring java_string)
      : StringRefBase<GlobalString>(
            JniHelper::PromoteLocalToGlobalString(java_string)) {}
  GlobalString(AdoptGlobal, jstring java_string)
      : StringRefBase<GlobalString>(java_string) {}

  // jobject constructors.
  GlobalString(PromoteToGlobal, jobject java_string_as_object)
      : StringRefBase<GlobalString>(JniHelper::PromoteLocalToGlobalString(
            static_cast<jstring>(java_string_as_object))) {}
  GlobalString(AdoptGlobal, jobject java_string_as_object)
      : StringRefBase<GlobalString>(
            static_cast<jstring>(java_string_as_object)) {}

  GlobalString(GlobalObject<kJavaLangString, kDefaultClassLoader, kDefaultJvm>
                   &&global_string)
      : StringRefBase<GlobalString>(
            static_cast<jstring>(global_string.Release())) {}

  GlobalString(LocalString &&local_string)
      : StringRefBase<GlobalString>(
            JniHelper::PromoteLocalToGlobalString(local_string.Release())) {}

  // Returns a StringView which possibly performs an expensive pinning
  // operation.  String objects can be pinned multiple times.
  UtfStringView Pin() { return {RefBaseTag<jstring>::object_ref_}; }

 private:
  // Construction from jstring requires |PromoteToGlobal| or |AdoptGlobal|.
  explicit GlobalString(jstring obj) : StringRefBase(obj) {}

  // Construction from jstring requires |PromoteToGlobal| or |AdoptGlobal|.
  explicit GlobalString(jobject obj)
      : StringRefBase(static_cast<jstring>(obj)) {}

  // Invoked through CRTP on dtor.
  void ClassSpecificDeleteObjectRef(jstring object_ref) {
    JniHelper::DeleteGlobalString(object_ref);
  }
};

}  // namespace jni

#endif  // JNI_BIND_GLOBAL_STRING_H_
