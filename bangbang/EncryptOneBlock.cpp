//
// Created by wanna on 2021/12/26.
//

#include <cstring>
#include "EncryptOneBlock.h"
#include "finalRoundTable.h"
#include "roundTables.h"
#include "xorTables.h"
#include "common.h"


void EncryptOneBlock(unsigned char input[],unsigned char output[]){

    int v11; // r1
    int v13; // r3
    int v14; // r3
    int v15; // r2
    int v16; // r1
    unsigned char *v17; // r0
    int v18; // r2
    unsigned char *v19; // r3
    unsigned char v20; // r5
    unsigned char v21; // r0
    int v22; // r1
    unsigned char v23; // r5
    unsigned char v24; // r7
    int v26; // r6
    int v28; // r7
    int v29; // r5
    unsigned char *v33; // r1
    int v36; // r6
    unsigned char v37; // r7
    unsigned char v41; // [sp+4h] [bp-DCh]
    unsigned char block_matrix[32]; // [sp+48h] [bp-98h] BYREF
    unsigned char tmp_block_matrix[120]; // [sp+68h] [bp-78h] BYREF
    unsigned char v24_1;

    memset(block_matrix, 0, sizeof(block_matrix));
    PrepareAESMatrix(input,  block_matrix);

    for (int round = 0; round < 9; ++round)
    {
        for (int m = 0; m < 4; ++m)
        {
            for (int n = 0; n != 4; ++n )
            {
                v13 = n + byte_3A405[2 * m];
                v14 = v13 & 3;
                v15 = block_matrix[8 * m + v14];
                v16 = (4 * (v14 + 4 * round) + m) << 8;
                v11 = 4 * (v15 + v16);
                v17 = &tmp_block_matrix[16 * m + 32 + 4 * n];
                memcpy(v17, roundTables_auth1_ptr + v11,4u);
            }
        }

        v18 = 96 * round;
        for (int m = 0; m < 4; ++m)
        {
            v19 = &tmp_block_matrix[m + 32];
            for (int n = 0; n < 4; ++n)
            {
                v20 = *v19;
                v41 = v20 & 0xF;
                v21 = 24 * n;
                v22 = 6 * m;
                v23 = (v20 >> 4) << 4;
                for (int k = 1; k < 4; ++k)
                {
                    v24 = v19[k << 4];
                    v24_1 = ( (v24 << 0x1c) >> 0x18);
                    v26 = v41 | v24_1;
                    v28 = v22 + 1;
                    v41 = xorTables_auth1_ptr[256 * (v21 + v18 + v22) + v26] & 0xF;
                    v29 = (v23 >> 4) | ((v24 >> 4) << 4);
                    v22 += 2;
                    v23 = xorTables_auth1_ptr[256 * (v28 + v21 + v18) + v29] << 4;
                }
                v19 += 4;
                block_matrix[8 * m + n] = v23 | v41;
            }
        }
    }

    memcpy(tmp_block_matrix, block_matrix, 0x20u);
    for (int m = 0; m < 4; ++m)
    {
        v33 = block_matrix + m;
        for (int n = 0; n != 4; ++n )
        {
            v36 = (m + byte_3A405[2 * n]) & 3;
            v37 = finalRoundTable_auth1_ptr[256 * (4 * v36 + n) + tmp_block_matrix[8 * n + v36]];
            *v33 = v37;
            v33 += 8;
        }
    }

    for (int m = 0; m != 4; ++m )
    {
        for (int n = 0; n != 4; ++n )
        {
            output[4 * m + n] = block_matrix[8 * n + m];
        }
    }
}
