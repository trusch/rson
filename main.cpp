#include "rson/Value.h"

#include <iostream>
#include <iomanip>
#include <sstream>

int main(){
	RSON::Value bar = RSON::Object{
		{"aaa",RSON::Array{1,2,3,1.5}}
	};

	std::string barStr = bar.toRSON();
	std::stringstream ss{barStr};
	RSON::Value foo = RSON::Value::fromRSON(ss);
	std::string fooStr = foo.toRSON();
	for(std::size_t i=0;i<barStr.size();i++){
		std::cout<<std::hex<<(int)(std::uint8_t)barStr[i]<<" ";
	}
	std::cout<<std::endl;
	for(std::size_t i=0;i<fooStr.size();i++){
		std::cout<<std::hex<<(int)(std::uint8_t)fooStr[i]<<" ";
	}
	std::cout<<std::endl;

	return 0;
}