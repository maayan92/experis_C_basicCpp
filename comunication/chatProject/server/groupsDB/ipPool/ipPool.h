#ifndef __ipPool_H
#define __ipPool_H

#include "ADTerror.h"
#include <stdio.h>  /* for size_t */

#define IP_ADDRESSES 100 /*Number of ip addresses*/

typedef struct ipPool ipPool; 


/*
    DESCRIPTION:    Creates ip pool.

    RETURN:         Pointer to the new ip pool , if failed returns NULL.
*/
ipPool* IpPoolCreate();
        
/*
	DESCRIPTION:    Frees ip pool.

	INPUT:          _ipPool - Pointer to ip pool that was created in IpPoolCreate(). Should not be NULL.
*/
void IpPoolDestroy(ipPool* _ipPool);

/*
    DESCRIPTION:    Recieve an ip address from ip pool.

    INPUT:          _ipPool -  Pointer to ip pool that was created in IpPoolCreate(). Should not be NULL.
                    _str - string that will receive the ip from _ipPool.

    RETURN:         Value of OK if ip address was removed from the pool and was instered into the value of _str.
                    ERROR_NOT_INITIALIZED if _ipPool was not initialized.
                    ERROR_WRONG_INPUT if the input is flawed.
                    ERROR_UNDERFLOW if the _ipPool is empty.
*/
ErrorCode IpPoolRecieve(ipPool* _ipPool,char* _str);

/*
    DESCRIPTION:    Return an ip address to the ip pool.

    INPUT:          _ipPool -  Pointer to ip pool that was created in IpPoolCreate(). Should not be NULL.
                    _str - string that holds the value of the returned ip address.

    RETURN:         Value of OK if ip address was inserted  successfully to the pool.
                    ERROR_NOT_INITIALIZED if _ipPool was not initialized.
                    ERROR_WRONG_INPUT if the input is flawed.
                    ERROR_ALLOCATION_FAILED if allocation of the returned ip addresses was failed.
*/
ErrorCode IpPoolReturn(ipPool* _ipPool,char* _str);

/*
    DESCRIPTION:    Counts the number of ip addresses in the pool.

    INPUT:          _ipPool -  Pointer to _ipPool that was created in IpPoolCreate()
                    
    RETURN:         The number of ip addresses in the pool.
*/
size_t IpPoolNumOfAddresses(ipPool* _ipPool);


#endif
