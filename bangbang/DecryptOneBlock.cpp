
#include <cstring>
#include "DecryptOneBlock.h"
#include "invFirstRoundTable.h"
#include "invRoundTables.h"
#include "invXorTables.h"
#include "common.h"


void DecryptOneBlock(unsigned char input[], unsigned char output[])
{
    int j; // r6
    int v8; // r7
    int k; // r5
    int v11; // r2
    int v12; // r1
    int v14; // r3
    int v15; // r0
    int v16; // r1
    unsigned char *v17; // r0
    int v18; // r2
    unsigned char *v19; // r3
    unsigned char v20; // r5
    int v21; // r0
    int v22; // r1
    unsigned char v23; // r5
    unsigned char  v24; // r12
    int v26; // r7
    unsigned char v27; // r5

    unsigned char *v31; // r0
    unsigned char *v32; // r1
    int i; // r3
    int v35; // r6
    int v36; // r12
    int v38; // r7
    int l; // r3
    int m; // r2
    unsigned char v42; // [sp+4h] [bp-DCh]

    unsigned char block_state[32]; // [sp+48h] [bp-98h] BYREF
    unsigned char temp_state_block[120]; // [sp+68h] [bp-78h] BYREF
    memset(block_state, 0, sizeof(block_state));

    PrepareAESMatrix(input, block_state);// 转换为状态矩阵

    for (int round = 9; round > 0; --round)
    {
        for (j = 1; j != 5; ++j)
        {
            v8 = j - 1;
            for (k = 0; k != 4; ++k)
            {
                v11 = byte_3A405[2 * j - 1];
                v14 = (k + v11) & 3;
                v15 = block_state[8 * v8 + v14];
                v16 = (4 * (v14 + 4 * round) + v8) << 8;
                v12 = 4 * (v15 + v16);
                v17 = &temp_state_block[16 * j + 16 + 4 * k];
                memcpy(v17, invRoundTables_auth1_ptr + v12, 4u);
            }
        }

        v18 = 96 * round;
        for (int n = 0; n < 4; ++n)
        {
            v19 = &temp_state_block[n + 32];
            for (int v50 = 0;v50 < 4;v50++)
            {
                v20 = *v19;
                v42 = v20 & 0xF;
                v21 = 24 * v50;
                v22 = 6 * n;
                v23 = 16 * (v20 >> 4);
                for (int k = 1; k < 4; ++k)
                {
                    v24 = v19[k * 16];
                    v26 = v22 + 1;
                    unsigned char v24_1 = ((v24 << 28) >> 0x18);
                    v42 = invXorTables_auth1_ptr[256 * (v21 + v18 + v22) + (v42 |v24_1)] ;
                    v27 = (v23 >> 4) | (16 * (v24 >> 4));
                    v22 += 2;
                    v23 = 16 * invXorTables_auth1_ptr[256 * (v26 + v21 + v18) + v27];
                }
                v19 += 4;
                block_state[8 * n + v50] = v23 | v42;
            }
        }
    }
    memcpy(temp_state_block, block_state, 32u);
    for (int n = 0; n < 4; ++n)
    {
        v31 = byte_3A405 + 1;
        v32 = block_state + n;
        for ( i = 0; i != 4; ++i )
        {
            v35 = (n + *v31) & 3;
            v31 += 2;
            v36 = temp_state_block[8 * i + v35];
            v38 = ((4 * v35 + i) << 8) + v36;
            *v32 = invFirstRoundTable_auth1_ptr[v38];
            v32 += 8;
        }
    }
    for (l = 0; l != 4; ++l)
    {
        for (m = 0; m != 4; ++m)
        {
            output[4 * l + m] = block_state[8 * m + l];
        }
    }
}

