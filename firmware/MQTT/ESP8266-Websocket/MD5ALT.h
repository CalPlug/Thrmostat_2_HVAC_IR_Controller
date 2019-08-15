/* Modified Arduino Library for ESP32 (MD5ALT.h)
 * Original Library: MD5.H - header file for MD5C.C
 * Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 * rights reserved.
 * 
 * License to copy and use this software is granted provided that it
 * is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 * Algorithm" in all material mentioning or referencing this software
 * or this function.
 * 
 * License is also granted to make and use derivative works provided
 * that such works are identified as "derived from the RSA Data
 * Security, Inc. MD5 Message-Digest Algorithm" in all material
 * mentioning or referencing the derived work.
 * 
 * RSA Data Security, Inc. makes no representations concerning either
 * the merchantability of this software or the suitability of this
 * software for any particular purpose. It is provided "as is"
 * without express or implied warranty of any kind.
 * These notices must be retained in any copies of any part of this
 * documentation and/or software.
 * 
 * Modified by Navid Bazmoon
 * University of California, Irvine - CalPlug
 */

/* MD5ALT context. */
typedef struct {
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

// Modified from MD5Init to MD5InitALT by NB 12/2018 for ESP32 compatibility 
void MD5InitALT (MD5_CTX *);
// Modified from MD5Update to MD5UpdateALT by NB 12/2018 for ESP32 compatibility 
void MD5UpdateALT (MD5_CTX *, unsigned char *, unsigned int);
// Modified from MD5Final to MD5FinalALT by NB 12/2018 for ESP32 compatibility 
void MD5FinalALT (unsigned char [16], MD5_CTX *);

/* Function used by Websockets implementation */
void MD5 (unsigned char [], unsigned char [], unsigned int);