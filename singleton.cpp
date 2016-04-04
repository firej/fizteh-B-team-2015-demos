#include <iostream>
#include <string>

class Singleton {
	static Singleton* instance;
public:
	Singleton() {
		if (Singleton::instance == NULL) {
			instance = this;
		}
		else {
			throw "Not unique seingleton!";
		}
	}
	Singleton* get_instance() const {
		return Singleton::instance;
	}
	std::wstring get_string() {
		return std::wstring(L"Some string!");
	}
};
Singleton* Singleton::instance = NULL;

class SingletonAdapter {
	static Singleton* instance;
public:
	Singleton* get_instance() {
		if (instance) return instance;
		else return instance = new Singleton();
	}
};
Singleton* SingletonAdapter::instance = NULL;


int main() {
	SingletonAdapter s1;
	std::wcout << L"First object created! " << s1.get_instance()->get_string() << std::endl;
	SingletonAdapter s2;
	std::wcout << L"Second object created! " << s2.get_instance()->get_string() << std::endl;
	return 0;
}
