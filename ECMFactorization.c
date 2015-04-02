/*
 * ECMFactorization.c
 *
 *  Created on: Jun 6, 2014
 *      Author: amrqura
 */
#include <stdio.h>
#include <stdlib.h>
#include "EllipticCurve.h"
mpz_t N, A, X,Y;
mpz_t tmp, tmp2, G;
mpz_t SY, TX, AX, B,K;
int B1;
gmp_randstate_t gmpRandState;
int comparison;

clearVariables()
{
	mpz_clear(N);
	mpz_clear(X);
	mpz_clear(Y);
	mpz_clear(A);
	mpz_clear(SY);
	mpz_clear(TX);
	mpz_clear(AX);
	mpz_clear(B);
	mpz_clear(G);
	mpz_clear(tmp);
	mpz_clear(tmp2);
	mpz_clear(G);
	mpz_clear(K);
	/* Clean up resources occupied by compensated */
	  gmp_randclear(gmpRandState);
}

void modular_multiplication_withInt(mpz_t * r, mpz_t  a,int  b,mpz_t  mod)
{
	mpz_mul_ui (r, a, b);
	mpz_mod (r, r, mod);
}

void modular_multiplication(mpz_t * r, mpz_t  a,mpz_t  b,mpz_t  mod)
{
	mpz_mul (r, a, b);
	mpz_mod (r, r, mod);
}
void modular_subtract(mpz_t * r, mpz_t  a,mpz_t  b,mpz_t  mod)
{
	mpz_sub (r, a, b);
	mpz_mod (r, r, mod);
}

void modular_add(mpz_t * r, mpz_t  a,mpz_t  b,mpz_t  mod)
{
	mpz_add (r, a, b);
	mpz_mod (r, r, mod);
}

/*
 * for p in prime_range(B1):
    k = k*p^suitableExponent(p)
 */
 getK(mpz_t * K)
 {
	 mpz_t currentPrime;
	 mpz_init(currentPrime);
	 mpz_t tmpVal;
	mpz_init(tmpVal);
	 while(1)
	 {
		 mpz_nextprime(currentPrime,currentPrime);
		 int compareResult;
		 compareResult=mpz_cmp_ui(currentPrime,B1);
		 if(compareResult>0)
		 {
			 mpz_clear(currentPrime);
			 mpz_clear(tmpVal);
			 return;
		 }

		 int a=suitableExponent(currentPrime);
		 mpz_pow_ui(tmpVal,currentPrime,a); //
		 mpz_mul(K,K,tmpVal);

	 }
 }

getFactor()
{
	//3. Choose randomly x, y, a ∈ ZN.
		do
		{
			mpz_urandomm(X,gmpRandState,N);
			mpz_urandomm(Y,gmpRandState,N);
			mpz_urandomm(A,gmpRandState,N);
			//4. Set b = (y2 − x3 − ax) modulo N.
			mpz_init(SY);
			mpz_init(TX);
			mpz_init(AX);
			mpz_init(B);
			mpz_powm_ui(SY, Y, 2,N);
			mpz_powm_ui(TX, X, 3,N);
		    modular_multiplication(& AX, A, X,N);
			modular_subtract(&B,SY,TX,N);
			modular_subtract(&B,B,AX,N);
			//Compute g = gcd(4a3 + 27b2,N).
			mpz_init(tmp);
			mpz_powm_ui(tmp,A,3,N);
			modular_multiplication_withInt(&tmp,tmp,4,N);
			mpz_init(tmp2);

			mpz_powm_ui(tmp2,B,2,N);

			modular_multiplication_withInt(&tmp2,tmp2,27,N);
			modular_add(&tmp,tmp,tmp2,N);
			mpz_init(G);
			mpz_gcd(G,tmp,N);
			comparison=mpz_cmp(G,N);

		}
		while(comparison==0);
		comparison=mpz_cmp_ui(G,1);
		if(comparison>0)
		{
			gmp_printf("\n we found one factor which is  %Zd \n", G);
			mpz_cdiv_q(N,N,G);
			//clearVariables();
			return;
		}
		mpz_set(EC.a,A);
		mpz_init(EC.a);
		mpz_init(EC.b);
		mpz_init(EC.p);
		mpz_set(EC.b,B);
		mpz_set(EC.p,N);
		struct Point ECMPoint;
		mpz_init(ECMPoint.x);
		mpz_init(ECMPoint.y);
		mpz_set(ECMPoint.x,X);
		mpz_set(ECMPoint.y,Y);
		mpz_init(K);
		mpz_set_ui(K,1);
		getK(&K);
		//fact(40,&factorofNum);
		struct Point resultPoint;
		mpz_init(resultPoint.x);
		mpz_init(resultPoint.y);
		Scalar_Multiplication(ECMPoint,&resultPoint,&K);
		if(FactorFound==0)
		{
			B1=B1*2;
			getFactor();
		}
}

 int suitableExponent(mpz_t p)
 {
	 mpz_t tmpValue;
	 mpz_init(tmpValue);
	 mpz_set_ui(tmpValue,1);
	 int result=1;
	 while(1)
	 {
		 mpz_pow_ui(tmpValue,p,result);
		 int comparisonResult;
		 comparisonResult=mpz_cmp_ui(tmpValue,B1);
		 if(comparisonResult>=0)
			 return result-1;
		 result++;
	 }
 }


 int main()
 {


 	B1=10000;
 	char n[100];
 	//BIGNUM * N,* A,* X,*Y;
 	printf("Enter the number to Factor N :");
 	scanf("%s",&n);
 	mpz_init(N);
 	mpz_set_str(N,n,10);
 	mpz_init(X);
 	mpz_init(Y);
 	mpz_init(A);
 	// Initialize the random state with default algorithm... //
 	gmp_randinit_default(gmpRandState);

 	int PrimeTest;

 	int comparison=mpz_cmp_ui(N,1);
 	while(comparison>0)
 	{
 		PrimeTest=mpz_probab_prime_p(N,10);
 		if(PrimeTest >0)
 		{
 			gmp_printf("\n   number  %Zd  is prime \n", N);
 			exit(0);
 		}
 		getFactor();
 		if(FactorFound==1)
 			mpz_set(N,EC.p);
 	}


 	//clearVariables();

