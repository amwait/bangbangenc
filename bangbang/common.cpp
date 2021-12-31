//
// Created by wanna on 2021/12/26.
//

#include "common.h"

unsigned char byte_3A405[] = {0x00,0x00,0x01,0x03,0x02,0x02,0x03,0x01};
void PrepareAESMatrix(unsigned char block[],unsigned char state[]) {
    for (int i = 0; i != 4; ++i) {
        for (int j = 0; j != 4; ++j) {
            *(state + i + 8 * j) = *(block + 4 * i + j);
        }
    }
}