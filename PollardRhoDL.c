/*
 * PollardRhoDL.c
 *
 *  Created on: May 7, 2014
 *      Author: amrqura
 */
/*
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"
#include <CommonUtils.h>;

Array S0,S1,S2;
int x,q,d,g;
BIGNUM *Z,*X,* mod,*G,*D;
BN_CTX *t;
int S0Size,S1Size,S2Size;
void P_function(BIGNUM *Z,BIGNUM * p_C0,BIGNUM * p_C1)
{
	// compute P first:

	if(getLocation(&S0,S0Size,getInt(Z))>-1)
	{
		BN_mod_add(p_C1,p_C1,getBigNumber("1"),D,t); // p+t , only will affect the second coeeficient
	}
	else if((getLocation(&S1,S1Size,getInt(Z)))>-1) // 2*p , shall multiply the two coefficient by 2
	{
		BN_mod_mul(p_C0,p_C0,getBigNumber("2"),D,t);
		BN_mod_mul(p_C1,p_C1,getBigNumber("2"),D,t);
	}
	else if((getLocation(&S2,S2Size,getInt(Z)))>-1)
	{
		BN_mod_add(p_C0,p_C0,getBigNumber("1"),D,t);
	}
	// compute Z*
	if(getLocation(&S0,S0Size,getInt(Z))>-1)
		BN_mod_mul(Z,X,Z,mod,t);
	else if((getLocation(&S1,S1Size,getInt(Z)))>-1)
		BN_mod_exp(Z,Z,getBigNumber("2"),mod,t);

	else if((getLocation(&S2,S2Size,getInt(Z)))>-1)
		BN_mod_mul(Z,Z,G,mod,t);
}
/*
int main()
{
	printf("Enter group descriotion ,q :");

		scanf("%d",&q);
		printf("Enter d:");

		scanf("%d",&d);
		printf("\n Enter g:");

		scanf("%d",&g);
		printf("\n Enter X:");

		scanf("%d",&x);

		X = BN_new();
		G=BN_new();
		mod = BN_new();
		D=BN_new();
		t = BN_CTX_new();

		const int size=10;
		char  buf[size];
		snprintf(buf, sizeof(buf), "%d", x);

		BN_dec2bn(&X,buf);


		printf("\n the value of X is %s \n",BN_bn2dec(X));

		BN_dec2bn(&G,toArray(g));
		printf("the value of G is %s \n",BN_bn2dec(G));

		BN_dec2bn(&mod,toArray(q));
		printf("the value of Mod is %s \n",BN_bn2dec(mod));
		BN_dec2bn(&D,toArray(d));
		printf("the value of D is %s \n",BN_bn2dec(D));

		printf("Enter size of S0:");

		scanf("%d",&S0Size);


		printf("Enter size of S1:");

				scanf("%d",&S1Size);


		printf("Enter size of S2:");

				scanf("%d",&S2Size);

		initArray(&S0,S0Size);

		initArray(&S1,S1Size);

		initArray(&S2,S2Size);

		printf("\n filling S0 \n");
		i=0;
		int tmp;
		for(i=0;i<S0Size;i++)
		{
			printf("Enter S0[%d]:",i);
			scanf("%d",&tmp);
			insertArray(&S0,tmp);
		}

		printf("\n filling S1 \n");

		for(i=0;i<S1Size;i++)
		{
			printf("Enter S1[%d]:",i);
			scanf("%d",&tmp);
			insertArray(&S1,tmp);
		}

		printf("\n filling S2 \n");

		for(i=0;i<S2Size;i++)
		{
			printf("Enter S2[%d]:",i);
			scanf("%d",&tmp);
			insertArray(&S2,tmp);
		}

		printf("\n printing S0 \n");
		for(i=0;i<S0Size;i++)
		{
			printf("%d  ",S0.array[i]);
		}
		printf("\n");


		printf("\n printing S1 \n");
		for(i=0;i<S1Size;i++)
		{
			printf("%d  ",S1.array[i]);
		}
		printf("\n");


		printf("\n printing S2 \n");
		for(i=0;i<S2Size;i++)
		{
			printf("%d  ",S2.array[i]);
		}
		printf("\n");

		BIGNUM * U0, * V0,* X_Val, * Y_Val,* X_UO,* G_V0; // X_Val will pbe respresetation of X_K in the table
		BIGNUM * Row_K_C0,* ROW_K_C1; // C0,C1 are coeeficients
		BIGNUM * Tow_K_C0,* TOW_K_C1;// C0,C1 are coeeficients
		U0=BN_new();
		V0=BN_new();
		X_Val =BN_new();
		Y_Val=BN_new();
		X_UO=BN_new();
		G_V0=BN_new();
		ROW_K_C1=BN_new();
		Row_K_C0=BN_new();
		Tow_K_C0=BN_new();
		TOW_K_C1=BN_new();
		// set random value for U0,V0
		BN_rand_range(U0,D);
		BN_rand_range(V0,D);
		// compute X_0, X_0=x^U0*g^V0
		BN_mod_exp(X_UO,X,U0,mod,t);
		BN_mod_exp(G_V0,G,V0,mod,t);
		BN_mod_mul(X_Val,X_UO,G_V0,mod,t);
		BN_mod_mul(Y_Val,X_UO,G_V0,mod,t);
		// compute ROW_0
		BN_dec2bn(&Row_K_C0,BN_bn2dec(V0));
		BN_dec2bn(&ROW_K_C1,BN_bn2dec(U0));

		BN_dec2bn(&Tow_K_C0,BN_bn2dec(V0));
		BN_dec2bn(&TOW_K_C1,BN_bn2dec(U0));
		int k=0;
		BIGNUM * U,* _U,* V,* _V;
		while(1)
		{
			k++;
			P_function(X_Val,Row_K_C0,ROW_K_C1);
			P_function(Y_Val,Tow_K_C0,TOW_K_C1);
			P_function(Y_Val,Tow_K_C0,TOW_K_C1); // second level as recursive
			if(BN_cmp(X_Val,Y_Val)==0)
			{
				V=BN_new();
				U=BN_new();
				_U=BN_new();
				_V=BN_new();
				BN_copy(V,Row_K_C0);
				BN_copy(U,ROW_K_C1);
				BN_copy(_V,Tow_K_C0);
				BN_copy(_U,TOW_K_C1);

				printf("collision at %d, X_%d=%s and Y_%d=%s",k,k,BN_bn2dec(X_Val),k,BN_bn2dec(Y_Val));
				break;
			}
		}
		// compute the gcd
		BIGNUM * sub=BN_new();
		BIGNUM * gcdVal=BN_new();
		BN_mod_sub_quick(sub,U,_U,mod);

		BN_gcd(gcdVal,sub,D,t);
		printf("\n the gcd value  is %s \n",BN_bn2dec(gcdVal));
		if(BN_cmp(gcdVal,getBigNumber("1"))==0) // test equality
		{
			BIGNUM * finalResult=BN_new();
			BIGNUM * inverseValue=BN_new();
			// compute inverse
			BN_mod_inverse(inverseValue,sub,D,t);
			// compute v- _V
			BIGNUM * Vsub=BN_new();
			BN_mod_sub_quick(Vsub,_V,V,D);
			BN_mod_mul(finalResult,Vsub,inverseValue,D,t);
			printf("\n final value is %s",BN_bn2dec(finalResult));

		}
		printf("failure !!!");



}
*/


