/*
 * EllipticCurve.h
 *
 *  Created on: Jun 7, 2014
 *      Author: amrqura
 */
#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
#ifndef ELLIPTICCURVE_H_
#define ELLIPTICCURVE_H_
mpz_t tmpGCD;
int FactorFound=0;
struct Elliptic_Curve
{
	mpz_t a;
	mpz_t b;
	mpz_t p;

};
struct Point
{
	mpz_t x;
	mpz_t y;
};
struct Elliptic_Curve EC;

Point_Addition(struct Point P,struct Point Q,struct Point
		*R)
{
	mpz_mod(P.x,P.x,EC.p);
	mpz_mod(P.y,P.y,EC.p);
	mpz_mod(Q.x,Q.x,EC.p);
	mpz_mod(Q.y,Q.y,EC.p);
	mpz_t temp,slope;
	mpz_init(temp);
	mpz_init_set_ui(slope,0); // init slope
	if(mpz_cmp_ui(P.x,0)==0 && mpz_cmp_ui(P.y,0)==0) // if one point is /infinity
	{
		mpz_set(R->x,Q.x);
		mpz_set(R->y,Q.y);
		return;
	}
	if(mpz_cmp_ui(Q.x,0)==0 && mpz_cmp_ui(Q.y,0)==0)
	{
		mpz_set(R->x,P.x);
		mpz_set(R->y,P.y);
		return;
	}
	if(mpz_cmp_ui(Q.y,0)!=0)
	{
		mpz_sub(temp,EC.p,Q.y); // -Q.y
		mpz_mod(temp,temp,EC.p);
	}
	else
		mpz_set_ui(temp,0);
	if(mpz_cmp(P.y,temp)==0 && mpz_cmp(P.x,Q.x)==0) // p = -q
	{
		mpz_set_ui(R->x,0);
		mpz_set_ui(R->y,0);
		return;
	}
	if(mpz_cmp(P.x,Q.x)==0 && mpz_cmp(P.y,Q.y)==0) // if p=q , point doubling
	{
		Point_Doubling(P,R);
		return;
	}
	else
	{
		mpz_sub(temp,P.x,Q.x); // P.x-Q.x
		mpz_mod(temp,temp,EC.p); // P.x-Q.x mod N
		mpz_gcd(tmpGCD,temp,EC.p);

		if(mpz_cmp_d(tmpGCD,1)!=0 && mpz_cmp(tmpGCD,EC.p)!=0)
		{
			mpz_gcd(tmpGCD,temp,EC.p);
			gmp_printf("factor found which is : %Zd  \n",tmpGCD);
			FactorFound=1;
			mpz_cdiv_q(EC.p,EC.p,tmpGCD);
			gmp_printf("N now is  : %Zd  \n",EC.p);
			return;

		}

		mpz_invert(temp,temp,EC.p);// (P.x-Q.x)^-1
		mpz_sub(slope,P.y,Q.y);//P.Y-Q.Y
		mpz_mul(slope,slope,temp); //(P.Y-Q.Y)/(P.x-Q.x)
		mpz_mod(slope,slope,EC.p); //(P.Y-Q.Y)/(P.x-Q.x) Mod N
		mpz_mul(R->x,slope,slope); // slope^2
		mpz_sub(R->x,R->x,P.x); // slope^2-P.x
		mpz_sub(R->x,R->x,Q.x); //slope^2-P.x-Q.x
		mpz_mod(R->x,R->x,EC.p); //slope^2-P.x-Q.x mod N
		mpz_sub(temp,P.x,R->x); //Xp-Xr
		mpz_mul(R->y,slope,temp);//Xp-Xr*slope
		mpz_sub(R->y,R->y,P.y); //Xp-Xr*slope-Py
		mpz_mod(R->y,R->y,EC.p); //Xp-Xr*slope-Py mod N
		return;
	}
}

Point_Doubling(struct Point P,struct Point *R)
{
	mpz_t slope,temp;
	mpz_init(temp);
	mpz_init(slope);
	if(mpz_cmp_ui(P.y,0)!=0)
	{
		mpz_mul_ui(temp,P.y,2); // 2y
		mpz_mod(temp,temp,EC.p);
		mpz_gcd(tmpGCD,temp,EC.p);
		if(mpz_cmp_d(tmpGCD,1)!=0 && mpz_cmp(tmpGCD,EC.p)!=0)
		{
			mpz_gcd(tmpGCD,temp,EC.p);
			gmp_printf("factor found which is : %Zd \n",tmpGCD);
			mpz_cdiv_q(EC.p,EC.p,tmpGCD);
			FactorFound=1;
			gmp_printf("N now is  : %Zd  \n",EC.p);
			return;
		}
		mpz_invert(temp,temp,EC.p); // (2y mod N) ^-1
		mpz_mul(slope,P.x,P.x); // x^2
		mpz_mul_ui(slope,slope,3); // 3*x^2
		mpz_add(slope,slope,EC.a); // 3*x^2+a
		mpz_mul(slope,slope,temp);// (3*x^2)/(2y)
		mpz_mod(slope,slope,EC.p);// (3*x^2)/(2y) mod N
		mpz_mul(R->x,slope,slope); // s^2
		mpz_sub(R->x,R->x,P.x);// s^2 -x
		mpz_sub(R->x,R->x,P.x); // s^2-2x
		mpz_mod(R->x,R->x,EC.p);//s^2-2x mod N
		mpz_sub(temp,P.x,R->x); // x_p - x_r
		mpz_mul(R->y,slope,temp);// slope*(x_p - x_r)
		mpz_sub(R->y,R->y,P.y);// slope*(x_p - x_r)-y_p
		mpz_mod(R->y,R->y,EC.p); // slope*(x_p - x_r)-y_p mod N
	}
	else
	{
		mpz_set_ui(R->x,0);
		mpz_set_ui(R->y,0);
	}
}
// compute mP and set the result into R
Scalar_Multiplication(struct Point P,struct Point *R,mpz_t m)
{
	FactorFound=0;
	mpz_init(tmpGCD);

	struct Point Q,T;
	mpz_init(Q.x);   mpz_init(Q.y);
	mpz_init(T.x);   mpz_init(T.y);
	long no_of_bits,loop;
	no_of_bits=mpz_sizeinbase(m,2);
	mpz_set_ui(R->x,0);mpz_set_ui(R->y,0);
	if(mpz_cmp_ui(m,0)==0)
		return;
	mpz_set(Q.x,P.x);
	mpz_set(Q.y,P.y);
	if(mpz_tstbit(m,0)==1)
	{mpz_set(R->x,P.x);mpz_set(R->y,P.y);}
	for(loop=1;loop<no_of_bits;loop++)
	{
		if(FactorFound==1)
			return;
		//printf("loop is %d",loop);
		mpz_set_ui(T.x,0);
		mpz_set_ui(T.y,0);
		Point_Doubling(Q,&T);
		mpz_set(Q.x,T.x);
		mpz_set(Q.y,T.y);
		mpz_set(T.x,R->x);
		mpz_set(T.y,R->y);
		if(mpz_tstbit(m,loop))
		{
			Point_Addition(T,Q,R);
		}
	}
}


#endif /* ELLIPTICCURVE_H_ */
