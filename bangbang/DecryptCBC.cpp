//
// Created by wanna on 2021/12/26.
//

#include <cstring>
#include "DecryptCBC.h"
#include "DecryptOneBlock.h"

void RemoveCBCPadding(unsigned char* input, int *len)
{
    int tmplen = *len;
    unsigned char* end_pointer = input + tmplen - 1;
    while ( (*end_pointer) <= 0x10 )
    {
        tmplen--;
        end_pointer = input + tmplen;
    }
    *len = tmplen + 1;
}

//示例数据   unsigned char decode_data2[] = {0xde,0x1a,0x06,0x7a,0xd2,0x17,0x1c,0x7c,0x0c,0x34,0xb0,0x9a,0x95,0x13,0xe6,0xf3,0xbc,0x2d,0x23,0xd0,0xbc,0xf2,0xfd,0x9a,0xac,0x31,0x42,0xb5,0xcd,0x03,0x5f,0xb9,0xd4,0x2e,0xfe,0xa7,0x66,0x9a,0xdb,0x7e,0x31,0xba,0x82,0x4c,0x3c,0x03,0xd5,0x72,0x1e,0x2d,0x24,0xa4,0x2e,0xad,0x07,0x2d,0xaf,0xfd,0x19,0x69,0xa2,0xe2,0xd1,0xd8};
void DecryptCBC(unsigned char input[],int *len)
{
    int input_hex_len; // r5
    int index; // r0
    unsigned char *tmp_block_pointer;
    unsigned int v9; // r6
    unsigned char *block_pointer; // r5
    int v11; // r3
    unsigned char output[16];
    input_hex_len = *len;
    index = 11;

    if ( !(input_hex_len << 28) )
    {

        v9 = input_hex_len >> 4;
        block_pointer = input + input_hex_len - 32;
        while ( v9 )
        {
            DecryptOneBlock(block_pointer + 16, output);// 逆序解密，每次解密16个字节
            memcpy(block_pointer + 16, output, 0x10u);
            tmp_block_pointer = block_pointer;
            v11 = 16;
            if ( v9 == 1 )
            {
                do
                {
                    *(input + index++) ^= 0;
                }
                while (index != 16 );
            }
            else
            {
                do
                {
                    tmp_block_pointer[16] ^= *tmp_block_pointer;
                    ++tmp_block_pointer;
                    v11 --;
                }
                while ( v11 );
            }
            --v9;
            block_pointer -= 16;
        }
    }
    RemoveCBCPadding(input,len);
    input[*len] = '\0';
}

