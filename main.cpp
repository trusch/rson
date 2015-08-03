#include "rson/Value.h"
#include "rson/Encoder.h"
#include "rson/Decoder.h"

#include <iostream>
#include <iomanip>
#include <sstream>

void test(const RSON::Value & val, const std::string & prefix){
	RSON::Encoder encoder;
	RSON::Decoder decoder;
	std::string str = encoder.encode(val);
	std::cout<<prefix<<std::endl;
	for(std::size_t i=0;i<str.size();i++){
		std::cout<<(int)(std::uint8_t)str[i]<<" ";
	}
	std::cout<<std::endl;
	RSON::Value decoded = decoder.decode(str);
	str = encoder.encode(decoded);
	for(std::size_t i=0;i<str.size();i++){
		std::cout<<(int)(std::uint8_t)str[i]<<" ";
	}
	std::cout<<std::endl;
	
}

int main(){
	RSON::Value value;
		
	test(value,"Null: ");
	value = true;
	test(value,"bool(true): ");
	value = std::int8_t{32};
	test(value,"std::int8_t{32}: ");
	value = std::int16_t{32};
	test(value,"std::int16_t{32}: ");
	value = std::int32_t{32};
	test(value,"std::int32_t{32}: ");
	value = std::int64_t{32};
	test(value,"std::int64_t{32}: ");
	value = std::uint8_t{32};
	test(value,"std::uint8_t{32}: ");
	value = std::uint16_t{32};
	test(value,"std::uint16_t{32}: ");
	value = std::uint32_t{32};
	test(value,"std::uint32_t{32}: ");
	value = std::uint64_t{32};
	test(value,"std::uint64_t{32}: ");
	value = 32.0;
	test(value,"double{32.0}: ");
	value = "foo";
	test(value,"string{foo}: ");
	char buff[4] = {1,2,3,4};
	value = RSON::Value{buff,4};
	test(value,"binary{1,2,3,4}: ");
	value = RSON::Object{{"foo",32}};
	test(value,"object{foo:32}: ");
	value = RSON::Array{1,2,3,4};
	test(value,"array{1,2,3,4}: ");
	value.setType(RSON::INT8_ARRAY);
	test(value,"int8_array{1,2,3,4}: ");
	value.setType(RSON::INT16_ARRAY);
	test(value,"int16_array{1,2,3,4}: ");
	value.setType(RSON::INT32_ARRAY);
	test(value,"int32_array{1,2,3,4}: ");
	value.setType(RSON::INT64_ARRAY);
	test(value,"int64_array{1,2,3,4}: ");
	value.setType(RSON::UINT8_ARRAY);
	test(value,"uint8_array{1,2,3,4}: ");
	value.setType(RSON::UINT16_ARRAY);
	test(value,"uint16_array{1,2,3,4}: ");
	value.setType(RSON::UINT32_ARRAY);
	test(value,"uint32_array{1,2,3,4}: ");
	value.setType(RSON::UINT64_ARRAY);
	test(value,"uint64_array{1,2,3,4}: ");
	value = RSON::Array{32.,32.,32.,32.};
	value.setType(RSON::DOUBLE_ARRAY);
	test(value,"double_array{32.,32.,32.,32.}: ");
	value = RSON::Array{"foo","bar"};
	value.setType(RSON::STRING_ARRAY);
	test(value,"string_array{foo,bar}: ");
	value.setType(RSON::BINARY_ARRAY);
	test(value,"binary_array{foo,bar}: ");
	value = RSON::Array{RSON::Object{{"foo",1}},RSON::Object{{"bar",2}}};
	value.setType(RSON::OBJECT_ARRAY);
	test(value,"object_array{{foo:1},{bar:2}}: ");
	


	return 0;
}