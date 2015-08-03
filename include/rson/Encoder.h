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

#ifndef __RSONENCODER__
#define __RSONENCODER__

#include "rson/Value.h"

namespace RSON {

    class Encoder {
        protected:
            std::string sizeToString(std::size_t len);

            std::string encodeNull();
            std::string encode8bit(const Value & value);
            std::string encode16bit(const Value & value);
            std::string encode32bit(const Value & value);
            std::string encode64bit(const Value & value);
            std::string encodeString(const Value & value);
            std::string encodeObject(const Value & value);
            std::string encodeArray(const Value & value);
            std::string encode8bitArray(const Value & value);
            std::string encode16bitArray(const Value & value);
            std::string encode32bitArray(const Value & value);
            std::string encode64bitArray(const Value & value);
            std::string encodeStringArray(const Value & value);
            std::string encodeObjectArray(const Value & value);

        public: 
            std::string encode(const Value & value);
    };

}

#endif // __RSONENCODER__