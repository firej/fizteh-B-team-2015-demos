#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <string>
using namespace std;

class NotFoundException{};
class DublicateKeyException{};

class Hasher {
public:
	unsigned __int64 hash(string key) {
		unsigned char result = 0;
		for (unsigned int i = 0; i < key.length(); i++) {
			result ^= key[i];
		}
		return result;
	}
	unsigned __int64 hash(unsigned __int64 key) {
		unsigned char result = 34;
		return result ^ (key >> 2);
	}
	unsigned __int64 operator () (string key) {
		return hash(key);
	}
};

template <class T>
class HashTable {
	struct row{
		unsigned __int64 hash;
		struct {
			string key;
			T data;
		} pair;
	};
	row* values[256];
	Hasher hasher;
public:
	HashTable(Hasher h = Hasher()): hasher(h){
		memset(this->values, 0, sizeof(this->values));
	};
	bool insert(string key, T data) {
		try {
			this->find(key);
			throw DublicateKeyException();
			return false;
		}
		catch (NotFoundException) {
			unsigned __int64 hash = hasher(key);
			row **ptr = this->values + hash;
			unsigned char max_hashes = 5;
			while (*ptr != NULL && max_hashes) {
				hash = hasher.hash(hash);
				ptr = this->values + hash;
				max_hashes--;
			}
			if (max_hashes) {
				*ptr = new row({ hash, { key, data } });
				return true;
			}
			else {
				throw "shit!";
			}
		}
	}
	T find(string key) {
		unsigned __int64 hash = hasher(key);
		row **ptr = this->values + hash;
		unsigned char max_hashes = 5;
		while (*ptr != NULL && max_hashes) {
			if ((*ptr)->pair.key == key)
				return (*ptr)->pair.data;
			hash = hasher.hash(hash);
			ptr = this->values + hash;
			max_hashes--;
		}
		throw NotFoundException();
	}
	T operator [] (string key) {
		return find(key);
	}
};


int main() {
	HashTable<string> ht;

	ht.insert("key", "value");
	ht.insert("key2", "value2");
	ht.insert("limepie3", "value3");
	ht.insert("limepie4", "value4");
	ht.insert("key255", "value2");

	ht.insert("key3", "some cookies!");

	cout << ht["key"] << endl;
	cout << ht["key2"] << endl;
	cout << ht["key255"] << endl;
	cout << ht["limepie3"] << endl;
	cout << ht["limepie4"] << endl;


	return 0;
}