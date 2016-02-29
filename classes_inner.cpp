#include <vector>
#include <iostream>

class MyIterator;
int getLast(MyVector mv);
class MyVector {
protected:
	int array[1024];
public:
	MyVector() {};
	~MyVector() {};
	friend MyIterator;
	friend int getLast(MyVector mv);
};

int getLast(MyVector mv) {
	return mv.array[1023];
}

class MyIterator {
	MyVector*	mv;
public:
	MyIterator(MyVector* mvp) : mv(mvp){};
	int getFirst() {
		return mv->array[0];
	}
};

int main() {
	MyVector my;
	//MyVector::MyIterator mi(&my);
	MyIterator mi(&my);
	std::cout << mi.getFirst() << std::endl;

	return 0;
}