#include <iostream>

class MyClass {
public:
	MyClass() { std::cout << "Constructor!!!" << std::endl; }
	~MyClass() { std::cout << "Destructor!!!" << std::endl; }
};

class Exception {
public:
	char *some;
	Exception(){};
	Exception(char *str) : some(str) {};
};

class IOEx : public Exception {};
class NetworkEx : public Exception {};

void foo() {
	MyClass	mc;
	throw "Simple string!";
	throw IOEx();
}


int main() {
	try {
		try {
			foo();
		}
		catch (Exception ex) {
			std::cout << "Some exception" << ex.some;
		}
	}
	catch (char* strex) {
		std::cout << "Some string exception: " << strex << std::endl;
	}
	
	return 0;
}