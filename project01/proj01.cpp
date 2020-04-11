#include <iostream>
#include <iomanip>
using std::cout; using std::cin; using std::setprecision; using std::fixed; using std::endl;

int main() {
	
	auto firstNumberReal = float{0.0};
	auto firstNumberImaginary = float{0.0};
	auto secondNumberReal = float{0.0};
	auto secondNumberImaginary = float{0.0};
	
	cout << "";
	cin >> firstNumberReal;
	cout << "";
	cin >> firstNumberImaginary;
	cout << "";
	cin >> secondNumberReal;
	cout << "";
	cin >> secondNumberImaginary;
	
	float sumReal = (firstNumberReal + secondNumberReal);
	float sumImaginary = (firstNumberImaginary + secondNumberImaginary);
	float differenceReal = (firstNumberReal - secondNumberReal);
	float differenceImaginary = (firstNumberImaginary - secondNumberImaginary);
	float productReal = (firstNumberReal * secondNumberReal) - (firstNumberImaginary * secondNumberImaginary);
	float productImaginary = (firstNumberReal * secondNumberImaginary) + (firstNumberImaginary * secondNumberReal);
	float quotientReal = (firstNumberReal * secondNumberReal) - (firstNumberImaginary * -secondNumberImaginary);
	float quotientImaginary = (firstNumberReal * -secondNumberImaginary) + (firstNumberImaginary * secondNumberReal);
	float quotientDenominator = (secondNumberReal * secondNumberReal) - (secondNumberImaginary * -secondNumberImaginary);
	
	
	cout << setprecision(2) << fixed << sumReal << " + " << sumImaginary << "i" << endl;
	cout << setprecision(2) << fixed << differenceReal << " + " << differenceImaginary << "i" << endl;
	cout << setprecision(2) << fixed << productReal << " + " << productImaginary << "i" << endl;
	cout << setprecision(2) << fixed << quotientReal/quotientDenominator << " + " << quotientImaginary/quotientDenominator << "i" << endl;
}

