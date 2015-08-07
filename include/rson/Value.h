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

#ifndef __RSONVALUE__
#define __RSONVALUE__

#include <string>
#include <cstdint>
#include <map>
#include <deque>

#include <iostream>

namespace RSON {
    enum Type {
        NULLVALUE,      // \x00
        BOOL,           // \x01
        INT8,           // \x02
        INT16,          // \x03
        INT32,          // \x04
        INT64,          // \x05
        UINT8,          // \x06
        UINT16,         // \x07
        UINT32,         // \x08
        UINT64,         // \x09
        DOUBLE,         // \x0a
        STRING,         // \x0b
        BINARY,         // \x0c
        OBJECT,         // \x0d
        ARRAY,          // \x0e
        BOOL_ARRAY,     // \x0f
        INT8_ARRAY,     // \x10
        INT16_ARRAY,    // \x11
        INT32_ARRAY,    // \x12
        INT64_ARRAY,    // \x13
        UINT8_ARRAY,    // \x14
        UINT16_ARRAY,   // \x15
        UINT32_ARRAY,   // \x16
        UINT64_ARRAY,   // \x17
        DOUBLE_ARRAY,   // \x18
        STRING_ARRAY,   // \x19
        BINARY_ARRAY,   // \x1a
        OBJECT_ARRAY    // \x1b
    };

    class Value;
/*    class Encoder;
    class Decoder;
*/
    typedef std::map<std::string,Value> Object;
    typedef std::deque<Value> Array;

    class Value {
    friend class Encoder;
    friend class Decoder;
    friend class JSONEncoder;
    friend class JSONDecoder;

    protected:
        union NumberUnion {
            std::uint8_t data[8];
            bool         boolValue;
            std::int8_t  int8;
            std::int16_t int16;
            std::int32_t int32;
            std::int64_t int64;
            std::uint8_t  uint8;
            std::uint16_t uint16;
            std::uint32_t uint32;
            std::uint64_t uint64;
            double        doubleValue;
        } _numbers;

        Type _type = NULLVALUE;

        Object _object;
        Array _array;
        std::string _string;

    public:
        Value();
        
        Value(const Value & val);
        Value(Value && val);
        
        Value& operator=(const RSON::Value& val);
        Value& operator=(RSON::Value && val);

        Value(std::nullptr_t);
        Value(const bool & val);

        Value(const std::int8_t & val);
        Value(const std::int16_t & val);
        Value(const std::int32_t & val);
        Value(const std::int64_t & val);
        Value(const std::uint8_t & val);
        Value(const std::uint16_t & val);
        Value(const std::uint32_t & val);
        Value(const std::uint64_t & val);
        Value(const double & val);

        Value(const std::string & val);
        Value(const char * val);
        Value(const char * ptr, std::size_t len);
        Value(const Object & val);
        Value(const Array & val);
        
        Value(std::string && val);
        Value(Object && val);
        Value(Array && val);

        bool isNull() const;
        bool isBool() const;
        bool isInt8() const;
        bool isInt16() const;
        bool isInt32() const;
        bool isInt64() const;
        bool isUint8() const;
        bool isUint16() const;
        bool isUint32() const;
        bool isUint64() const;
        bool isDouble() const;
        bool isNumber() const;
        bool isString() const;
        bool isBinary() const;
        bool isObject() const;
        bool isArray() const;

        bool & getBool();
        std::int8_t & getInt8();
        std::int16_t & getInt16();
        std::int32_t & getInt32();
        std::int64_t & getInt64();
        std::uint8_t & getUint8();
        std::uint16_t & getUint16();
        std::uint32_t & getUint32();
        std::uint64_t & getUint64();
        double & getDouble();
        std::string & getString();
        const char* getBinary();
        Object & getObject();
        Array & getArray();

        std::size_t size() const;

        Type getType() const;
        void setType(Type type);

        std::string toRSON() const;
        static Value fromRSON(std::string);
    };


}


#endif // __RSONVALUE__
