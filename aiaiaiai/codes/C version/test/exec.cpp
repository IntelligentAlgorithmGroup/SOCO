#include <iostream>
#include "func.h"
using namespace std;
int main()
{
	Init_x();
	//for (int i = 1; i <= 30; ++i)
	//{
	//	funcnum = i;
	//	printf("f(%d):", i);
	//	if (i != 2) 
	//	{
	//		printf("\tPSO: "); 
	//		PSO();
	//		printf("\t\tDE: ");
	//		DE();
	//	}
	//	else printf("\tError!\n");
	//}
	// funcnum = 1;
	// PSO();
	// DE();

	cout << "Please enter the number of the function you want to see" << endl;
	cin >> funcnum;
	cout << "you chose function ("<< funcnum << ")" << endl;
	if(funcnum == 2)	printf("Error\n");
	else{
		printf("PSO:\n");
		PSO();
		printf("DE:\n");
		DE();
	}
//	system("pause");
	return 0;

}
