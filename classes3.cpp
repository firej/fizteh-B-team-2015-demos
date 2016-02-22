#include <iostream>
#include <vector>
#include <initializer_list>

class BaseObj {
public:
	BaseObj() {
		std::cout << "BaseObj created!" << "\t";
	}
	virtual ~BaseObj() {
		std::cout << "BaseObj destroyed!!! \t";
	}
	int f;
	virtual int method() const{
		return 0;
	}
};

class Obj : public BaseObj {
public:
	Obj() {
		std::cout << "Obj created" << std::endl;
	}
	virtual ~Obj() {
		std::cout << "Obj destroyed" << std::endl;
	}
	virtual int method() const{
		return 1;
	}
};

int foo(const BaseObj* ptr) {
	return ptr->method();
}

int main(){
	Obj	*o = new Obj();
	BaseObj *ptr = o;
	std::cout << o->method() << std::endl;
	std::cout << ptr->method() << std::endl;
	std::cout << foo(ptr) << std::endl;
	delete ptr;
	return 0;
}
