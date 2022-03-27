#pragma once
#include <iostream>
#include <vector>
#include<map>
#include<memory>
#include<iterator>
using namespace std;


template <class K, class V>
class CacheMemory{
public:
	CacheMemory(){}
	~CacheMemory(){}
	void add(const K& key, const V& value)  {
		auto check = main_mem.find(key);
		if (check != main_mem.end()) {
			add2cache(key,value);
			throw "DuplicateKeyException";
			return;
		}
		shared_ptr <V> temp;
		temp = make_shared<V>(value);
		main_mem.insert({ key,temp });
		temp = nullptr;
		temp.~shared_ptr();
	}
	void erase(const K& key) {
		auto check = main_mem.find(key);
		if (check == main_mem.end())
			throw "ObjectNotExistException";
		main_mem.erase(key);
	}
	shared_ptr<V> get(const K& key) {
		auto it = cache.find(key);
		if (it != cache.end()) {
			weak_ptr<V> temp = it->second;
			if (!temp.expired())
				return main_mem.find(key)->second;
			cache.erase(key);
			return nullptr;
		}
		auto temp2 = main_mem.find(key);
		if (temp2 != main_mem.end()) {
			V* s = temp2->second.get();
			add2cache(key, *s);
			return temp2->second;
		}
		return nullptr;
	}
private:
	void add2cache(const K& key,const V& value) {
		shared_ptr <V> ptr;
		ptr = make_shared<V>(value);
		weak_ptr<V> w = ptr;
		cache.insert({ key,w });
	}
	map <K, shared_ptr<V> > main_mem;
	map <K, weak_ptr<V> > cache;
};

//int main() {
//	CacheMemory<int, string> m;
//	int x = 1;
//	string s = "gilad";
//	m.add(x, s);
//	m.add(9, "shiran");
//	m.add(2, "sasson");
//	m.add(x, s);
//	m.add(9, "shiran");
//	shared_ptr<string> temp = m.get(x);
//	string* itzhak = temp.get();
//	cout << *itzhak;
//}