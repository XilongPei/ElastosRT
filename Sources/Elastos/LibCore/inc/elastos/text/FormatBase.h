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

#ifndef __ELASTOS_TEXT_FORMATBASE_H_
#define __ELASTOS_TEXT_FORMATBASE_H_

#include "elastos/core/Object.h"
#include "elastos/core/StringBuffer.h"
#include "AttributedCharacterIteratorAttribute.h"

using Elastos::Core::EIID_ICloneable;
using Elastos::Text::IAttributedCharacterIterator;;
using Elastos::Text::IFieldPosition;
using Elastos::Text::IParsePosition;
using Elastos::Core::StringBuffer;
using Elastos::Core::IStringBuffer;
using Elastos::Core::ICloneable;

namespace Elastos {
namespace Text {

class FormatBase
    : public Object
    , public IFormat
    , public ISerializable
    , public ICloneable
{
public:
    class Field
        : public AttributedCharacterIteratorAttribute
    {
    protected:
        CARAPI constructor(
            /* [in] */ const String& fieldName)
        {
            return AttributedCharacterIteratorAttribute::constructor(fieldName);
        }

        CARAPI GetClassID(
            /* [out] */ ClassID* clsid)
        {
            assert(0 && "TODO");
            return NOERROR;
            // return _Field::GetClassID(clsid);
        }
    };

public:
    CAR_INTERFACE_DECL()

    virtual CARAPI Clone(
        /* [out] */ IInterface** outobj) = 0;

    CARAPI CloneImpl(
        /* [in] */ IFormat* format);

    virtual ~FormatBase();

    virtual CARAPI Format(
        /* [in] */ IInterface* object,
        /* [out] */ String* value);

    virtual CARAPI Format(
        /* [in] */ IInterface* object,
        /* [in] */ IStringBuffer * buffer,
        /* [in] */ IFieldPosition* field) = 0;

    virtual CARAPI FormatToCharacterIterator(
        /* [in] */ IInterface* object,
        /* [out] */ IAttributedCharacterIterator** characterIterator);

    virtual CARAPI ParseObject(
        /* [in] */ const String& string,
        /* [out] */ IInterface** object);

    virtual CARAPI ParseObject(
        /* [in] */ const String& string,
        /* [in] */ IParsePosition* position,
        /* [out] */ IInterface** object) = 0;

protected:
    FormatBase();

    static CARAPI UpTo(
        /* [in] */ const String& string,
        /* [in] */ IParsePosition* position,
        /* [in] */ StringBuffer& buffer,
        /* [in] */ Char32 stop,
        /* [out] */ Boolean* succeeded);

    static CARAPI UpToWithQuotes(
        /* [in] */ const String& string,
        /* [in] */ IParsePosition* position,
        /* [in] */ StringBuffer& buffer,
        /* [in] */ Char32 stop,
        /* [in] */ Char32 start,
        /* [out] */ Boolean* succeeded);
};

} // namespace Text
} // namespace Elastos

#endif //__ELASTOS_TEXT_FORMATBASE_H_
