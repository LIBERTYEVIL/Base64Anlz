/*
    ==============================================================
                   COPYRIGHT (C) 2025, LIBERTYEVIL
    ==============================================================
     * Licensed under GNU GPL v3
     * Original repository: https://github.com/LIBERTYEVIL/Base64Anlz/
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base64.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {   
        printf("Base64 Analyzer Usage:\n");
        printf("1.No Argument - Display this help\n");
        printf("2.Input a string:\n");
        printf(" - If it's a base64 string, decode and analyze other info\n");
        printf(" - If it's a file within base64 strings, try find hiden info\n");
        printf(" - Encode other string to base64 string\n");
        printf("COPYRIGHT (C) LIBERTYEVIL 2025\n");
    }
    else if (argc > 2)
    {
        printf("Too many arguments inputted.\n");
    }
    else if (argc == 2)
    {
        b64stgp bitlist = NULL;
        FILE* fp = NULL;
        if ((fp = fopen(argv[1], "r")) != NULL)
        {
            printf("File opened successfully, reading...\n");

            int i = 0, j = 0, ch = 0, ch_pre = 0, lnum = 0;
            while ((ch = fgetc(fp)) != EOF)
            {
                ch_pre = ch;
                if (ch == '\n') i++;
            }
            if(ch_pre != '\n' && ch_pre != '\r') i++;
            fseek(fp, 0, SEEK_SET);
            char* lines[i];
            int chnums[i];
            lnum = i;
            ch_pre = ch = i = 0;

            while ((ch = fgetc(fp)) != EOF) 
            {
                if (ch == '\n') 
                {
                    lines[i] = calloc(j+1, sizeof(char));
                    chnums[i] = j;
                    i++;
                    j = 0;
                }
                if (ch != '\n' && ch != '\r') j++;
                ch_pre = ch;
            }
            ch_pre = ch = i = 0;
            fseek(fp, 0, SEEK_SET);

            while ((ch = fgetc(fp)) != EOF)
            {
                if (ch != '\n' && ch != '\r') 
                {
                    lines[i][j] = ch;
                    j++;
                }
                else if (ch == '\n')
                {
                    if (ch_pre == '\r')
                    {
                        lines[i][j-1] = '\0';
                    }
                    lines[i][j] = '\0';
                    i++;
                    j = 0;
                }
                ch_pre = ch;
            }
            fclose(fp);

            bitlist = GetBitListFromBase64Para(lines, lnum);
            const char* hiddenstr = GetStrFromB64stgBits(bitlist, lnum);
            printf("Result: %s\n", hiddenstr);
            char* filename0 = calloc(strlen(argv[1])+15, sizeof(char));
            strcpy(filename0, argv[1]);
            strcpy(strrchr(filename0, '.'), "_stegres.txt");
            FILE* wrtf = fopen(filename0, "w");
            fprintf(wrtf, "%s", hiddenstr);
            fclose(wrtf);
            printf("It has been output to %s\n", filename0);
            free(filename0);
            for (size_t k = 0; k < lnum; k++)
            {
                free((void*) lines[k]);
            }
            free((void*) hiddenstr);
        }
        else 
        {
            const char* decoded = (is_not_base64_str(argv[1]) == 0) ? base64_decode(argv[1]) : NULL;
            const char* encoded = base64_encode(argv[1]);
            size_t orglen = strlen(argv[1]);
            size_t declen = (decoded!=NULL) ? strlen(decoded) : 0;
            size_t enclen = (decoded!=NULL) ? strlen(encoded) : 0;

            printf("Analysis Result:\n");
            printf(" - Original String: %s\n", argv[1]);
            printf(" - Original Length: %d\n", strlen(argv[1]));
            printf(" - Base64 Encoding Result: %s\n", encoded);
            printf(" - Base64 Encoded  Length: %d\n", strlen(encoded));
            printf(" - Base64 Decoding Result: %s\n", ((decoded==NULL) ? "Cannot decode as a Base64 str." : decoded));
            if (decoded != NULL) printf(" - Base64 Decoded  Length: %d\n", strlen(decoded));
            if(decoded != NULL) free((void*) decoded);
            if(encoded != NULL) free((void*) encoded);
            if(decoded==NULL);
            else if (if_steg_base64(argv[1]))
            {
                b64stg hinfo = GetBitGroupFromBase64Str(argv[1]);
                printf(" - This base64 string has steganography:\n");
                printf("   Size:  %d Bits\n", hinfo.bitnum);
                printf("   Value: 0x%x\n", hinfo.bitsgp);
            }
            else
            {
                printf("There's no steganography in the string.\n");
            }
        }
    }
    return 0;
}
