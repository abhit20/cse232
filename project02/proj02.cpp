#include <iomanip> // For formatted output
#include <iostream> // For cin, cout, and system
#include <cmath> // For math
using std::cin; using std::cout; using std::endl;

int main (){
	
	long long Int1, Int2;
	cin >> Int1 >> Int2;
	
	long startNumberForLargestSequence = 0;
	long largestSequenceNumber = 0;
	
	long startNumberForLongestSequence = 0;
	long maxSequenceLength = 0;
	
	if (Int1<Int2) {

		for(Int1; Int1<=Int2; Int1++){
			long a = Int1;
			long sequenceLength = 0;
			while (a != 1)
			{
				long nextTerm = 0;
				if (a%2 == 0)
					nextTerm  = floor(pow(a,0.5));
				else
					nextTerm = floor(pow(a,1.5));
				if(largestSequenceNumber<nextTerm){
					startNumberForLargestSequence = Int1;
					largestSequenceNumber = nextTerm;
				}
				a = nextTerm;
				sequenceLength++;
			}
			
			if(maxSequenceLength<sequenceLength){
				startNumberForLongestSequence = Int1;
				maxSequenceLength = sequenceLength;
			}
		}
		
		cout << startNumberForLongestSequence << " " << maxSequenceLength << endl;
		cout << startNumberForLargestSequence << " " << largestSequenceNumber << endl;
		
	} else {
		cout << "Error" << endl;
	}
	
}

