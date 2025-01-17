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
#ifndef JNI_BIND_IMPLEMENTATION_CORPUS_H_
#define JNI_BIND_IMPLEMENTATION_CORPUS_H_

#include <tuple>

#include "implementation/corpus_tag.h"
#include "metaprogramming/concatenate.h"
#include "metaprogramming/detect.h"

namespace jni {

// Provides the universe of keys, including user defined types if any.
// Users define custom types by partially specialising UserDefined (see test).
template <typename... Defaults>
struct Corpus {
  template <typename T, bool = ::jni::metaprogramming::Detect_v<
                            UserDefined, JniUserDefinedCorpusTag> >
  struct Helper {
    using type = ::jni::metaprogramming::ConcatenateTup_t<
        ::jni::metaprogramming::Detect_t<UserDefined, JniUserDefinedCorpusTag>,
        std::tuple<Defaults...> >;
  };

  template <typename T>
  struct Helper<T, false> {
    using type = std::tuple<Defaults...>;
  };

  template <typename T>
  using type = typename Helper<T>::type;
};

template <typename T, typename... Defaults>
using Corpus_t = typename Corpus<Defaults...>::template type<T>;

}  // namespace jni

#endif  // JNI_BIND_IMPLEMENTATION_CORPUS_H_
