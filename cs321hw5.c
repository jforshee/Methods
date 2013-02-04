
#include <stdio.h>
#include <math.h>

float solution = 1.88988f;

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
 * First function we will test our methods with.
 * f(x) = x^(1/3)
 */
float function1(float x)
{
	return pow(x, 1 / 3.0f);
}

/*
 * Second function we will test our methods with.
 * f(x) = 3x^3
 */
float function2(float x)
{
	return 3 * x * x * x;
}

/*
 * Driver method.
 */
int main()
{
	float xa = 0;		/* our interval [a,b] */
	float xb = 2;
	float ta = 0;
	float tb = pow(2, 1/3.0f);
	
	int i;
	int n_values[3] = { 10, 100, 1000 };
	
	for (i = 0; i < 3; i++) {
		int n = n_values[i];
		float trapezoid_func1 = trapezoid(&function1, xa, xb, n);
		float trapezoid_func2 = trapezoid(&function2, ta, tb, n);
		
		printf("n = %i\n", n);
		printf("function 1: trapezoid: %f\n", trapezoid_func1);
		printf("            error: %f\n", solution - trapezoid_func1);
		printf("function 2: trapezoid: %f\n", trapezoid_func2);
		printf("            error: %f\n", solution - trapezoid_func2);
	}
}	

