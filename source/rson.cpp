#include "rson/Value.h"
#include <memory>
#include <sstream>

std::string RSON::Value::toRSON() const {
    std::string result{};
    result.push_back(std::uint8_t{_type});
    switch(_type){
        case NULLVALUE: {
            break;
        }
        case BOOL: {
            result.push_back(_numbers.data[0]);
            break;
        }
        case INT8:
        case UINT8: {
            result.push_back(_numbers.data[0]);
            break;
        }
        case INT16:
        case UINT16: {
            result.push_back(_numbers.data[0]);
            result.push_back(_numbers.data[1]);
            break;
        }
        case INT32:
        case UINT32: {
            result.push_back(_numbers.data[0]);
            result.push_back(_numbers.data[1]);
            result.push_back(_numbers.data[2]);
            result.push_back(_numbers.data[3]);
            break;
        }
        case INT64: 
        case UINT64: 
        case DOUBLE: {
            result.push_back(_numbers.data[0]);
            result.push_back(_numbers.data[1]);
            result.push_back(_numbers.data[2]);
            result.push_back(_numbers.data[3]);
            result.push_back(_numbers.data[4]);
            result.push_back(_numbers.data[5]);
            result.push_back(_numbers.data[6]);
            result.push_back(_numbers.data[7]);
            break;
        }
        case STRING: 
        case BINARY: {
            std::uint32_t len = _string.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;
            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(_string);
            break;
        }
        case OBJECT: {
            std::string subdoc{};
            for(const auto & kv : _object){
                subdoc.append(kv.first);
                subdoc.push_back('\x00');
                subdoc.append(kv.second.toRSON());
            }
            std::uint32_t len = subdoc.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;
            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(subdoc);
            break;
        }
        case ARRAY: {
            std::string subdoc{};
            for(const auto & elem : _array){
                subdoc.append(elem.toRSON());
            }
            std::uint32_t len = subdoc.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;
            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(subdoc);
            break;
        }
        case BOOL_ARRAY: 
        case INT8_ARRAY: 
        case UINT8_ARRAY: {
            std::string subdoc{};
            for(const auto & elem : _array){
                subdoc.push_back(elem._numbers.data[0]);
            }
            std::uint32_t len = subdoc.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;
            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(subdoc);
            break;
        }
        case INT16_ARRAY: 
        case UINT16_ARRAY: {
            std::string subdoc{};
            for(const auto & elem : _array){
                subdoc.push_back(elem._numbers.data[0]);
                subdoc.push_back(elem._numbers.data[1]);
            }
            std::uint32_t len = subdoc.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;
            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(subdoc);
            break;
        }
        case INT32_ARRAY: 
        case UINT32_ARRAY: {
            std::string subdoc{};
            for(const auto & elem : _array){
                subdoc.push_back(elem._numbers.data[0]);
                subdoc.push_back(elem._numbers.data[1]);
                subdoc.push_back(elem._numbers.data[2]);
                subdoc.push_back(elem._numbers.data[3]);
            }
            std::uint32_t len = subdoc.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;

            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(subdoc);
            break;
        }
        case INT64_ARRAY: 
        case UINT64_ARRAY: 
        case DOUBLE_ARRAY: {
            std::string subdoc{};
            for(const auto & elem : _array){
                subdoc.push_back(elem._numbers.data[0]);
                subdoc.push_back(elem._numbers.data[1]);
                subdoc.push_back(elem._numbers.data[2]);
                subdoc.push_back(elem._numbers.data[3]);
                subdoc.push_back(elem._numbers.data[4]);
                subdoc.push_back(elem._numbers.data[5]);
                subdoc.push_back(elem._numbers.data[6]);
                subdoc.push_back(elem._numbers.data[7]);
            }
            std::uint32_t len = subdoc.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;

            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(subdoc);
            break;
        }
        case STRING_ARRAY: 
        case BINARY_ARRAY: {
            std::string subdoc{};
            for(const auto & elem : _array){
                std::uint32_t len = elem._string.size();
                std::uint8_t *ptr = (std::uint8_t*) &len;

                subdoc.push_back(ptr[0]);
                subdoc.push_back(ptr[1]);
                subdoc.push_back(ptr[2]);
                subdoc.push_back(ptr[3]);
                subdoc.append(elem._string);
            }
            std::uint32_t len = subdoc.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;

            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(subdoc);
            break;
        }
        case OBJECT_ARRAY: {
            std::string subdoc{};
            for(const auto & elem : _array){
                std::string objectStr{};
                for(const auto & kv : elem._object){
                    objectStr.append(kv.first);
                    objectStr.append('\x00');
                    objectStr.append(kv.second.toRSON());
                }
                std::uint32_t len = objectStr.size();
                std::uint8_t *ptr = (std::uint8_t*) &len;

                subdoc.push_back(ptr[0]);
                subdoc.push_back(ptr[1]);
                subdoc.push_back(ptr[2]);
                subdoc.push_back(ptr[3]);
                subdoc.append(objectStr);
            }
            std::uint32_t len = subdoc.size();
            std::uint8_t *ptr = (std::uint8_t*) &len;

            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            result.append(subdoc);
            break;
        }
    }
    return result;
}

RSON::Value RSON::Value::fromRSON(std::istream & data){
    RSON::Value result;
    RSON::Type type;
    char c;
    data.get(c);
    type = (RSON::Type)c;
    result.setType(type);
    switch(type){
        case NULLVALUE: {
            break;
        }
        case BOOL:
        case INT8:
        case UINT8: {
            data.get(c);
            result._numbers.data[0] = c;
            break;
        }
        case INT16:
        case UINT16: {
            data.get(c);
            result._numbers.data[0] = c;
            data.get(c);
            result._numbers.data[1] = c;
            break;
        }
        case INT32:
        case UINT32: {
            data.get(c);
            result._numbers.data[0] = c;
            data.get(c);
            result._numbers.data[1] = c;
            data.get(c);
            result._numbers.data[2] = c;
            data.get(c);
            result._numbers.data[3] = c;
            break;
        }
        case INT64:
        case UINT64:
        case DOUBLE: {
            data.get(c);
            result._numbers.data[0] = c;
            data.get(c);
            result._numbers.data[1] = c;
            data.get(c);
            result._numbers.data[2] = c;
            data.get(c);
            result._numbers.data[3] = c;
            data.get(c);
            result._numbers.data[4] = c;
            data.get(c);
            result._numbers.data[5] = c;
            data.get(c);
            result._numbers.data[6] = c;
            data.get(c);
            result._numbers.data[7] = c;
            break;
        }
        case STRING:
        case BINARY: {
            std::size_t len;
            char *ptr = (char*)&len;
            data.get(ptr[0]);
            data.get(ptr[1]);
            data.get(ptr[2]);
            data.get(ptr[3]);
            auto buff = std::shared_ptr<char>(new char[len]);
            data.get(&*buff,len);
            result._string = std::string{&*buff,len};
            break;
        }
        case OBJECT: {
            std::uint32_t len;
            char *ptr = (char*)&len;
            data.get(ptr[0]);
            data.get(ptr[1]);
            data.get(ptr[2]);
            data.get(ptr[3]);
            auto buff = std::shared_ptr<char>(new char[len]);
            data.read(&*buff,len);
            std::string objectData{&*buff,len};
            std::stringstream ss{objectData};
            while(ss.good()){
                std::string key;
                while(true){
                    ss.get(c);
                    if(c=='\x00')break;
                    key += c;
                }
                RSON::Value val = RSON::Value::fromRSON(ss);
                result._object[key] = val;
            }
            break;
        }
        case ARRAY: {
            std::uint32_t len;
            char *ptr = (char*)&len;
            data.get(ptr[0]);
            data.get(ptr[1]);
            data.get(ptr[2]);
            data.get(ptr[3]);
            auto buff = std::shared_ptr<char>(new char[len]);
            data.read(&*buff,len);
            std::string objectData{&*buff,len};
            std::stringstream ss{objectData};
            while(ss.good()){
                RSON::Value val = RSON::Value::fromRSON(ss);
                result._array.emplace_back(std::move(val));
            }
            break;
        }
    }
    return result;
}