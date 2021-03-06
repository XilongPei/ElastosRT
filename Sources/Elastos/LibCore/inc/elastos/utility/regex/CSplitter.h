//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
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
//=========================================================================

#ifndef __ELASTOS_UTILITY_REGEX_REGEX_SPLITTER_H__
#define __ELASTOS_UTILITY_REGEX_REGEX_SPLITTER_H__

#include "_Elastos_Utility_Regex_CSplitter.h"
#include "Singleton.h"
#include <elastos/utility/etl/List.h>

using Elastos::Core::Singleton;
using Elastos::Utility::Etl::List;

namespace Elastos {
namespace Utility {
namespace Regex {

/**
 * Used to make {@code String.split} fast (and to help {@code Pattern.split} too).
 * @hide
 */
CarClass(CSplitter)
    , public Singleton
    , public ISplitter
{
public:
    CAR_INTERFACE_DECL()

    CAR_SINGLETON_DECL()

    /**
     * Returns a result equivalent to {@code s.split(separator, limit)} if it's able
     * to compute it more cheaply than ICU, or null if the caller should fall back to
     * using ICU.
     */
    CARAPI FastSplit(
        /* [in] */ const String& re,
        /* [in] */ const String& input,
        /* [in] */ Int32 limit,
        /* [out, callee] */ ArrayOf<String>** array);

    CARAPI Split(
        /* [in] */ IPattern* pattern,
        /* [in] */ const String& re,
        /* [in] */ const String& input,
        /* [in] */ Int32 limit,
        /* [out, callee] */ ArrayOf<String>** array);

private:
    CARAPI FinishSplit(
        /* [in] */ List<String>& list,
        /* [in] */ const String& input,
        /* [in] */ Int32 begin,
        /* [in] */ Int32 limit,
        /* [out, callee] */ ArrayOf<String>** array);

private:
    // The RI allows regular expressions beginning with ] or }, but that's probably a bug.
    static const String METACHARACTERS;
};

} // namespace Regex
} // namespace Utility
} // namespace Elastos

#endif //__SPLITTER_H__
