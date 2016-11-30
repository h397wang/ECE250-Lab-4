


#include <iostream>

using namespace std;

int main(){
	
	int n = 5;
	int ** array = new int*[n];
	for (int i = 0; i < n; i++){
		
		array[i] = new int[n];
	}
	
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			
			array[i][j] = i*j;
			cout << array[i][j] << endl;
		}
	}
		
}

