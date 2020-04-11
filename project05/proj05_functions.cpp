#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::to_string;
#include <locale>
using std::tolower; using std::islower; using std::isupper;
#include <algorithm>
#include<cmath>
#include<cctype>
using std::isalpha;


string lower_case(const string& s){
	string lower = s;
	string output;
	for (auto ch : s){
		output += tolower(ch);
	}
	return output;
}

string to_binary(char c){
	int val =c-'a';
	if(!(val>=0 && val<26)) {
		return "";
		
	}
	string ans ="";
	for(int i=0; i<5; i++){
		ans=std::to_string(val%2)+ans;
		val=(val-val%2)/2;
	}
	return ans;
}


char from_binary(const string& bit_str1){
	string bit_str = bit_str1;
	if(bit_str.length() != 5){
		return 0;
	}
	for(auto ele : bit_str) {
		if(ele < '0' || ele > '1'){
			return '0';
		}
	}
	int total = 0;
	int index = 0;
	for(int i = bit_str.length()-1; i>=0;i--){
		total += ((bit_str[index]-'0')*(std::pow(2,i)));
		index++;
	}
	if (total>25){
		return 0;
	}
	if(!(islower((char)('a'+total))))
		return 0;
	return (char)('a'+total);
}

bool check_message(const string& plaintext1, const string& secret_message1){
	string plaintext = plaintext1;
	string secret_message = secret_message1;
	int plaintext_count = 0,secret_message_count = 0;
	for (auto pt : plaintext){
		if(isalpha(pt))
			plaintext_count++;
	}
	for (auto sm : secret_message){
		if(isalpha(sm))
			secret_message_count++;
	}
	if(plaintext_count >= (5*secret_message_count) ){
		return true;
	}
	return false;
}

string encode(const string& plaintext, const string& secret_message){
	
	string lower_plaintext = lower_case(plaintext);
	string lower_secret_message = lower_case(secret_message);
	
	if(!(check_message(lower_plaintext, lower_secret_message)))
		return "Error";
	
	string secret_message_binary;
	
	for(auto s:lower_secret_message) {
		string binary = to_binary(s);
		secret_message_binary+=binary;
	}
	int j =0;
	while(j<secret_message_binary.length()){
		for(int i =0; i< lower_plaintext.length();i++){
			if(isalpha(lower_plaintext[i])){
				if(secret_message_binary[j] == '1'){
					lower_plaintext[i] = toupper(lower_plaintext[i]);
				}
				j++;
			}
		}
	}
	return lower_plaintext;
	
}

string decode(const string& to_decode){
	
	string binary;
	
	for(auto ch: to_decode){
		if(isalpha(ch)){
			if(isupper(ch)){
				binary+='1';
			} else {
				binary+='0';
			}
		}
	}
	string output;
	while(binary.length()>=5){
		output+=from_binary(binary.substr(0,5));
		binary.erase(0,5);
	}
	return output;
	
}
