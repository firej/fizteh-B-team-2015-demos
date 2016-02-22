#include <iostream>
#include <vector>

class BaseObj {
public:
	BaseObj() {
	}
	virtual ~BaseObj() {
	}
	int f;
	int method() const{
		return 0;
	}
};

class Obj1 : public virtual BaseObj {
public:
	/*int method() const{
		return 1;
	}*/
};

class Obj2 : public virtual BaseObj {
public:
	/*int method() const{
		return 2;
	}*/
};

class Obj : public virtual Obj1, Obj2 {
public:

};

int main(){
	Obj	*o = new Obj();
	//BaseObj *ptr = o;
	std::cout << o->method() << std::endl;
	delete o;
	return 0;
}
