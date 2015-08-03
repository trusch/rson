#include "rson/Value.h"

RSON::Value::Value() {}

RSON::Value::Value(const RSON::Value & val) : _type{val._type} {
    if(isNumber()){
        _numbers.uint64 = val._numbers.uint64;
    }else if(isObject()){
        _object = val._object;
    }else if(isArray()){
        _array = val._array;
    }else if(isString() || isBinary()){
        _string = val._string;
    }
}
RSON::Value::Value(RSON::Value && val) {
    _type = val._type;
    if(isNumber()){
        _numbers.uint64 = val._numbers.uint64;
    }else if(isObject()){
        _object = std::move(val._object);
    }else if(isArray()){
        _array = std::move(val._array);
    }else if(isString() || isBinary()){
        _string = std::move(val._string);
    }
}

RSON::Value& RSON::Value::operator=(const RSON::Value& val){
    _type = val._type;
    if(isNumber()){
        _numbers.uint64 = val._numbers.uint64;
    }else if(isObject()){
        _object = val._object;
    }else if(isArray()){
        _array = val._array;
    }else if(isString() || isBinary()){
        _string = val._string;
    }
    return *this;
}

RSON::Value& RSON::Value::operator=(RSON::Value && val){
    _type = val._type;
    if(isNumber()){
        _numbers.uint64 = val._numbers.uint64;
    }else if(isObject()){
        _object = std::move(val._object);
    }else if(isArray()){
        _array = std::move(val._array);
    }else if(isString() || isBinary()){
        _string = std::move(val._string);
    }
    return *this;
}

RSON::Value::Value(const bool & val) : _type{BOOL} {
    _numbers.uint64 = 0;
    _numbers.boolValue = val;
}

RSON::Value::Value(const std::int8_t & val) : _type{INT8} {
    _numbers.uint64 = 0;
    _numbers.int8 = val;
}
RSON::Value::Value(const std::int16_t & val) : _type{INT16} {
    _numbers.uint64 = 0;
    _numbers.int16 = val;
}
RSON::Value::Value(const std::int32_t & val) : _type{INT32} {
    _numbers.uint64 = 0;
    _numbers.int32 = val;
}
RSON::Value::Value(const std::int64_t & val) : _type{INT64} {
    _numbers.uint64 = 0;
    _numbers.int64 = val;
}
RSON::Value::Value(const std::uint8_t & val) : _type{UINT8} {
    _numbers.uint64 = 0;
    _numbers.uint8 = val;
}
RSON::Value::Value(const std::uint16_t & val) : _type{UINT16} {
    _numbers.uint64 = 0;
    _numbers.uint16 = val;
}
RSON::Value::Value(const std::uint32_t & val) : _type{UINT32} {
    _numbers.uint64 = 0;
    _numbers.uint32 = val;
}
RSON::Value::Value(const std::uint64_t & val) : _type{UINT64} {
    _numbers.uint64 = val;
}
RSON::Value::Value(const double & val) : _type{DOUBLE} {
    _numbers.doubleValue = val;
}

RSON::Value::Value(const std::string & val) : _type{STRING}, _string{val} {}
RSON::Value::Value(const char * val) : _type{STRING}, _string{val} {}
RSON::Value::Value(const char * ptr, std::size_t len) : _type{BINARY}, _string{ptr,len} {}
RSON::Value::Value(const Object & val) : _type{OBJECT}, _object{val} {}
RSON::Value::Value(const Array & val) : _type{ARRAY}, _array{val.begin(),val.end()} {}

RSON::Value::Value(std::string && val) : _type{STRING}, _string{val} {}
RSON::Value::Value(Object && val) : _type{OBJECT}, _object{val} {}
RSON::Value::Value(Array && val) : _type{ARRAY}, _array{std::make_move_iterator(val.begin()), 
                                           std::make_move_iterator(val.end())} {}

bool RSON::Value::isNull(){
    return _type == NULLVALUE;
}
bool RSON::Value::isBool(){
    return _type == BOOL;
}
bool RSON::Value::isInt8(){
    return _type == INT8;
}
bool RSON::Value::isInt16(){
    return _type == INT16;
}
bool RSON::Value::isInt32(){
    return _type == INT32;
}
bool RSON::Value::isInt64(){
    return _type == INT64;
}
bool RSON::Value::isUint8(){
    return _type == INT8;
}
bool RSON::Value::isUint16(){
    return _type == INT16;
}
bool RSON::Value::isUint32(){
    return _type == INT32;
}
bool RSON::Value::isUint64(){
    return _type == INT64;
}
bool RSON::Value::isDouble(){
    return _type == DOUBLE;
}
bool RSON::Value::isNumber(){
    switch(_type){
        case BOOL:
        case INT8:
        case INT16:
        case INT32:
        case INT64:
        case UINT8:
        case UINT16:
        case UINT32:
        case UINT64:
        case DOUBLE: {
            return true;
        }
        default: {
            return false;
        }
    }
}
bool RSON::Value::isString(){
    return _type == STRING;
}
bool RSON::Value::isBinary(){
    return _type == BINARY;
}
bool RSON::Value::isObject(){
    return _type == OBJECT;
}
bool RSON::Value::isArray(){
    switch(_type){
        case ARRAY:
        case BOOL_ARRAY:
        case INT8_ARRAY:
        case INT16_ARRAY:
        case INT32_ARRAY:
        case INT64_ARRAY:
        case UINT8_ARRAY:
        case UINT16_ARRAY:
        case UINT32_ARRAY:
        case UINT64_ARRAY:
        case DOUBLE_ARRAY:
        case STRING_ARRAY:
        case BINARY_ARRAY:
        case OBJECT_ARRAY: {
            return true;
        }
        default: {
            return false;
        }
    }
}

bool & RSON::Value::getBool(){return _numbers.boolValue;}
std::int8_t & RSON::Value::getInt8(){return _numbers.int8;}
std::int16_t & RSON::Value::getInt16(){return _numbers.int16;}
std::int32_t & RSON::Value::getInt32(){return _numbers.int32;}
std::int64_t & RSON::Value::getInt64(){return _numbers.int64;}
std::uint8_t & RSON::Value::getUint8(){return _numbers.uint8;}
std::uint16_t & RSON::Value::getUint16(){return _numbers.uint16;}
std::uint32_t & RSON::Value::getUint32(){return _numbers.uint32;}
std::uint64_t & RSON::Value::getUint64(){return _numbers.uint64;}
double & RSON::Value::getDouble(){return _numbers.doubleValue;}
std::string & RSON::Value::getString(){return _string;}
const char* RSON::Value::getBinary(){return _string.data();}
RSON::Object & RSON::Value::getObject(){return _object;}
RSON::Array & RSON::Value::getArray(){return _array;}

std::size_t RSON::Value::size(){
    if(isArray()){
        return _array.size();
    } else if(isObject()){
        return _object.size();
    } if(isString() || isBinary()){
        return _string.size();
    }
    return 0;
}

RSON::Type RSON::Value::getType(){ return _type; }
void RSON::Value::setType(RSON::Type type){ _type = type; }

