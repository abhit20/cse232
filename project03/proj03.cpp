#include<iostream>
#include<cmath>
using std::cout; using std::cin; using std::endl; using std::boolalpha;

bool is_prime(long n){
	int j = 0;
	if(n%2 != 0){
		for(int i=3;i<=sqrt(n);i+=2) {
			if(n%i==0) {
				j++;
			}
		}
		if (j==0){
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
	return 0;
}

bool is_powerful(long n){
	bool bol = false;
	for(int i =2;i <n;++i) {
		if ((n%i) == 0){
			if(is_prime(i)==true){
				if(n%(i*i) == 0){
					bol = true;
				} else {
					bol = false;
				}
			}
		}
	}
	return bol;
	return 0;
}


bool is_perfect_power(long n){
	for(int i =2; pow(2,i)<=n;i++){
		int root = round(pow(n, 1.0/i));
		if(pow(root,i) == n){
			return true;
		}
	}
	return false;
}

bool is_achilles(long n){
	if (is_powerful(n) == true){
		if(is_perfect_power(n) == false){
			return true;
		}
	}
	return false;
}

// main is below. You cannot modify main
int main (){
	cout << boolalpha;
	
	int test_case;
	cin >> test_case;
	
	switch (test_case){
			
			
		case 1 : {
			long num;
			cin >> num;
			cout <<  is_prime(num) << endl;
			break;
		} // of case 1
			
		case 2 : {
			long num;
			cin >> num;
			cout << is_powerful(num) << endl;
			break;
		} // of case 2
			
		case 3 : {
			long num;
			cin >> num;
			cout << is_perfect_power(num) << endl;
			break;
		} // of case 3
			
		case 4 : {
			long num;
			cin >> num;
			cout << is_achilles(num) << endl;
			break;
		} // of case 4
			
	} // of switch
} // of main

