#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include <fstream>
using std::fstream; using std::ifstream;
#include<string>
using std::string; using std::to_string;
#include<vector>
using std::vector;
#include<sstream>
using std::ostringstream; using std::ostream;
#include <algorithm>
using std::min_element; using std::max_element;
#include <cctype>
using std::tolower; using std::isspace;
#include <cmath>
#include<map>
using std::map;
#include<utility>
using std::pair; using std::make_pair;
using map_type = std::map<std::string, long>;

ostream& print_vector (ostream &out, const vector<string> &v){
	int i = 0;
	for(auto a : v){
		out << a;
		if(i !=v.size()-1)
			out << ",";
		i++;
	}
	return out;
}

string clean_word(const string& i){
	string result;
	for(auto a : i){
		if(isalpha(a))
			result+=tolower(a);
	}
	return result;
}

vector<string> split(const string &s, char delim){
	string e = s;
	vector<string> r;
	
	while(e.size() !=0){
		long ind = e.find(delim);
		if (ind != -1){
			r.push_back(e.substr(0,ind));
			e.erase(0, ind+1);
		} else{
			r.push_back(e.substr(0,ind));
			e.erase(0);
		}
	}
	return r;
}

ostream& print_map(ostream& out, const map_type& m){
	int i = 0;
	for( auto const& [key, val] : m)
	{
		out << key;        // string (key)
		out << ':';
		out << val;        // string's value
		if(i < m.size()-1)
			out << ",";
		i++;
	}
	return out;
}

bool process_words(map_type& m, string s){
	ifstream fp;
	fp.open(s);
	string x;
	if (!(fp.is_open()))
		return false;
	while (fp) {
		getline(fp, x);
		auto splt = split(x,' ');
		for(auto ele : splt){
			string clean = clean_word(ele);
			if(m.find(clean) != m.end())
				m[clean]++;
			else
				m[clean] = 1;
		}
	}
	return true;
}

double jaccard_similarity(const map_type &a, const map_type &b){
	
	auto akey_count = a.size();
	auto bkey_count = b.size();
	auto a_b_intersection = 0;
	if(akey_count >= bkey_count){
		for( auto const& [key, val] : a)
		{
			if(b.find(key) != b.end())
				a_b_intersection++;// string (key)
		}
	} else {
		for( auto const& [key, val] : b)
		{
			if(a.find(key) != a.end())
				a_b_intersection++;// string (key)
		}
	}
	auto similarity = double(a_b_intersection)/(akey_count+bkey_count-a_b_intersection);
	return similarity;
}

double calc_norm_factor(const map_type &m){
	double squared_total = 0.0;
	
	for( auto const& [key, val] : m)
	{
		squared_total += (val*val);
	}
	double norm_factor = std::sqrt(squared_total);
	return norm_factor;
}


double cosine_similarity_tf(const map_type &a, const map_type &b){
	auto akey_count = a.size();
	auto bkey_count = b.size();
	auto a_norm_factor = calc_norm_factor(a);
	
	std::map<std::string, double> a1;
	for( auto const& [key, val] : a)
	{
		a1[key] = double(val)/double(a_norm_factor);
	}
	
	auto b_norm_factor = calc_norm_factor(b);
	std::map<std::string, double> b1;
	for( auto const& [key, val] : b)
	{
		b1[key] = double(val)/double(b_norm_factor);
	}
	
	
	double cos_similarity;
	if(akey_count >= bkey_count){
		for( auto const& [key, val] : a)
		{
			if(b.find(key) != b.end())
				cos_similarity += (a1[key] * b1[key]);
		}
	} else {
		for( auto const& [key, val] : b)
		{
			if(a.find(key) != a.end())
				cos_similarity += (a1[key] * b1[key]);
		}
	}
	return cos_similarity;
	
}


