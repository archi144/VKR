#ifndef ISPRIME_H
#define ISPRIME_H
#include <math.h>
bool isPrime( long int prime)
{
     long int i, j;

    j = static_cast<long int>(sqrt(prime));

    for ( i = 2; i <= j; i++)
    {
        if ( prime % i == 0 )
        {
            return false;
        }
    }

    return true;
}
#endif // ISPRIME_H
