#include<stdio.h>
#include<stdlib.h>
#include<openssl/bn.h>

/**
  * Pollard's Rho algorithm for factoring
  * Burton Rosenberg
  * Oct 20, 2004
  *
  * HOW THE METHOD WORKS:
  *
  *    Starting from some value, we repeated apply the function
  *    f(x) = x^2+1 mod n.
  *
  *    Suppose p is a number dividing n. Eventually f(x) mod p
  *    repeats itself. This must happen after p evaluations of f but
  *    normally happens after square root of p evaluation of f.
  *
  *    Once it repeats, it continues to repeat, in a cycle of mod p
  *    values x_1, x_2, x_3, ..., x_k, x_1, x_2, ...
  *    By trying slowing increasing distances between x_i and x_{i+k}
  *    (that is, by trying k=1, 2, 3, and so forth)
  *    we eventually find the k such that x_i =x_{i+k} mod p.
  *    And then gcd(n,x_i-x_{i+k}) = p.
  *
  *    In thinking about this algorithm, consider that f(x) is like
  *    throwing darts into boxes, and we know that soon enough two
  *    darts will be in the same box. Two darts, x_i and x_j, are
  *    in the same box when their difference shares a factor with n.
  *    And after the x_i's begin to cycle (but we can't see this just
  *    yet ... we need to look mod p to see the cycling) the 
  *    difference between x_i and x_j only depends on the spacing i-j.
  *
  *    The algorithm continues to generate x_i as we systematically
  *    trying spacings 1, 2, 3, ..., until we detect the two darts
  *    in the same box, and this also gives us p, the factor of n.
  *
  *    This method can fail entirely, in which case the common factor
  *    found is n itself. Or it can run very slowly, in which case
  *    two darts do not land in the same box until almost all the
  *    boxes have a dart in them alread. Since factoring is hard,
  *    it is expected that any good practical and fast method will
  *    be unpredictable in these ways. However, when it works, it
  *    doubles the bit size of the numbers you can hope to factor.
  *
  *    For example, if a number is the product of two 24 bit numbers,
  *    you can hope to factor in about 4,000 iterations of f(x).
  */

#define DEBUG 0

BN_CTX * bnctx ;
BIGNUM * bn_one ;

void myPrint( BIGNUM * x, char * t ) {
   char * s = BN_bn2dec( x ) ;
   printf("%s%s", s, t ) ;
//   OPENSSL_free(s) ;
   free(s) ;
}

void f( BIGNUM * x, BIGNUM * m ) {
    BN_mod_mul( x, x, x, m, bnctx ) ;
    BN_mod_add( x, x, bn_one, m, bnctx ) ;
}
/*
int main( int argc, char * argv[] )
{

    int i ;
    BIGNUM * bn_pr = BN_new() ;
    BIGNUM * bn_a = BN_new() ;
    BIGNUM * bn_b = BN_new() ;
    BIGNUM * bn_r = BN_new() ;

    bn_one = BN_new() ;
    BN_one(bn_one) ;
    bnctx = BN_CTX_new() ;
    
    if ( argv[1]==NULL ) exit(0) ;

    i = strspn(argv[1],"0123456789") ;
    if ( i!=strlen(argv[1]) ) {
       printf("input error\n") ;
       exit(0) ;
    }

    BN_one(bn_a) ;
    BN_one(bn_b) ;
    BN_dec2bn( &bn_pr, argv[1] ) ;
//    printf("%s\n", BN_bn2dec(bn_pr) ) ;
   
    i = 1 ;
    while ( 1 ) {

	if ( DEBUG ) {
	myPrint( bn_a, " ") ; myPrint( bn_b, "\n") ;
	}

        f(bn_a, bn_pr) ;
        f(bn_b, bn_pr) ;
        f(bn_b, bn_pr) ;
        BN_mod_sub( bn_r, bn_a, bn_b, bn_pr, bnctx ) ;
        BN_gcd( bn_r, bn_r, bn_pr, bnctx ) ;
        if ( BN_cmp( bn_r, bn_pr ) == 0 )  {
           break ;
        }
        if ( BN_cmp( bn_r, bn_one ) != 0 ) {
           break ;
        }

        i++ ;

    }
    myPrint(bn_pr," = ") ;
    myPrint(bn_r," * ") ;
    BN_div( bn_r, bn_one, bn_pr, bn_r, bnctx ) ;
    myPrint(bn_r,"\n") ;
    printf("iter = %d\n", i) ;

}

*/
