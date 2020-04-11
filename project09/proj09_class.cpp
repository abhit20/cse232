#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include <fstream>
using std::fstream; using std::ifstream; using std::ofstream;
#include<string>
using std::string; using std::to_string;
#include<sstream>
#include<vector>
using std::vector;
#include<sstream>
using std::ostringstream; using std::ostream;
#include <algorithm>
using std::min_element; using std::max_element;
#include <cctype>
using std::tolower; using std::isspace;

#include "proj09_class.h"

Element::Element(string key, initializer_list<string> values){
	key_ = key;
	values_ = values;
}

bool Element::operator==(const Element& ele) const{
	if((ele.key_ != key_)||(ele.values_!=values_))
		return false;
	return true;
}

ostream& operator<<(ostream& oss, Element& ele){
	oss << ele.key_ << ":";
	int count = 0;
	for(auto a: ele.values_){
		oss << a;
		if(count != ele.values_.size()-1){
			oss<<",";
			count++;
		}
	}
	return oss;
}

MVM::MVM(initializer_list<Element> data){
	data_ = data;
}

vector<Element>::iterator MVM::find_key(string key){
	
	auto result = lower_bound(data_.begin(), data_.end(), key, [](Element i,string key){
		return (i.key_<key);
		
	});
	return result;
}

vector<string> MVM::find_value(string val){
	vector<string> result;
	for(auto a: data_){
		for(auto b: a.values_){
			if(b==val){
				result.push_back(a.key_);
			}
		}
	}
	return result;
}

bool MVM::add(string key, string val){
	auto findKey = find_key(key);
	auto findValue = find_value(val);
	if(key==findKey->key_){
		if(std::find(findValue.begin(),findValue.end(),key)==findValue.end()){
			findKey->values_.push_back(val);
		}else{
			return false;
		}
	} else if (findKey==data_.end()){
		data_.push_back(Element(key,{val}));
	} else{
		data_.insert(findKey,Element(key,{val}));
	}
	return true;
}

size_t MVM::size(){
	return data_.size();
}

bool MVM::remove_key(string s){
	auto findKey = find_key(s);
	if(s==findKey->key_){
		data_.erase(findKey);
		return true;
	}
	return false;
}

vector<string> MVM::remove_value(string val){
	auto findValue = find_value(val);
	vector<Element> :: iterator e_itr;
	for(auto a: findValue){
		e_itr = find_key(a);
		auto k = std::find(e_itr->values_.begin(), e_itr->values_.end(), val);
		e_itr->values_.erase(k);
	}
	return findValue;
}

ostream& operator<<(ostream& oss, MVM& mvm){
	int count =0;
	for(auto a: mvm.data_){
		oss<< a;
		if(count != mvm.data_.size()-1){
			oss<< " ";
		}
		count++;
	}
	return oss;
}

