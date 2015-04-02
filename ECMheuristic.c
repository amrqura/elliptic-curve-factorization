/*
 * ECMheuristic.c
 *
 *  Created on: Jun 14, 2014
 *      Author: amrqura
 */
#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
#include<math.h>
#include "DynamicArray.h"

// check if X is Y smooth or no
// return 0 if false , 1 if true;
// check if x is divisible by all primes from Y up to sqrt(x)
int isSmooth(mpz_t X,mpz_t Y)
{
	mpz_t max;
	mpz_init(max);
	mpz_cdiv_q_ui(max,X,2); // get the square root of X
	gmp_printf("\n   root %Zd \n", max);

	mpz_t comparisonGCD;
	mpz_t tmpPrime;
	mpz_init(tmpPrime);
	mpz_init(comparisonGCD);
	mpz_nextprime(tmpPrime,Y); // get first prime after Y
	gmp_printf("\n   tmpPrime %Zd \n", tmpPrime);

	while(mpz_cmp(tmpPrime,max)<0)
	{
		gmp_printf("\n   tmpPrime %Zd \n", tmpPrime);

		mpz_gcd(comparisonGCD,tmpPrime,X);
		gmp_printf("\n   comparisonGCD %Zd \n", comparisonGCD);
		//int compare=mpz_cmp_ui(comparisonGCD,1);
		if(mpz_cmp_ui(comparisonGCD,1)>0)
			return 0;
		mpz_nextprime(tmpPrime,tmpPrime);
	}
	return 1;
}


double getProbablityinN(int x,int y)
{
	double val=log(x)/log(y);
	mpz_t a;
	mpz_init(a);
	mpz_set_ui(a,val);
	mpz_pow_ui(a,a,-val);
	return mpz_get_ui(a);
}



double getProbablity(int p)
{
	return (SiFunction(p+1+sqrt(p))-SiFunction(p+1-sqrt(p)))/(4*sqrt(p));
}


long factorial(int n)
{
  int c;
  long result = 1;

  for (c = 1; c <= n; c++)
    result = result * c;

  return result;
}


Array * getPrimesUpToN(int n)
{

	mpz_t N;
	mpz_init(N);
	mpz_set_ui(N,n);

	Array * result;

	initArray(&result,1);
	printf("%d",n);

	mpz_t tmpPrime;
	mpz_init(tmpPrime);
	mpz_set_ui(tmpPrime,1);

	mpz_nextprime(tmpPrime,tmpPrime); // get first prime after 1


	int compare=mpz_cmp_si(tmpPrime,n);

	int insertedVal;
	while(compare<=0)
	{
		insertedVal=mpz_get_ui(tmpPrime);

		insertArray(&result,insertedVal);
		mpz_nextprime(tmpPrime,tmpPrime); //
		gmp_printf("\n   tmpPrime %Zd \n", tmpPrime);
		compare=mpz_cmp_ui(tmpPrime,n);
	}
	int nn=result->usedSize;
	printf("usedSize=%d",nn);

	return result;

}

double SiFunction(int X,int B)
{
	Array * b=getPrimesUpToN(20);
	printf("%d",b->usedSize);
	int n=b->usedSize; // number of primes till B
	double Fact=factorial(n);
	double testVal=1;
	for(i=0;i<n;i++)
	{
		testVal*=(log(X)/log(b->array[i]));

	}
	return testVal/Fact;
}


int main()
{
	int x=1000000;
	double p=sqrt(x);
	int y=30;
	double p1=getProbablityinN(x,y);
	double p2=getProbablity(p);
	while(p1!=p2)
	{
		x+=100;
		p=sqrt(x);
		y+=100
		p1=getProbablityinN(x,y);
		p2=getProbablity(p);
	}
}
