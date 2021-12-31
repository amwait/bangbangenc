#include <iostream>
#include <string>
#include <cstring>
#include "EncrypyCBC.h"
#include "DecryptCBC.h"

#include "bangbang.h"
#include "base64new.h"

using namespace std;

char *randstr(char *str, const int len)
{
    srand(time(NULL));
    int i;
    for (i = 0; i < len; ++i)
    {
        switch ((rand() % 3))
        {
            case 1:
                str[i] = 'A' + rand() % 26;
                break;
            case 2:
                str[i] = 'a' + rand() % 26;
                break;
            default:
                str[i] = '0' + rand() % 10;
                break;
        }
    }
    str[++i] = '\0';
    return str;
}

int main()
{

    char source_check_data[500] ;
    cout <<"random str:"<< randstr(source_check_data, 50);
    cout<<" len:"<<strlen(source_check_data)<<endl;

    char check_data[2000];
    check_code(source_check_data,check_data);
    cout<<check_data<<endl;

    char decheck_data[2000];
    dechck_code(check_data, decheck_data);
    cout<<decheck_data<<endl;
    return 0;

}
