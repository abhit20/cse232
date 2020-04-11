#pragma once
#include<iostream>
using std::cout; using std::endl; using std::boolalpha; using std::ostream;
#include<initializer_list>
using std::initializer_list;
#include <algorithm>
using std::max; using std::copy; using std::swap;
#include <utility>
using std::make_pair; using std::pair;
#include <stdexcept>
using std::runtime_error;

const static size_t element_array_size = 5;

template<typename K, typename V>
struct Element{
public:
	K key_;
	V values_[element_array_size];
	Element* next_ = nullptr;
	
	size_t count_ = 0;
	
	Element()=default;
	Element(K key, initializer_list<V> values){
		key_= key;
		count_ = values.size();
		next_ = nullptr;
		copy(values.begin(), values.end(), values_);
	}
	
	Element(const Element& other){
		key_ = other.key_;
		count_ = other.count_;
		next_ = nullptr;
		copy(other.values_,other.values_+other.count_,values_);
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
	Element<K, V> * data_head_ = nullptr;
	
	size_t num_keys_ = 0;
	
	pair <Element<K,V>*, Element<K,V> *> find_key(K key){
		Element<K,V> *first = nullptr;
		Element<K,V> *second = nullptr;
		for(auto p = data_head_;p!=nullptr;p = p->next_){
			if(key <= p->key_){
				second = p;
				break;
			} else first = p;
		}
		return pair <Element<K,V>*, Element<K,V> *>(first,second);
	}
	MVM find_value(V val){
		MVM<K,V> result;
		for(auto p = data_head_; p != nullptr; p = p->next_){
			for(auto a : p->values_){
				if(a==val){
					result.add(p->key_, val);
				}
			}
		}
		return result;
	}
	
public:
	//Constructors
	MVM()=default;
	MVM(initializer_list<Element<K,V>> init){
		num_keys_ = init.size();
		Element<K, V> * temp_p = nullptr;
		for(auto a:init ){
			if(data_head_==nullptr){
				data_head_ = new Element<K,V>(a);
				temp_p = data_head_;
			}
			else{
				temp_p->next_ = new Element<K,V>(a);
				temp_p = temp_p->next_;
			}
		}
	}
	
	//Rule of Three
	MVM(const MVM& other){
		if(other.data_head_==nullptr){
			data_head_=nullptr;
			num_keys_=0;
		} else{
			Element<K,V> * temp_p = nullptr;
			num_keys_=other.num_keys_;
			for(auto * p = data_head_;p!=nullptr;p = p->next_){
				if(data_head_==nullptr){
					data_head_ = new Element<K,V>(*p);
					temp_p=data_head_;
				}else{
					auto &q = temp_p->next_;
					q=new Element<K,V>(*p);
					temp_p = q;
				}
			}
		}
	}
	MVM& operator=(const MVM& other);
	~MVM(){
		Element<K,V>* to_del = data_head_;
		while (to_del !=nullptr){
			data_head_ = data_head_->next_;
			delete to_del;
			to_del = data_head_;
		}
		data_head_ = nullptr;
	}
	//Other Functions
	size_t size(){
		return num_keys_;
	}
	bool add(K key , V value)
	{
		auto findKey = find_key(key);
		auto first = findKey.first;
		auto second = findKey.second;
		Element<K,V>* ele = new Element<K,V>(key,{value});
		
		if(first == nullptr && second == nullptr){
			data_head_ =  ele;
			ele -> next_ = nullptr;
			num_keys_++;
			return true;
		} else if ( first == nullptr) {
			if(second->key_ == key){
				for(auto i = 0; i< second->count_; i++){
					if(second->values_[i] == value) return false;
				}
				second->values_[second->count_++] = value;
				return true;
			}
			ele->next_ = data_head_;
			data_head_ = ele;
			++num_keys_;
			return true;
		} else if (second == nullptr){
			first->next_ = ele;
			ele->next_ = nullptr;
			++num_keys_;
			return true;
		} else {
			if(second->key_ == key) {
				for(auto i = 0; i< second->count_; i++) {
					if(second->values_[i] == value) return false;
				}
				second->values_[second->count_++] = value;
				return true;
			}
			first->next_ = ele;
			ele->next_ = second;
			++num_keys_;
			return true;
		}
	}
	bool remove_key(K key){
		auto findKey = find_key(key);
		if((findKey.second)!=nullptr){
			if(findKey.second->key_!=key) return false;
			else{
				if(findKey.first==nullptr){
					data_head_ = findKey.second ->next_;
					delete findKey.second;
					num_keys_--;
				} else {
					findKey.first -> next_ = findKey.second->next_;
					delete findKey.second;
					num_keys_--;
				}
			}
		}
		else return false;
		return true;
	}
	
	MVM remove_value(V val){
		MVM findValue = find_value(val);
		auto temp_p = findValue.data_head_;
		for(size_t i = 0; i < findValue.size(); i++){
			auto findKey = find_key(temp_p->key_);
			auto * j = findKey.second->values_;
			size_t temp_Count = findKey.second->count_;
			for(auto * i = findKey.second->values_; i<findKey.second->values_+temp_Count; i++){
				if(*i==val){
					findKey.second->count_--;
				}
				else{
					*j=*i;
					j++;
				}
			}
			temp_p=temp_p->next_;
		}
		return findValue;
	}
	friend ostream& operator<<(ostream& oss, MVM& mvm){
		Element<K,V>* p = mvm.data_head_;
		auto count = 0;
		while(p!=nullptr){
			oss << *p;
			if(count!=(mvm.size()-1)) oss << " ";
			count++;
			p = p->next_;
		}
		return oss;
	}
};
