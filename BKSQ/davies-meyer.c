/** \file davies-meyer.c */
/*
 * File:   davies-meyer.c
 * Author: Alexandros Sivris
 */

#include <stdio.h>
#include <string.h>

#include "bksq.h"
#include "davies-meyer.h"


/**
 * hashes given data using the Davies-Meyer-construction
 * @param data a pointer to the data to be hashed
 * @param data_length The length of the data in bits
 * @param hash a pointer to an array for receiving the hash, must be of size |BLOCKSIZE_BYTE| bytes
 * @return Returns 0, if hashing successful
 */

int main()
{
    uint8_t testdm[144] = {0x56, 0x2b, 0x8b, 0x39, 0x18, 0xd0, 0x49, 0x03, 0xc5, 0x01, 0x76, 0x16, 0xe8, 0xd8, 0xa9, 0x96, 0x46, 0xa8, 0xeb, 0x4b, 0x38, 0x47, 0x5f, 0xda, 0x18, 0xaa, 0xc7, 0x82, 0x9c, 0x0a, 0x3f, 0xba, 0x53, 0x71, 0xe3, 0x33, 0x09, 0x8e, 0x6b, 0x3f, 0x6d, 0xe3, 0xa7, 0x06, 0xca, 0xa1, 0xd1, 0xf4, 0xdc, 0xe0, 0xbc, 0xe8, 0x8a, 0x83, 0x2f, 0x54, 0xe5, 0x3b, 0xce, 0x2c, 0x0a, 0x51, 0x39, 0xfb, 0x9e, 0x27, 0x4e, 0xdd, 0x3a, 0x23, 0xe6, 0x40, 0xc4, 0x1c, 0x2c, 0x49, 0x90, 0xdb, 0x86, 0x6b, 0xf5, 0x26, 0x52, 0xe9, 0x84, 0x35, 0xdb, 0x75, 0xb8, 0x02, 0x09, 0x5c, 0x30, 0x6b, 0xa8, 0xb9, 0x65, 0xde, 0xde, 0x9e, 0x06, 0x50, 0x2b, 0x95, 0xab, 0xb0, 0xfc, 0xbc, 0xf7, 0x32, 0x66, 0xdf, 0xf4, 0xd5, 0x8b, 0xe0, 0xfc, 0x5a, 0xd0, 0x2f, 0x0d, 0xda, 0x6e, 0xe5, 0x31, 0xaa, 0x34, 0xf3, 0x46, 0x99, 0x2d, 0xb4, 0x2a, 0x0b, 0x4e, 0x9c, 0xce, 0x5c, 0x37, 0x35, 0x52, 0x66, 0x8c, 0x39};
    uint8_t hash[12];
    uint8_t checkdm[12] = {0xb7, 0x41, 0x17, 0xd9, 0x98, 0xf8, 0xc7, 0xb9, 0xa9, 0xc5, 0x7c, 0x47};
    uint8_t i;
    printf("\n");
    printf("Teste Davies-Meyer...  ");


    dmhash(testdm, 144 * 8, hash);
    for (i = 0; i < 12; i++) {
        printf("%.02X ",hash[i]);
		}


    printf("\n");
    printf("Fertig!");
    printf("\n\n");

    return 0;
}

uint8_t dmhash(uint8_t const *data, uint32_t const data_length, uint8_t * hash) {
    // sanity checks
    if ((data_length % BLOCKSIZE) != 0) return INVALID_DATA_LENGTH;

	// TODO: put your code for hashing here
    // encryption fct. uint8_t bksq_encrypt(uint8_t const * plain, uint8_t * cyphertext, uint8_t const * key)
    uint8_t out_vector[12],block_data[12];
    uint8_t i,j,l;
    uint8_t total_blocks = data_length / BLOCKSIZE;

    for (i=0;i<12;i++)
        hash[i] = 0;
    l=0;
    for (i=0;i<total_blocks;i++)
    {

        for (j=l;j<l+12;j++)
        {
            block_data[j%12] = data[j];

        }
        l += 12;
        BLOCKCYPHER_ENCRYPT(hash, block_data, out_vector);

        for (j=0;j<12;j++)
            hash[j] ^= out_vector[j];

    }

    return DM_OK;
}

uint8_t gmul(uint8_t a, uint8_t b) {

	uint8_t p = 0;

	uint8_t counter;

	uint8_t carry;

	for (counter = 0; counter < 9; counter++) {

		if (b & 1)

			p ^= a;

		carry = a & 0x80;  /* detect if x^8 term is about to be generated */

		a <<= 1;

		if (carry)

			a ^= 0x11B; /* replace x^8 with x^4 + x^3 + x + 1 */

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



 }



	for (i=0;i<12;i++)

    {

        cyphertext[i] = tmp_output_s[i];

    }

    return BKSQ_ENCRYPT_OK;

}


