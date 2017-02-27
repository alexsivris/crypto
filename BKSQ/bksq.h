/* 
 * File:   bksq.h
 * Author: Markus Wamser, TUMEISEC
 *
 * Created on 28. April 2014, 18:48
 */

#ifndef BKSQ_H
#define	BKSQ_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<stdint.h>
   
#define BKSQ_ENCRYPT_OK 0;

   
uint8_t bksq_encrypt(uint8_t const * plain, uint8_t * cyphertext, uint8_t const * key);


#ifdef	__cplusplus
}
#endif

#endif	/* BKSQ_H */

