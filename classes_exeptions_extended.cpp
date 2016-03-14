#include <iostream>
#include <string>


class Exception {
protected:
	std::string message;
	char * megabytebuffer;
public:
	Exception() {
		megabytebuffer = new char[1024 * 1024];
	}
	Exception(const Exception &source_e) {
		std::cout << "Exception copy construction" << std::endl;
		this->message = source_e.message;
		megabytebuffer = new char[1024 * 1024];
		memcpy(this->megabytebuffer, source_e.megabytebuffer, 1024*1024);
	}
	Exception(Exception &&source_e) {
		std::cout << "Exception move construction" << std::endl;
		this->message = source_e.message;
		megabytebuffer = source_e.megabytebuffer;
		source_e.megabytebuffer = NULL;
	}
	Exception(std::string s) : message(s) {
		megabytebuffer = new char[1024 * 1024];
	}
	~Exception() {
		delete[] megabytebuffer;
	}
	std::string get_message() {
		return this->message;
	}
};

class NetworkException : public Exception {
public:
	NetworkException(std::string s) : Exception(s) {}
};

class IOException : public Exception {
public:
	IOException(std::string s) : Exception(s) {}
};

int main() {
	std::string s;
	try {
		throw IOException("some message");
	}
	catch (IOException e) {
		std::cout << "Got some message from IOexception: " << e.get_message() << std::endl;
	}
	catch (Exception e) {
		std::cout << "Got some message from exception: " << e.get_message() << std::endl;
	}

	return 0;
}
