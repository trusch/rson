#include "rson/Decoder.h"

namespace RSON {
    
    std::uint8_t Decoder::readUint8(std::istream & data){
        char v;
        data.get(v);
        return v;
    }

    std::uint16_t Decoder::readUint16(std::istream & data){
        std::uint16_t v;
        char *ptr = (char*)&v;
        data.get(ptr[0]);
        data.get(ptr[1]);
        return v;
    }

    std::uint32_t Decoder::readUint32(std::istream & data){
        std::uint32_t v;
        char *ptr = (char*)&v;
        data.get(ptr[0]);
        data.get(ptr[1]);
        data.get(ptr[2]);
        data.get(ptr[3]);
        return v;
    }

    std::uint64_t Decoder::readUint64(std::istream & data){
        std::uint64_t v;
        char *ptr = (char*)&v;
        data.get(ptr[0]);
        data.get(ptr[1]);
        data.get(ptr[2]);
        data.get(ptr[3]);
        data.get(ptr[4]);
        data.get(ptr[5]);
        data.get(ptr[6]);
        data.get(ptr[7]);
        return v;
    }

    std::string Decoder::readCString(std::istream & data){
        std::string result{};
        char c;
        while(true){
            data.get(c);
            if(c=='\x00'){
                break;
            }
            result.push_back(c);
        }
        return result;
    }

    std::string Decoder::readString(std::istream & data, std::size_t size){
        std::string result(size,'\x00');
        data.read((char*)result.data(),size);
        return result;
    }

    Value Decoder::decode(std::istream & data){
        char c;
        data.get(c);
        Type type = (Type)c;
        Value value;
        value.setType(type);
        switch(type){
            case NULLVALUE: {
                break;
            }
            case BOOL:
            case UINT8:
            case INT8: {
                value._numbers.uint64 = readUint8(data);
                break;
            }
            case UINT16:
            case INT16: {
                value._numbers.uint64 = readUint16(data);
                break;
            }
            case UINT32:
            case INT32: {
                value._numbers.uint64 = readUint32(data);
                break;
            }
            case UINT64:
            case INT64:
            case DOUBLE: {
                value._numbers.uint64 = readUint64(data);
                break;
            }
            case STRING:
            case BINARY: {
                std::size_t len = readUint32(data);
                value._string.resize(len);
                data.read((char*)value._string.data(),len);
                break;
            }
            case OBJECT: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    std::string key = readCString(ss);
                    if(ss.good()){
                        Value v = decode(ss);
                        value._object.emplace(key,v);
                    }
                }
                break;
            }
            case ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = decode(ss);
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case BOOL_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    value._array.emplace_back(bool(readUint8(ss)));
                }
                break;
            }
            case INT8_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = std::int8_t(readUint8(ss));
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case UINT8_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = readUint8(ss);
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case INT16_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = std::int16_t(readUint16(ss));
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case UINT16_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = readUint16(ss);
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case INT32_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = std::int32_t(readUint32(ss));
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case UINT32_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = readUint32(ss);
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case INT64_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = std::int64_t(readUint64(ss));
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case UINT64_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v = readUint64(ss);
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case DOUBLE_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    Value v;
                    v.setType(DOUBLE);
                    v._numbers.uint64 = readUint64(ss);
                    if(ss.good()){
                        value._array.emplace_back(std::move(v));
                    }
                }
                break;
            }
            case STRING_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    std::size_t len = readUint32(ss);
                    Value v;
                    v.setType(STRING);
                    v._string.resize(len);
                    ss.read((char*)v._string.data(),len);
                    if(ss.good()){
                        value._array.emplace_back(v);
                    }
                }
                break;
            }
            case BINARY_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    std::size_t len = readUint32(ss);
                    Value v;
                    v.setType(BINARY);
                    v._string.resize(len);
                    ss.read((char*)v._string.data(),len);
                    if(ss.good()){
                        value._array.emplace_back(v);
                    }
                }
                break;
            }
            case OBJECT_ARRAY: {
                std::size_t len = readUint32(data);
                std::string subdoc(len,'\x00');
                data.read((char*)subdoc.data(),len);
                std::stringstream ss{subdoc};
                while(ss.good()){
                    std::size_t len = readUint32(ss);
                    RSON::Object object;
                    std::string valueDoc(len,'\x00');
                    ss.read((char*)valueDoc.data(),len);
                    std::stringstream vss{valueDoc};
                    while(vss.good()){
                        std::string key = readCString(vss);
                        Value v = decode(vss);
                        if(vss.good()){
                            object.emplace(key,v);
                        }
                    }
                    if(ss.good()){
                        value._array.emplace_back(object);
                    }
                }
                break;
            }
        }
        return value;
    }

}