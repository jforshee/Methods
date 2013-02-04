#include <stdio.h>

float x_squared(float x);
float sin(float x);
float cos(float x);
int factorial(int n);
float pow(float x, int n);
float abs(float x);
float estimate_error(float x);

int main()
{
	/*
	 * We use the non-linear equation x^2 = sin(x). The expected
	 * non-zero root is x = 0.876726, so we start with an initial
	 * guess of x_0 = 1.
	 */
	float x_0 = 1.0f, d;
	int trial;
	
	for (trial = 0; trial < 20; trial++) {
		d = (x_squared(x_0) - sin(x_0)) / ((2 * x_0) - cos(x_0));
		x_0 = x_0 - d;	/* Self-populates */
	}

	printf("Estimated root: %f\n", x_0);
	printf("True error: %f\n", abs(0.876726f - x_0));
	printf("Estimated error: %f\n", estimate_error(x_0));

	return 0;
}

float x_squared(float x)
{
	return x * x;
}

/*
 * Taylor series approximation of sin(x), to 4 terms, which
 * is sufficiently accurate for our use.
 */
float sin(float x)
{
	return (
			x
			- (pow(x, 3) / factorial(3))
			+ (pow(x, 5) / factorial(5))
			- (pow(x, 7) / factorial(7))
		   );
}

/*
 * Taylor series approximation of cos(x), to 4 terms, which
 * is suffficiently accurate for our use.
 */
float cos(float x)
{
	return (
			1
			- (pow(x, 2) / factorial(2))
			+ (pow(x, 4) / factorial(4))
			- (pow(x, 6) / factorial(6))
			);
}

/* Naive factorial implementation. */
int factorial(int n)
{
	int product = 1, m;
	for (m = 2; m <= n; m++)
		product = product * m;

	return product;
}

/* Returns x to an integer power. */
float pow(float x, int n)
{
	float product = 1, m;
	if (n == 0) return 1;

	for (m = 0; m < n; m++)
		product = product * x;
	
	return product;
}

/* Absolute value of x */
float abs(float x)
{
	if (x < 0)
		return (x * -1);
	return x;
}

float estimate_error(float x_n)
{
	float f_x = x_squared(x_n) - sin(x_n);
	float df_x = (2 * x_n) - cos(x_n);

	return abs(f_x / df_x);
}
