/*
    ==============================================================
                   COPYRIGHT (C) 2025, LIBERTYEVIL
    ==============================================================
     * Licensed under GNU GPL v3
     * Original repository: https://github.com/LIBERTYEVIL/Base64Anlz/
*/

#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern const char base64_encode_tab[64];        
extern const char base64_decode_tab[256];

#define ENT base64_encode_tab
#define DET base64_decode_tab

typedef unsigned char byte;

/* Base64 steganography bits group linked list */
typedef struct b64stg {
    byte bitnum;    // The number of bits
    byte bitsgp;    // Bits from base64 steg
    struct b64stg* nextg;
} b64stg, *b64stgp;



/* Functions */
byte is_not_base64_str (const char* str);
byte if_steg_base64 (const char* b64str);

const char* base64_encode (const char* str);                            // RELEASE
const char* base64_decode (const char* b64str);                         // RELEASE

b64stg  GetBitGroupFromBase64Str (const char* b64str);
b64stg* GetBitListFromBase64Para (char* b64strs[], size_t b64strnum);   // RELEASE LIST
const char* GetStrFromB64stgBits (b64stg* BitList, size_t b64strnum);   // RELEASE

#endif