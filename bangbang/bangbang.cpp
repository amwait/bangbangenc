//
// Created by wanna on 2021/12/27.
//

#include <cstring>
#include <malloc.h>
#include <cstdio>
#include <iostream>
#include "bangbang.h"
#include "EncrypyCBC.h"

#include "DecryptCBC.h"
#include "base64new.h"
using namespace std;
void check_code(char *data, char * encrypt_data)
{
    /*
     * 加密流程是：对于给定的一个人字符串，取byte数据。然后进行加密，对与加密的结果(input)进行base64 编码后 ，再在首字符前拼接上 F 即可得到最终的加密字符串，可以发送到服务器了
     * */
    int input_len = strlen(data);

    unsigned char tmp[2000];
    memcpy(tmp, data, input_len);
    EncryptCBC(tmp, &input_len);
    string encode = base64_encode(tmp, input_len);
    const char * encode_str = encode.c_str();
    int encode_len = encode.length();
    memcpy(encrypt_data, encode_str,encode_len);
    encrypt_data[encode_len] = '\0';
}

void dechck_code(char *data, char *out)
{
    /*
     * 解密流程是：对于从服务器返回给定一个字符串，去掉首字符F后进行base64 解码，即可得到 decode_data
     * 对于解密则inputData 已足够存放解密后的值 因此不需要重要赋值给新的字符串指针
    */

    std::string decoded  = base64_decode(data);
    unsigned char *decodes = (unsigned char *) decoded.data();
    int input_len = decoded.length();
    DecryptCBC(decodes, &input_len);
    memcpy(out,decodes,input_len);
    out[input_len] = '\0';
}