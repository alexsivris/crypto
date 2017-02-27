/* 
 * File:   davies-meyer.h
 * Author: Markus Wamser, TUMEISEC
 */

#ifndef DAVIES_MEYER_H
#define	DAVIES_MEYER_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef BLOCKSIZE
#define BLOCKSIZE 96
#endif

#define BLOCKSIZE_BYTE (BLOCKSIZE+7)/8
#define BLOCKCYPHER_ENCRYPT(in, key, out) bksq_encrypt(in, out, key)
   
    
    /**
     * Error values
     */
#define DM_OK 0;
#define INVALID_DATA_LENGTH 1;
    
uint8_t dmhash(uint8_t const *data, uint32_t const data_length, uint8_t * tag);

#ifdef	__cplusplus
}
#endif

#endif	/* DAVIES_MEYER_H */

