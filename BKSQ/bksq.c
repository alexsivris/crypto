/** \file bksq.c */
/*
 * File:   bksq.c
 * Author: Alexandros Sivris
 */

#include <stdio.h>

#include "bksq.h"

/* helper functions */

// TODO: put your helper functions here

/** The |bksq_encrypt| ist the main method to encrypt a single block of data with the BKSQ algorithm.
 * Note that we only support 96 bit (12 byte) keys.
 *
 * @param plain points to a 96 bit (12 byte) input-to-be-encrypted
 * @param cyphertext points to a 96 bit (12 byte) array to receive the output
 * @param key provides the 96 bit (12 byte) key for encryption
 * @returns whether operation was successful
 */
uint8_t checksbox(uint8_t input)
{
        char i;
        uint8_t result=0,index=0;
        uint8_t msb = (input & 0xF0 )>> 4;
        uint8_t lsb = input & 0x0F;
        unsigned char s[256] =
{
   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
    index = (msb * 16) + lsb;
    result = s[index];
    printf("\n%d aes index: %d",msb,index );
    return result;
}

int main()
{
    int i=0;
    uint8_t plaintext[12] = {0x00 ,0x01 ,0x02 ,0x03 ,0x04 ,0x05 ,0x06 ,0x07 ,0x08 ,0x09 ,0x0a ,0x0b};
    uint8_t key[12] = { 0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4};
    uint8_t cyphertext[12];
    uint8_t sbox;
    //{0x09,0xd8,0x1a,0x08,0x7e,0xa1,0x14,0xc4,0x6f,0x16,0x7b,0xee};
    bksq_encrypt(plaintext, cyphertext, key);


    return 0;
}
uint8_t gmul(uint8_t a, uint8_t b) {
    /*(c) wikipedia.org*/
	uint8_t p = 0;
	uint8_t counter;
	uint8_t carry;
	for (counter = 0; counter < 9; counter++) {
		if (b & 1)
			p ^= a;
		carry = a & 0x80;
		a <<= 1;
		if (carry)
			a ^= 0x11B;
		b >>= 1;
	}
	return p;
}

uint8_t bksq_encrypt(uint8_t const * plain, uint8_t * cyphertext, uint8_t const * key) {

    // a.) plain in bytes unterteilen - Ergebnis in theta[i][j]-matrix
	char i,j,k = 0,l,r=0;
	uint8_t tmp_output[12],tmp_output_s[12],pi_buf=0,pi_buf2=0,pi_buf4,pi_buf5,pi_buf7;
	uint8_t a_matrix[12];
	uint8_t ct=1;
	uint8_t msb=0,lsb=0,index=0;
	uint8_t test_key[12] = { 0xfd, 0xfd , 0xfd , 0x0a , 0x0a , 0x0a , 0xf1 , 0xf1 , 0xf1 , 0x06 , 0x06 , 0x06};


	//Start SBOX

    uint8_t s[256] =
    {
       0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
       0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
       0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
       0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
       0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
       0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
       0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
       0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
       0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
       0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
       0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
       0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
       0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
       0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
       0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
       0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
    };
    /*EOF SBOX*/
	uint8_t round_key[12],old_key[12];

    for (i=0;i<12;i++)
    {
        round_key[i] = key[i];
        a_matrix[i] = plain[i];
    }
    pi_buf = gmul(2,8);
    printf("0x%.2X \n\n",pi_buf);
	//10 Runden, da 96 Bit
	for (r=0;r<=10;r++)
	{

		/* 1. Linear Transformation */
		if (r)
		{
            for(i=0;i<12;i+=3)
            {
                tmp_output[i] = gmul(3,a_matrix[i]) ^ gmul(2,a_matrix[i+1]) ^ gmul(2,a_matrix[i+2]);
                tmp_output[i+1] = gmul(2,a_matrix[i]) ^ gmul(3,a_matrix[i+1]) ^ gmul(2,a_matrix[i+2]);
                tmp_output[i+2] = gmul(2,a_matrix[i]) ^ gmul(2,a_matrix[i+1]) ^ gmul(3,a_matrix[i+2]);
            }
		}
		else
		{
			for (i=0;i<=9;i+=3)
            {
                tmp_output[i] = gmul(246,a_matrix[i]) ^ gmul(247,a_matrix[i+1]) ^ gmul(247,a_matrix[i+2]);
                tmp_output[i+1] = gmul(247,a_matrix[i]) ^ gmul(246,a_matrix[i+1]) ^ gmul(247,a_matrix[i+2]);
                tmp_output[i+2] = gmul(247,a_matrix[i]) ^ gmul(247,a_matrix[i+1]) ^ gmul(246,a_matrix[i+2]);
            }
            for(i=0;i<12;i++)
            {
                test_key[i] ^= tmp_output[i];
                printf("0x%.2X ", test_key[i]);
            }

            printf("\n");
        }

		//b.) Nichtlineare Transformation mit AES S-box
		if (r)
		{
			for (i=0;i<12;i++)
            {
                msb = (tmp_output[i] & 0xF0 )>> 4;
                lsb = tmp_output[i] & 0x0F;
                index = (msb * 16) + lsb;
                tmp_output_s[i] = s[index];
            }
		}

		//c.) Byte Permutation pi
		if (r)
		{
		  /*  pi_buf = tmp_output_s[4];
		    pi_buf2 = tmp_output_s[5];
            tmp_output_s[4] = tmp_output_s[7];
            tmp_output_s[5] = pi_buf;
            pi_buf = tmp_output_s[6];
            tmp_output_s[6] = pi_buf2;
            tmp_output_s[7] = pi_buf;

            pi_buf = tmp_output_s[8];
            pi_buf2 = tmp_output_s[9];
            tmp_output_s[8] = tmp_output_s[10];
            tmp_output_s[9] = tmp_output_s[11];
            tmp_output_s[10] = pi_buf;
            tmp_output_s[11] = pi_buf2;
*/
            pi_buf = tmp_output_s[1];
            pi_buf2 = tmp_output_s[2];
            pi_buf4 = tmp_output_s[4];
            pi_buf5 = tmp_output_s[5];
            pi_buf7 = tmp_output_s[7];
            tmp_output_s[1] = tmp_output_s[10];
            tmp_output_s[2] = tmp_output_s[8];
            tmp_output_s[4] = pi_buf;
            tmp_output_s[5] = tmp_output_s[11];
            tmp_output_s[7] = pi_buf4;
            tmp_output_s[8] = pi_buf2;
            tmp_output_s[10] = pi_buf7;
            tmp_output_s[11] = pi_buf5;


		}

        if(!r)
        {
            for (i=0;i<12;i++)
            {
                tmp_output_s[i] = tmp_output[i] ^ round_key[i];

            }
        }
		//d.) bitwise round key addition sigma - round key ist 96 bit lang
		else
        {
            for (i=0;i<12;i++)
            {
                tmp_output_s[i] ^= round_key[i];

            }
        }



        //next round

		//psi-fct. auf round key anwenden
            //alten schluessel speichern
            ct = gmul(2,ct);
            for (i=0;i<12;i++)
                old_key[i] = round_key[i];

			//Rotation
			pi_buf = round_key[9];
			round_key[9] = round_key[10];
			round_key[10] = round_key[11];
			round_key[11] = pi_buf;

			//Substitution
			for (i=9;i<12;i++)
            {
                msb = (round_key[i] & 0xF0 )>> 4;
                lsb = round_key[i] & 0x0F;
                index = (msb * 16) + lsb;
                round_key[i] = s[index];
            }


            for (i=0;i<3;i++)
            {
                round_key[i] = round_key[9+i] ^ old_key[i];
            }

            //xor ct und a0
			round_key[0] ^= ct;
            for (k=1;k<3;k++)
				round_key[k] ^= 0;

            for (k=3;k<12;k++)
                round_key[k] = round_key[k-3] ^ old_key[k];

        for (i=0;i<12;i++)
        {
            a_matrix[i] = tmp_output_s[i];
        }

        printf("rho %d:",r);
        for (i=0;i<12;i++)
        {
            printf("%.2X ",tmp_output_s[i]);
        }
        printf("\nct: %.2X\n",ct);
        printf("key %d:",r+1);
        for (i=0;i<12;i++)
        {
            printf("%.2X ",round_key[i]);
        }
        printf("\n");

	}

	for (i=0;i<12;i++)
    {
        cyphertext[i] = tmp_output_s[i];
    }
    return BKSQ_ENCRYPT_OK;
}
