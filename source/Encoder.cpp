#include "rson/Encoder.h"

namespace RSON {
      std::string Encoder::encode(const Value & value) {
            switch(value._type){
                  case NULLVALUE: {
                        return encodeNull();
                  }
                  case BOOL: {
                        return encode8bit(value);
                  }
                  case INT8: {
                        return encode8bit(value);
                  }
                  case INT16: {
                        return encode16bit(value);
                  }
                  case INT32: {
                        return encode32bit(value);
                  }
                  case INT64: {
                        return encode64bit(value);
                  }
                  case UINT8: {
                        return encode8bit(value);
                  }
                  case UINT16: {
                        return encode16bit(value);
                  }
                  case UINT32: {
                        return encode32bit(value);
                  }
                  case UINT64: {
                        return encode64bit(value);
                  }
                  case DOUBLE: {
                        return encode64bit(value);
                  }
                  case STRING: {
                        return encodeString(value);
                  }
                  case BINARY: {
                        return encodeString(value);
                  }
                  case OBJECT: {
                        return encodeObject(value);
                  }
                  case ARRAY: {
                        return encodeArray(value);
                  }
                  case BOOL_ARRAY: {
                        return encode8bitArray(value);
                  }
                  case INT8_ARRAY: {
                        return encode8bitArray(value);
                  }
                  case INT16_ARRAY: {
                        return encode16bitArray(value);
                  }
                  case INT32_ARRAY: {
                        return encode32bitArray(value);
                  }
                  case INT64_ARRAY: {
                        return encode64bitArray(value);
                  }
                  case UINT8_ARRAY: {
                        return encode8bitArray(value);
                  }
                  case UINT16_ARRAY: {
                        return encode16bitArray(value);
                  }
                  case UINT32_ARRAY: {
                        return encode32bitArray(value);
                  }
                  case UINT64_ARRAY: {
                        return encode64bitArray(value);
                  }
                  case DOUBLE_ARRAY: {
                        return encode64bitArray(value);
                  }
                  case STRING_ARRAY: {
                        return encodeStringArray(value);
                  }
                  case BINARY_ARRAY: {
                        return encodeStringArray(value);
                  }
                  case OBJECT_ARRAY: {
                        return encodeObjectArray(value);
                  }
            }
      }

      std::string Encoder::encodeNull(){
            std::string result{};
            result.push_back(std::uint8_t(NULLVALUE));
            return result;
      }
      

      std::string Encoder::encode8bit(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            result.push_back(value._numbers.data[0]);
            return result;
      }
      std::string Encoder::encode16bit(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            result.push_back(value._numbers.data[0]);
            result.push_back(value._numbers.data[1]);
            return result;
      }
      std::string Encoder::encode32bit(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            result.push_back(value._numbers.data[0]);
            result.push_back(value._numbers.data[1]);
            result.push_back(value._numbers.data[2]);
            result.push_back(value._numbers.data[3]);
            return result;
      }
      std::string Encoder::encode64bit(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            result.push_back(value._numbers.data[0]);
            result.push_back(value._numbers.data[1]);
            result.push_back(value._numbers.data[2]);
            result.push_back(value._numbers.data[3]);
            result.push_back(value._numbers.data[4]);
            result.push_back(value._numbers.data[5]);
            result.push_back(value._numbers.data[6]);
            result.push_back(value._numbers.data[7]);
            return result;
      }
      std::string Encoder::encodeString(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            result.append(sizeToString(value._string.size()));
            result.append(value._string);
            return result;
      }
      std::string Encoder::encodeObject(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            std::string subdoc{};
            for(const auto & kv : value._object){
                  subdoc.append(kv.first);
                  subdoc.push_back('\x00');
                  subdoc.append(encode(kv.second));
            }
            result.append(sizeToString(subdoc.size()));
            result.append(subdoc);
            return result;
      }
      std::string Encoder::encodeArray(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            std::string subdoc{};
            for(const auto & elem : value._array){
                  subdoc.append(encode(elem));
            }
            result.append(sizeToString(subdoc.size()));
            result.append(subdoc);
            return result;
      }
      std::string Encoder::encode8bitArray(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            std::string subdoc{};
            for(const auto & elem : value._array){
                  subdoc.push_back(elem._numbers.data[0]);
            }
            result.append(sizeToString(subdoc.size()));
            result.append(subdoc);
            return result;
      }
      std::string Encoder::encode16bitArray(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            std::string subdoc{};
            for(const auto & elem : value._array){
                  subdoc.push_back(elem._numbers.data[0]);
                  subdoc.push_back(elem._numbers.data[1]);
            }
            result.append(sizeToString(subdoc.size()));
            result.append(subdoc);
            return result;
      }
      std::string Encoder::encode32bitArray(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            std::string subdoc{};
            for(const auto & elem : value._array){
                  subdoc.push_back(elem._numbers.data[0]);
                  subdoc.push_back(elem._numbers.data[1]);
                  subdoc.push_back(elem._numbers.data[2]);
                  subdoc.push_back(elem._numbers.data[3]);
            }
            result.append(sizeToString(subdoc.size()));
            result.append(subdoc);
            return result;
      }
      std::string Encoder::encode64bitArray(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            std::string subdoc{};
            for(const auto & elem : value._array){
                  subdoc.push_back(elem._numbers.data[0]);
                  subdoc.push_back(elem._numbers.data[1]);
                  subdoc.push_back(elem._numbers.data[2]);
                  subdoc.push_back(elem._numbers.data[3]);
                  subdoc.push_back(elem._numbers.data[4]);
                  subdoc.push_back(elem._numbers.data[5]);
                  subdoc.push_back(elem._numbers.data[6]);
                  subdoc.push_back(elem._numbers.data[7]);
            }
            result.append(sizeToString(subdoc.size()));
            result.append(subdoc);
            return result;
      }
      std::string Encoder::encodeStringArray(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            std::string subdoc{};
            for(const auto & elem : value._array){
                  subdoc.append(sizeToString(elem._string.size()));
                  subdoc.append(elem._string);
            }
            result.append(sizeToString(subdoc.size()));
            result.append(subdoc);
            return result;
      }

      std::string Encoder::encodeObjectArray(const Value & value){
            std::string result{};
            result.push_back(std::uint8_t(value._type));
            std::string subdoc{};
            for(const auto & elem : value._array){
                  std::string objectStr{};
                  for(const auto & kv : elem._object){
                        objectStr.append(kv.first);
                        objectStr.push_back('\x00');
                        objectStr.append(encode(kv.second));
                  }
                  subdoc.append(sizeToString(objectStr.size()));
                  subdoc.append(objectStr);
            }
            result.append(sizeToString(subdoc.size()));
            result.append(subdoc);
            return result;
      }

      std::string Encoder::sizeToString(std::size_t len){
            std::uint32_t l = static_cast<std::uint32_t>(len);
            char *ptr = (char*)&l;
            std::string result{};
            result.push_back(ptr[0]);
            result.push_back(ptr[1]);
            result.push_back(ptr[2]);
            result.push_back(ptr[3]);
            return result;
      }

}

