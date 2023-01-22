/*
 * Copyright 2022 Google LLC
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
#ifndef JNI_BIND_IMPLEMENTATION_CUSTOM_CORPUS_H_
#define JNI_BIND_IMPLEMENTATION_CUSTOM_CORPUS_H_

#include <tuple>

#include "implementation/corpus_tag.h"
#include "jni_dep.h"

namespace jni {

template <>
struct UserDefined<JniUserDefinedCorpusTag> {
  using type = std::tuple<jstring>;
};

// Not going to work, this isn't defined.
#include "implementation/proxy_definitions_string.h"

}  // namespace jni

#endif  // JNI_BIND_IMPLEMENTATION_CUSTOM_CORPUS_H_
