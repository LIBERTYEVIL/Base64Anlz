/*
    ==============================================================
                   COPYRIGHT (C) 2025, LIBERTYEVIL
    ==============================================================
     * Licensed under GNU GPL v3
     * Original repository: https://github.com/LIBERTYEVIL/Base64Anlz/
*/

#include "base64.h"

const char base64_encode_tab[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

const char base64_decode_tab[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
    -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

byte is_not_base64_str (const char* str)
{
    byte ret = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (DET[str[i]] != -1) continue;
        else if(str[i] == '=' && (str[i+1]=='='||str[i+1]=='\0')) continue;
        else
        {
            ret = 1;
            break;
        }
    }
    return ret;
}

const char* base64_encode (const char* str) 
{
    const size_t len = strlen(str), b64len = len / 3 * 4 + (len%3==0 ? 1 : 5);
    if (len == 0) return NULL;
    char* b64str = (char*) calloc(b64len + 1, sizeof(char));
    if (b64str==NULL) return NULL;
    size_t idx = 0, b64idx=0, l = len;
    byte chr[3] = {0,0,0}, sec[4] = {0,0,0,0};

    while (l >= 3)
    {
        for (byte i=0; i<3; i++) chr[i] = str[idx++];
        sec[0] = chr[0] >> 2;
        sec[1] = ((chr[0] & 0x03) << 4) + ((chr[1] & 0xf0) >> 4);
        sec[2] = ((chr[1] & 0x0f) << 2) + ((chr[2] & 0xc0) >> 6);
        sec[3] = chr[2] & 0x3f;
        for (byte i=0; i<4; i++) b64str[b64idx++] = ENT[sec[i]];
        l -= 3;
    }

    if (l == 2)
    {
        chr[0] = str[idx++], chr[1] = str[idx];
        sec[0] = chr[0] >> 2;
        sec[1] = ((chr[0] & 0x03) << 4) + ((chr[1] & 0xf0) >> 4);
        sec[2] = (chr[1] & 0x0f) << 2;
        for (byte i=0; i<3; i++) b64str[b64idx++] = ENT[sec[i]];
        b64str[b64idx++] = '=';
    }
    else if (l == 1) 
    {
        chr[0] = str[idx],
        sec[0] = chr[0] >> 2;
        sec[1] = (chr[0] & 0x03) << 4;
        for (byte i=0; i<2; i++) b64str[b64idx++] = ENT[sec[i]];
        b64str[b64idx++] = '=';
        b64str[b64idx++] = '=';
    }
    b64str[b64idx++] = '\0';
    return (const char*)b64str;
}

const char* base64_decode (const char* b64str) 
{
    const size_t b64len = strlen(b64str);
    if (b64len == 0) return NULL;
    const byte sig_num = ((b64str[b64len-2]=='=')&&(b64str[b64len-1]=='=')) ? 2 : (b64str[b64len-1]=='=' ? 1 : 0);
    const size_t objlen = b64len / 4 * 3 - sig_num + 1;

    char* objstr = (char*) calloc(objlen + 1, sizeof(char));
    if (objstr==NULL) return NULL;
    size_t b64idx = 0, objidx=0, l = b64len - sig_num;
    byte dec[3] = {0,0,0}, sec[4] = {0,0,0,0};

    while (l >= 4)
    {
        for (byte i = 0; i < 4; i++) sec[i] = DET[b64str[b64idx++]];
        dec[0] = (sec[0] << 2) + ((sec[1] & 0x30) >> 4);
        dec[1] = ((sec[1] & 0x0f) << 4) + ((sec[2] & 0x3c) >> 2);
        dec[2] = ((sec[2] & 0x03) << 6) + sec[3];
        for (byte i = 0; i < 3; i++) objstr[objidx++] = dec[i];
        l -= 4;
    }
    if (l == 3)
    {
        for (byte i = 0; i < 3; i++) sec[i] = DET[b64str[b64idx++]];
        dec[0] = (sec[0] << 2) + ((sec[1] & 0xc0) >> 4);
        dec[1] = ((sec[1] & 0x0f) << 4) + ((sec[2] & 0x3c) >> 2);
        objstr[objidx++] = dec[0], objstr[objidx++] = dec[1];
    }
    else if (l == 2)
    {
        for (byte i = 0; i < 2; i++) sec[i] = DET[b64str[b64idx++]];
        dec[0] = (sec[0] << 2) + ((sec[1] & 0xc0) >> 4);
        objstr[objidx++] = dec[0];
    }
    objstr[objidx++] = '\0';
    return (const char*)objstr;
}

byte if_steg_base64 (const char* b64str)
{
    const char* decstr = base64_decode(b64str);
    const char* recstr = base64_encode(decstr);
    byte ret = ((b64str[strlen(b64str) - 1] == '=') && (strcmp(b64str, recstr) != 0)) ? 1 : 0;
    free((void*)decstr);
    free((void*)recstr);
    return ret;
}

// TODO:

b64stg GetBitGroupFromBase64Str (const char* b64str)
{
    b64stg BitG;
    BitG.bitnum = 0;
    BitG.bitsgp = 0;
    BitG.nextg = NULL;

    const size_t b64len = strlen(b64str);
    const byte sig_num = ((b64str[b64len-2]=='=')&&(b64str[b64len-1]=='=')) ? 2 : (b64str[b64len-1]=='=' ? 1 : 0);
    
    if (sig_num == 2)
    {
        BitG.bitnum = 4;
        BitG.bitsgp = (DET[b64str[b64len - 3]]) & 0x0f;
    }
    else if (sig_num == 1)
    {
        BitG.bitnum = 2;
        BitG.bitsgp = (DET[b64str[b64len - 2]]) & 0x03;
    }
    else
    {
        BitG.bitnum = 0;
        BitG.bitsgp = 0;
    }
    return BitG;
}

b64stg* GetBitListFromBase64Para (char* b64strs[], size_t b64strnum)
{
    b64stgp NodePtr = NULL, HeadNodePtr = NULL;
    NodePtr = HeadNodePtr = calloc(1, sizeof(b64stg));
    if (HeadNodePtr == NULL) return NULL;
    
    for (size_t str_counter = 0; str_counter < b64strnum; str_counter++)
    {
        *NodePtr = GetBitGroupFromBase64Str(b64strs[str_counter]);
        NodePtr -> nextg = calloc(1, sizeof(b64stg));
        if (NodePtr -> nextg == NULL) return NULL;
        else NodePtr = NodePtr -> nextg;
    }
    return HeadNodePtr;
}

const char* GetStrFromB64stgBits (b64stg* BitList, size_t b64strnum)
{
    // Initialize vars
    size_t TotalNum = 0;    // Total bits number -> Total bytes number 
    byte OutputByte = 0;    // A after-working whole byte to save
    byte FilledBNum = 0;    
    byte BackupBits = 0;
    byte BackupFlag = 0;
    char* FinalStr = NULL;
    char* FinalStrPtr = NULL;
    b64stgp pointer = BitList;
    const byte AndMap[5] = {0x00, 0x00, 0x03, 0x00, 0x0f};

    // Read once to create a buffer
    for (size_t str_counter = 0; str_counter < b64strnum; str_counter++)
    {
        if (pointer != NULL) 
        {
            TotalNum += pointer -> bitnum;
            pointer = pointer -> nextg;
        }
    }
    if (TotalNum % 8 == 0) TotalNum /= 8;
    else
    {
        TotalNum /= 8;
        TotalNum ++;
    }
    TotalNum ++;
    FinalStr = calloc(TotalNum, sizeof(char));
    if(FinalStr == NULL) return NULL;
    FinalStrPtr = FinalStr;
    pointer = BitList;

    // Read again and get final string
    for (size_t str_counter = 0; str_counter < b64strnum; str_counter++)
    {
        if (pointer != NULL)
        {
            if (pointer -> bitnum == 0) pointer = pointer -> nextg;
            else if (FilledBNum + pointer -> bitnum <= 8)
            {
                OutputByte <<= pointer -> bitnum;
                OutputByte += (pointer -> bitsgp & AndMap[pointer -> bitnum]);

                if (FilledBNum + pointer -> bitnum == 8)
                {
                    FilledBNum = 0;

                    *(FinalStrPtr++) = OutputByte;
                    OutputByte = 0;
                }
                else FilledBNum += pointer -> bitnum;

                pointer = pointer -> nextg;
            }
            else    // Filled 6bits and next is 4bits
            {
                OutputByte <<= 2;
                OutputByte += ((pointer->bitsgp & 0x0c) >> 2);
                *(FinalStrPtr++) = OutputByte;

                OutputByte = (pointer->bitsgp & 0x03);
                FilledBNum = 2;

                pointer = pointer -> nextg;
            }
            
        }
    }

    // Realease List
    pointer = BitList;
    for (size_t str_counter = 0; str_counter < b64strnum; str_counter++)
    {
        b64stgp TempPtr = pointer -> nextg;
        free((void*) pointer);
        pointer = TempPtr;
    }
    pointer = NULL;
    FinalStr[TotalNum-1] = '\0';
    return (const char*)FinalStr;
}

