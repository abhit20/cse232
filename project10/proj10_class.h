#pragma once
#include<iostream>
using std::cout; using std::endl; using std::boolalpha; using std::ostream;
#include<initializer_list>
using std::initializer_list;
#include <algorithm>
using std::max; using std::copy; using std::swap; using std::distance;
using std::rotate;
#include <utility>
using std::make_pair; using std::pair;
#include <stdexcept>
using std::runtime_error;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<sstream>
using std::ostringstream;

const static size_t element_array_size = 5;

template<typename K, typename V>
struct Element{
public:
	K key_;
	V values_[element_array_size];
	size_t count_ = 0;
	Element()=default;
	Element(K key, initializer_list<V> values){
		key_ = key;
		copy(values.begin(), values.end(), values_);
		count_ = values.size();
	}
	bool operator==(const Element& ele)const{
		if((ele.key_ == key_)&&(ele.count_==count_)){
			for(int a = 0; a<ele.count_;a++){
				if(values_[a]!=ele.values_[a]){
					return false;
				} else{
					return true;
				}
			}
		}
		return false;
	}
	friend ostream& operator<<(ostream& oss, Element& ele){
		oss << ele.key_ << ":";
		for(int a = 0; a<ele.count_;a++){
			oss << ele.values_[a];
			if(a!=ele.count_-1){
				oss<<",";
			}
		}
		return oss;
	}
};

template<typename K, typename V>
class MVM{
public:
	Element<K, V> * data_ = nullptr;
	size_t num_keys_ = 0;
	size_t num_elements_ = 0;
	Element<K, V> * find_key(K key){
		auto result = lower_bound(data_,data_+num_keys_,key,[](Element<K,V> ele, K key){
			return ele.key_<key;
		});
		return result;
	}
	size_t find_value(V val, K* (&keys_found)){
		size_t keys_size=0;
		if(keys_found==nullptr) {
			vector<K> keys;
			for(auto a = 0; a<size();a++){
				for(auto b=0;b<data_[a].count_;b++){
					if(val==data_[a].values_[b]){
						keys_size+=1;
						keys.push_back(data_[a].key_);
					}
				}
			}
			if(keys_size>0){
				keys_found = new K[keys_size];
				copy(keys.begin(),keys.end(),keys_found);
			}
			return keys_size;
		}
		else throw runtime_error("error");
	}
	void grow(){
		if(num_elements_ == 0 && data_==nullptr){
			num_elements_ = 2;
			data_ = new Element<K,V>[2]{};
		} else {
			auto data_new = new Element<K,V>[2*num_elements_]{};
			copy(data_, data_+num_elements_, data_new);
			num_elements_ *=2;
			swap(data_new,data_);
			delete [] data_new;
		}
	}
	
public:
	MVM()=default;
	MVM(initializer_list<Element<K,V>> init){
		num_keys_=init.size();
		num_elements_=init.size();
		data_ = new Element<K,V>[num_keys_];
		copy(init.begin(),init.end(),data_);
	}
	MVM(const MVM& mvm);
	~MVM(){
		delete [] data_;
	}
	size_t size(){
		return num_keys_;
	}
	bool add(K key, V value){
		auto findKey = find_key(key);
		if(findKey!=data_+num_keys_ && findKey->key_==key){
			auto findValue = std::find(findKey->values_,findKey->values_+findKey->count_,value);
			if(findValue == findKey->values_+findKey->count_ && findKey->count_ !=element_array_size)
				findKey->values_[findKey->count_++] = value;
			else return false;
		} else {
			auto pos = distance(data_, findKey);
			if(num_keys_ == num_elements_) grow();
			data_[num_keys_++] = Element <K,V>(key,{value});
			rotate(data_+pos, data_+num_keys_-1, data_+num_keys_);
		}
		return true;
	}
	bool remove_key(K key){
		Element<K, V> * findKey = find_key(key);
		if(key==findKey->key_){
			if(num_keys_>1){
				int index = 0;
				while(findKey->key_!=data_[index].key_){
					index++;
				}
				int sizeOf = size();
				while(index<sizeOf-1){
					data_[index]=data_[index+1];
					index++;
				}
			}
			num_keys_--;
			num_elements_--;
			return true;
		}
		return false;
	}
	size_t remove_value(V val, K* (&keys_found)){
		auto k_size = find_value(val, keys_found);
		for(size_t i = 0; i < k_size; i++){
			auto findKey = find_key(keys_found[i]);
			auto * j = findKey->values_;
			int temp_Count = findKey->count_;
			for(auto * i = findKey->values_; i<findKey->values_+temp_Count; i++){
				if(*i==val){
					findKey->count_--;
				}
				else{
					*j=*i;
					j++;
				}
			}
		}
		return k_size;
	}
	friend ostream& operator<<(ostream& oss, MVM& mvm){
		for(int a =0; a<mvm.size();a++){
			oss<< mvm.data_[a];
			if(a!= mvm.size()-1){
				oss<< " ";
			}
		}
		return oss;
	}
};
