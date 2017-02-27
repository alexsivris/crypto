/** \file ctrmode.h */
/* Author: markus Wamser, TUEISEC
 */

#ifndef CTRMODE_H
#define	CTRMODE_H

#include "bksq.h"


#ifdef	__cplusplus
extern "C" {
#endif

#ifndef BLOCKSIZE
#define BLOCKSIZE 96 ///< fix the BLOCKSIZE to 96 bits if not defined otherwise
#endif

#define BLOCKSIZE_BYTE (BLOCKSIZE+7)/8 ///< the BLOCKSIZE in bytes, for convenience only
    
#define BLOCKCYPHER_ENCRYPT(in, key, out) bksq_encrypt(in, out, key) ///< dependeny injection, defining the block cypher used
    
    /**
     * A data structure holding all information relevant for en/decryption
     */
    typedef struct {
        uint8_t *data; ///< a pointer to the input data
        uint32_t data_lenght; ///< length of the input data in bits; must be a multiple of the blocklength
        uint8_t const *key; ///< a pointer to the key
        uint8_t const *nonce; ///< a pointer to the nonce to be used for encryption/decryption
        uint8_t nonce_length; ///< the length of the none in bits
    } CONTEXT;
    
    uint8_t ctr(CONTEXT ctx);
    
#define CTR_OK 0; ///< Error/Return value: everything fine
#define INVALID_DATA_LENGTH 1; ///< Error/Return value: data length no good, maybe missing padding
#define INVALID_NONCE_LENGTH 2; ///< Error/Return value: nonce length no good, maybe missing padding   
    
#ifdef	__cplusplus
}
#endif

#endif	/* CTRMODE_H */

