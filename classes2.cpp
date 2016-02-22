#include <iostream>
#include <vector>
#include <initializer_list>
#include <vector>

class BaseObj{
public:
	BaseObj() {
		std::cout << "BaseObj created!" << "\t";
	}
	~BaseObj() {
		std::cout << "BaseObj destroyed!!! \t";
	}
};

class Some {
public:
	Some() {
		std::cout << "Some init!" << std::endl;
	}
};

class Obj: BaseObj {
	float field_a, field_b;
public:
	Obj(float a, float b): field_a(a), field_b(b) {
		std::cout << "Obj created with params" << std::endl;
	}
	Obj(): field_a(0), field_b(1) {
		//Obj(0, 1);
		std::cout << "Obj created" << std::endl;
	}
	Obj(std::initializer_list<int> list_of_objs) {
		for each (auto i in list_of_objs) {
			std::cout << " " << i;
		}
		std::cout << std::endl;
	}
	~Obj() {
		std::cout << "Obj destroyed" << std::endl;
	}
};

int main(){
	Obj	o = { 1,2,3,4,5,6,7 };
	return 0;
}
