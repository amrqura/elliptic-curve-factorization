/*
 * BabyStepGaintStepDL.c
 *
 *  Created on: May 1, 2014
 *      Author: amrqura
 */
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <CommonVariables.h>

unsigned char key[16], iv[16];

/*
int main()
{
	printf("Enter group descriotion ,q :");
	int q;
	scanf("%d",&q);

	printf("Enter d:");
	int d;
	scanf("%d",&d);

	printf("\n Enter g:");
			int g;
			scanf("%d",&g);


	printf("\n Enter X:");
		int x;
		scanf("%d",&x);

	int m =ceil(sqrt(d));

	Array babyArray;
	initArray(&babyArray,m);

	BIGNUM *X,* mod,*b,*c,*I,* G,* res;
	BN_CTX *t;
	t = BN_CTX_new();
	BN_CTX_init(t);
	X = BN_new();
	b = BN_new();
	c = BN_new();
	mod = BN_new();
	I= BN_new();
	G=BN_new();
	res=BN_new();

	const int size=10;
	char  buf[size];
	snprintf(buf, sizeof(buf), "%d", x);

	BN_dec2bn(&X,buf);

	BN_dec2bn(&G,toArray(g));
	BN_dec2bn(&mod,toArray(q));

	int i=0;
	for( i=0;i<m;i++)
	{
		BN_dec2bn(&I,toArray(i));
		BN_mod_exp(c,G,I,mod,t);
		BN_mod_mul(res,c,X,mod,t);
		int resultNum;
		sscanf(BN_bn2dec(res), "%d", &resultNum);
		insertArray(&babyArray,resultNum);
	}
	// start gaint step
	BIGNUM *GaintStepValue;
	GaintStepValue= BN_new();
	BIGNUM *KM;
	KM=BN_new();
	i=0;
	while(1)
	{
		BN_dec2bn(&I,toArray(i));
		BN_dec2bn(&KM,toArray(i*m));
		BN_mod_exp(GaintStepValue,G,KM,mod,t);
		int currentResult;
		sscanf(BN_bn2dec(GaintStepValue), "%d", &currentResult);
		int j;
		for(j=0;j<m;j++)
		{
			if(babyArray.array[j]==currentResult)
			{
				int finalResult=(i*m)-j;
				printf("discrete log for %d is %d",x,finalResult);
				freeArray(&babyArray);
				exit(0);
			}
		}
		i++;


	}
}
*/
