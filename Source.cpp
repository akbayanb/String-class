#include "String.h"
#include <iostream>
#include <cstdarg>
using namespace std;

double print(char* M, int n,  ...) {
	va_list ap;
	double sum = 0;
	va_start(ap, n);
	for (int i = 0; i < n; i++)
	{	if (M[i] == 'i')
			sum += va_arg(ap, int);
		else if (M[i] == 'd')
			sum += va_arg(ap, double);
		else if (M[i] == 'c')
			sum += va_arg(ap, char);
		else if (M[i] == 's')
			sum += va_arg(ap, short int);
		else if (M[i] == 'f')
		sum += va_arg(ap, float);
	}
	va_end(ap);
	return sum;
}

int main() {
	
	 cout<<String::Format("iic", 12, 23, 'F')<<endl;

	system("pause");
	return 0;
}
