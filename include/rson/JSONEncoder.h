/*
 * Copyright (c) 2015, Tino Rusch
 *
 * This file is released under the terms of the MIT license. You can find the
 * complete text in the attached LICENSE file or online at:
 *
 * http://www.opensource.org/licenses/mit-license.php
 * 
 * @author: Tino Rusch (tino.rusch@webvariants.de)
 */

#ifndef __JSONENCODER__
#define __JSONENCODER__

#include "rson/Value.h"

namespace RSON {
    class JSONEncoder {
        protected:
            std::string encodeNull();
            std::string encodeBool(const Value & value);
            std::string encodeInteger(const Value & value);
            std::string encodeDouble(const Value & value);
            std::string encodeString(const Value & value);
            std::string encodeBinary(const Value & value);
            std::string encodeObject(const Value & value);
            std::string encodeArray(const Value & value);
            std::string escapeString(const std::string & str);

        public: 
            std::string encode(const Value & value);
    };
}

#endif // __JSONENCODER__