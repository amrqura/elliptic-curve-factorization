/*
 * CommonUtils.h
 *
 *  Created on: May 7, 2014
 *      Author: amrqura
 */
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bn.h>

#ifndef COMMONVARIABLES_H_
#define COMMONVARIABLES_H_

int i; // for all loops

char * toArray(double number)
    {
	 	 const int size=10;
		char  buf[size];
		snprintf(buf, sizeof(buf), "%d", number);
		return buf;
    }

int getInt(BIGNUM * a)
{
	int resultNum;
	sscanf(BN_bn2dec(a), "%d", &resultNum);
	return resultNum;
}

BIGNUM * getBigNumber(char * val)
{
	BIGNUM * result;
	result=BN_new();
	BN_dec2bn(&result,val);
	return result;
}

#endif /* COMMONVARIABLES_H_ */
