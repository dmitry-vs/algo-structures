#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double bodyMassIndex(double m, double h) {
	return m / (h * h);
}

double* quadraticRoots(double a, double b, double c) {
	double dscr = (double)(b * b - 4 * a * c);
	if (dscr < 0)
		return NULL;

	double* ret = (double*)malloc(2 * sizeof(double));
	ret[0] = (-1 * b + sqrt(dscr)) / 2 * a;
	ret[1] = (-1 * b - sqrt(dscr)) / 2 * a;

	return ret;
}

enum Ages {
	Incorrect,
	God,
	Goda,
	Let
};

Ages ageFormat(int age) {
	if (age < 1 || age > 150) {
		return Incorrect;
	}
	
	int lastDigit = age % 10;
	if (lastDigit == 0)
		return Let;
	if (lastDigit == 1)
	{
		if (age % 100 == 11)
			return Let;
		else
			return God;
	}
	if (lastDigit == 2 || lastDigit == 3 || lastDigit == 4)
		return Goda;

	return Let;
}

int main()
{
	printf("Body mass index:\n");
	printf("%f\n\n", bodyMassIndex(78, 1.78));
	
	printf("Quadratic equation: x^2 - 7x + 12 = 0, roots:\n");
	double* roots = quadraticRoots(1, -7, 12);
	printf("%f\n", roots[0]);
	printf("%f\n\n", roots[1]);
	free(roots);

	int age;
	printf("Input age:\n");
	scanf_s("%d", &age);
	Ages ageFmt = ageFormat(age);
	if (ageFmt == God)
		printf("God");
	else if (ageFmt == Goda)
		printf("Goda");
	else if (ageFmt == Let)
		printf("Let");
	else
		printf("Incorrect");

	return 0;
}
