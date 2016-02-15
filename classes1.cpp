#include <iostream>
#include <string>
#include <vector>


class student{
public:
	std::string FIO;
	int rate;
	student(){}
	student(std::string a){
		FIO = a;
	}
	student(int rate1){
		rate1 = rate;
	}
};

class group{
public:
	std::vector<student> students;
	float avgrate();
};

float group::avgrate(){
	int k = students.size();
	float sum = 0;
	for (int i = 0; i < k; i++){
		sum += students[i].rate;
	}
	if (k) {
		return sum / k;
	}
	else {
		return 0;
	}
}

class MyClass{
public:
	int myfield;
	MyClass() {
		std::cout << "My object created" << std::endl;
		myfield = 0;
	}
	MyClass(int param) {
		std::cout << "My object created with param " << param << std::endl;
		myfield = param;
	}
	int operator + (int op2) {
		return this->myfield + op2;
	}
	~MyClass() {
		std::cout << "My object destroyed" << std::endl;
	}
};

int main() {
	group g;
	g.students.push_back(student(5));
	std::cout << g.avgrate() << std::endl;

	std::vector<int> array = { 0, 1, 2, 3 };
	array[2] = 109000;
	array.push_back(1000);
	array.erase(array.begin() + 2);
	for (int i = 0; i < array.size(); i++){
		std::cout << *(array.begin() + i) << "   ";
	}
	std::cout << std::endl;

	for (std::vector<int>::iterator i = array.begin(); i < array.end(); i++){
		std::cout << *i << "   ";
	}
	std::cout << std::endl;

	for each (auto a in array){
		std::cout << a << "   ";
	}
	std::cout << std::endl;


	int a = 0;
	MyClass object(5);
	(std::cout << (object + 10)) << std::endl;
	return 0;
}
