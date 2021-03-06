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

#include "Elastos.CoreLibrary.Utility.h"
#include "org/apache/http/impl/cookie/BasicExpiresHandler.h"
#include "org/apache/http/impl/cookie/DateUtils.h"
#include "elastos/utility/logging/Logger.h"

using Elastos::Utility::Logging::Logger;

namespace Org {
namespace Apache {
namespace Http {
namespace Impl {
namespace Cookie {

BasicExpiresHandler::BasicExpiresHandler(
    /* [in] */ ArrayOf<String>* datepatterns)
{
    if (datepatterns == NULL) {
        Logger::E("BasicExpiresHandler", "Array of date patterns may not be null");
        assert(0);
        // throw new IllegalArgumentException("Array of date patterns may not be null");
    }
    mDatepatterns = datepatterns;
}

ECode BasicExpiresHandler::Parse(
    /* [in] */ ISetCookie* cookie,
    /* [in] */ const String& value)
{
    if (cookie == NULL) {
        Logger::E("BasicExpiresHandler", "Cookie may not be null");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }
    if (value.IsNull()) {
        Logger::E("BasicExpiresHandler", "Missing value for expires attribute");
        return E_MALFORMED_COOKIE_EXCEPTION;
    }
    // try {
    AutoPtr<IDate> date;
    ECode ec = DateUtils::ParseDate(value, mDatepatterns, (IDate**)&date);
    if (ec == (ECode)E_DATE_PARSE_EXCEPTION) {
        Logger::E("BasicExpiresHandler", "Unable to parse expires attribute: %s", value.string());
        return E_MALFORMED_COOKIE_EXCEPTION;
    }
    return cookie->SetExpiryDate(date);
    // } catch (DateParseException dpe) {
    //     throw new MalformedCookieException("Unable to parse expires attribute: "
    //         + value);
    // }
}

} // namespace Cookie
} // namespace Impl
} // namespace Http
} // namespace Apache
} // namespace Org