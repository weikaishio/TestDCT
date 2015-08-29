//
//  rc4.c
//  testgame
//
//  Created by Tim on 14-11-4.
//
//

#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef struct rc4_key_str
{
    unsigned char state[256];
    unsigned char x;
    unsigned char y;
} rc4_key;

static void swap_byte(unsigned char *a, unsigned char *b);

void prepare_key(unsigned char *key_data_ptr,
                 int key_data_len,
                 rc4_key *key)
{
    unsigned char index1;
    unsigned char index2;
    unsigned char* state;
    short counter;
    
    state = &key->state[0];
    for(counter = 0; counter < 256; counter++)
        state[counter] = counter;
    key->x = 0;
    key->y = 0;
    index1 = 0;
    index2 = 0;
    for(counter = 0; counter < 256; counter++)
    {
        index2 = (key_data_ptr[index1] + state[counter] +
                  index2) % 256;
        swap_byte(&state[counter], &state[index2]);
        
        index1 = (index1 + 1) % key_data_len;
    }
}

void rc4(unsigned char *buffer_ptr, int buffer_len,  rc4_key *key)
{
    unsigned char x;
    unsigned char y;
    unsigned char* state;
    unsigned char xorIndex;
    int counter;
    
    x = key->x;
    y = key->y;
    
    state = &key->state[0];
    for(counter = 0; counter < buffer_len; counter ++)
    {
        x = (x + 1) % 256;
        y = (state[x] + y) % 256;
        swap_byte(&state[x], &state[y]);
        
        xorIndex = (state[x] + state[y]) % 256;
        
        buffer_ptr[counter] ^= state[xorIndex];
    }
    key->x = x;
    key->y = y;
}

static void swap_byte(unsigned char *a, unsigned char *b)
{
    unsigned char swapByte;
    
    swapByte = *a;
    *a = *b;
    *b = swapByte;
}
void rc4out(const char* buffer,int size,const char* key)
{
//    char *Key = "ZmRkZDVjZjEwNTI5MTY0ZWFl";
    rc4_key rc4key;
    
    prepare_key((unsigned char*)key,	(int)strlen(key),	&rc4key);
    rc4((unsigned char *)buffer, size, &rc4key);
}
/*
 char *Key = "ZmRkZDVjZjEwNTI5MTY0ZWFl";
 return [self base64RC4WithKey:prestr key:Key];
 }
 +(NSString*)base64RC4WithKey:(NSString*)prestr key:(char*)Key
 
 rc4_key rc4key;
 
 prepare_key((unsigned char*)Key,	strlen(Key),	&rc4key);
 
 char* buffer=(char*)malloc([prestr length]);
 //    char buffer[256];
 memcpy(buffer, (char*)[prestr UTF8String], [prestr length]);
 rc4((unsigned char *)buffer, [prestr length], &rc4key);
*/