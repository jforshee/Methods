
#include <stdio.h>
#include <math.h>

float solution1 = 2.302585093f;
float solution2 = 3252.0f;

/*
 * Trapezoid integration over an interval [a,b]
 * Parameters:
 *		f: pointer to the function being integrated
 *		a, b: endpoints of the interval
 *		n: number of subintervals to compute
 */
float trapezoid(float (*f)(float), float a, float b, int n)
{
	float h = (b - a) / n;
	float sum = (*f)(a) + (*f)(b);
	
	int i;
	for (i = 1; i < n; i++) {
		float x = a + (h * i);
		sum += 2 * (*f)(x);
	}
	
	return (sum * h) / 2.0f;
}

/*
 * Simpson integration over an interval [a,b]
 * Parameters:
 *		f: pointer to the function being integrated
 *		a, b: endpoints of the interval
 *		n: number of subintervals to compute, must be even
 */
float simpson(float (*f)(float), float a, float b, int n)
{
	float h = (b - a) / n;
	float sum = (*f)(a);
	
	int i;
	for (i = 1; i < n; i += 2) {
		float x = a + (h * i);
		sum += 4 * (*f)(x);
	}
	for (i = 2; i < n - 1; i += 2) {
		float x = a + (h * i);
		sum += 2 * (*f)(x);
	}
	
	sum += (*f)(b);
	
	return (h * sum) / 3.0f;
}

/*
 * First function we will test our methods with.
 * f(x) = 1 / x
 */
float function1(float x)
{
	return (1 / x);
}

/*
 * Second function we will test our methods with.
 * f(x) = x^5 + 4x^3 + 2x
 */
float function2(float x)
{
	return (x * x * x * x * x) +
		   (4 * x * x * x) +
		   (2 * x);
}

/*
 * Driver method.
 */
int main()
{
	float a = 1;		/* our interval [a,b] */
	float b = 5;
	
	int i;
	int n_values[5] = { 100, 500, 1000, 5000, 10000 };
	
	for (i = 0; i < 5; i++) {
		int n = n_values[i];
		float trapezoid_func1 = trapezoid(&function1, a, b, n);
		float trapezoid_func2 = trapezoid(&function2, a, b, n);
		float simpson_func1 = simpson(&function1, a, b, n);
		float simpson_func2 = simpson(&function2, a, b, n);
		
		printf("n = %i\n", n);
		printf("function 1: trapezoid: %f\n", trapezoid_func1);
		printf("            error: %f\n", solution1 - trapezoid_func1);
		printf("            simpson's: %f\n", simpson_func1);
		printf("            error: %f\n", solution1 - simpson_func1);
		printf("function 2: trapezoid: %f\n", trapezoid_func2);
		printf("            error: %f\n", solution2 - trapezoid_func2);
		printf("            simpson's: %f\n", simpson_func2);
		printf("            error: %f\n\n", solution2 - simpson_func2);
	}
	
}
