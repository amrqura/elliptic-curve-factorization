/*
 * CRTDL.c

 *
 *  Created on: May 8, 2014
 *      Author: amrqura
 */
/*
#include "DynamicArray.h""
#include "CommonUtils.h"

Array * primeFactors(int n)
{
	Array * result;
	initArray(&result,1);
    // Print the number of 2s that divide n
    while (n%2 == 0)
    {
        insertArray(&result,2);
        n = n/2;
    }

    // n must be odd at this point.  So we can skip one element (Note i = i +2)
    int i = 3;
    for ( i = 3; i <= sqrt(n); i = i+2)
    {
        // While i divides n, print i and divide n
        while (n%i == 0)
        {
        	insertArray(&result,i);
            n = n/i;
        }
    }

    // This condition is to handle the case whien n is a prime number
    // greater than 2
    if (n > 2)
    	insertArray(&result,n);
}

int main()
{
	Array * Factors=primeFactors(20);
	i=0;
	for(i=0;i<3;i++)
		printf("%d",Factors->array[i]);

}
*/
