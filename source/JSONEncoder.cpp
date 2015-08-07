#include "rson/JSONEncoder.h"
#include "rson/base64.h"

namespace RSON {
    std::string JSONEncoder::encode(const Value & value) {
        switch(value._type){
            case NULLVALUE: {
              return encodeNull();
            }
            case BOOL: {
              return encodeBool(value);
            }
            case INT8: 
            case INT16:
            case INT32:
            case INT64:
            case UINT8:
            case UINT16:
            case UINT32:
            case UINT64: {
              return encodeInteger(value);
            }
            case DOUBLE: {
              return encodeDouble(value);
            }
            case STRING: {
              return encodeString(value);
            }
            case BINARY: {
              return encodeBinary(value);
            }
            case OBJECT: {
              return encodeObject(value);
            }
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
                return encodeArray(value);
            }
        }
    }

    std::string JSONEncoder::encodeNull(){
      return "null";
    }

    std::string JSONEncoder::encodeBool(const Value & value){
      return value._numbers.boolValue ? "true" : "false";
    }

    std::string JSONEncoder::encodeInteger(const Value & value){
      return std::to_string(value._numbers.int64);
    }

    std::string JSONEncoder::encodeDouble(const Value & value){
      return std::to_string(value._numbers.doubleValue);
    }

    std::string JSONEncoder::encodeString(const Value & value){
      std::string result = "\"";
      result += value._string;
      result += "\"";
      return result;
    }

    std::string JSONEncoder::encodeBinary(const Value & value){
      std::string result = "\"";
      result += base64_encode((const unsigned char*)value._string.c_str(),value._string.size());
      result += "\"";
      return result;
    }

  std::string JSONEncoder::encodeObject(const Value & value){
    std::string result{"{"};
    for(const auto & kv : value._object){
      result.push_back('"');
      result.append(kv.first);
      result.push_back('"');
      result.push_back(':');
      result.append(encode(kv.second));
      result.push_back(',');
    }
    result[result.size()-1] = '}';
    return result;
  }

  std::string JSONEncoder::encodeArray(const Value & value){
    std::string result{"["};
    for(const auto & elem : value._array){
      result.append(encode(elem));
      result.push_back(',');
    }
    result[result.size()-1] = ']';
    return result;
  }


  std::string JSONEncoder::escapeString(const std::string & str){
    std::string output{};
    output.reserve( input.length() );

    for( std::string::size_type i = 0; i < str.length(); ++i ){
        switch( str[i] ) {
            case '"':
                output += "\\\"";
                break;
            case '/':
                output += "\\/";
                break;
            case '\b':
                output += "\\b";
                break;
            case '\f':
                output += "\\f";
                break;
            case '\n':
                output += "\\n";
                break;
            case '\r':
                output += "\\r";
                break;
            case '\t':
                output += "\\t";
                break;
            case '\\':
                output += "\\\\";
                break;
            default:
                output += str[i];
                break;
        }
    }
    return output;
  }

}

