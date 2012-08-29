#include <iostream>
using namespace std;

const int SIZE = 125;

struct loc{
	short int x;
	short int y;
	short int z;
};
loc location[SIZE];

loc setFirstDim(loc location[SIZE]){

	int count = 0;
	for(short int i=1; i <= 5; i++){
		for(short int j=1; j <= 5; j++){
			for(short int k=1; k <= 5; k++){
				location[count].x = i;
				location[count].y = j;
				location[count].z = k;

				count++;
			}
		}
	}
		
	return location[SIZE];
		
}


int main(){
	
	location[SIZE] = setFirstDim(location);
	
	for(int i =0; i<125; i++){
		cout << location[i].x << location[i].y << location[i].z << "\n";
	}

	return 0;
}