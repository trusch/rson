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

#ifndef __RSONDECODER__
#define __RSONDECODER__

#include "rson/Value.h"
#include <sstream>

#include <iostream>

namespace RSON {

    class Decoder {
        protected:
            std::uint8_t readUint8(std::istream & data);
            std::uint16_t readUint16(std::istream & data);
            std::uint32_t readUint32(std::istream & data);
            std::uint64_t readUint64(std::istream & data);    
            std::string readCString(std::istream & data);
            std::string readString(std::istream & data, std::size_t size);
        public: 
            Value decode(std::istream & data);
            Value decode(std::string & data){
                std::stringstream ss{data};
                return decode(ss);
            };
    };

}

#endif // __RSONDECODER__