// whatever includes you need
#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string;
#include<cctype>
using std::isdigit; using std::isalpha;

bool valid_hex(string str) {
	if(str.substr(0,1)=="-"){
		str.erase(0,1);
	}
	if(str.substr(0,2)!="0x") {
		return false;
	} else {
		for(int i=2; i<str.length(); i++){
			if(!( (str.at(i)>='0' && str.at(i)<='9') ||
				 (str.at(i)>='a' && str.at(i)<='f')
				 )){
				return false;
			}
		}
	}
	return true;
}

bool valid_octal (string str) {
	if(str.substr(0,1)=="-"){
		str.erase(0,1);
	}
	if(str[0] != '0'){
		return false;
	}
	for(int i =1; i < str.length(); i++){
		if (isalpha(str[i]) || str[i] < '0' || str[i] > '7'){
			return false;
		}
	}
	return true;
}

bool valid_binary (string str){
	if(str.substr(0,1)=="-"){
		str.erase(0,1);
	}
	if(str.substr(0,2) != "0b"){
		return false;
	} else {
		for(int i =2; i < str.length(); i++){
			if (str[i] < '0' || str[i] > '1'){
				return false;
			}
		}
	}
	return true;
}

bool valid_int (string str){
	if(str.substr(0,1)=="-"){
		str.erase(0,1);
	}
	for(int i =0; i < str.length(); i++){
		if(isdigit(str[i]) == false){
			return false;
		}
	}
	return true;
}

bool valid_float(string str){
	string test = "0123456789e.-";
	int first_point = str.find('.');
	int second_point = str.rfind('.');
	int first_e = str.find('e');
	int second_e = str.rfind('e');
	if(second_e != first_e){
		return false;
	}
	if(second_point != first_point){
		return false;
	}
	if(str.at(str.length()-1) == 'e') {
		return false;
	}
	if (first_point != -1 || first_e != -1){
		for(int i =0; i < str.length(); i++){
			char str_element = str.at(i);
			int test_find = test.find(str_element);
			if(test_find == -1){
				return false;
			}
		}
	} else {
		return false;
	}
	return true;
}

string classify_string(string str){
	if(str == "" || str.length() == 1){
		return "false";
	} else if(valid_hex(str)) {
		return "hex";
	} else if (valid_octal(str)) {
		return "octal";
	} else if (valid_binary(str)) {
		return "binary";
	} else if (valid_int(str)) {
		return "int";
	} else if (valid_float(str)) {
		return "float";
	}
	return "false";
}

int main (){
	
	cout << boolalpha;
	int testnum;
	cin >> testnum;
	
	switch (testnum) {
		case 1:{
			string to_test;
			cin >> to_test;
			cout << valid_hex(to_test) << endl;
			break;
		}
			
		case 2:{
			string to_test;
			cin >> to_test;
			cout << valid_octal(to_test) << endl;
			break;
		}
			
		case 3:{
			string to_test;
			cin >> to_test;
			cout << valid_binary(to_test) << endl;
			break;
		}
			
		case 4:{
			string to_test;
			cin >> to_test;
			cout << valid_float(to_test) << endl;
			break;
		}
			
		case 5:{
			string to_test;
			cin >> to_test;
			cout << valid_int(to_test) << endl;
			break;
		}
			
		case 6:{
			string to_test;
			cin >> to_test;
			cout << classify_string(to_test) << endl;
			break;
		}
			
			
	}// of switch
}// of main

