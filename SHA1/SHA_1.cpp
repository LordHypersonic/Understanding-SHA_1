/*
Program: SHA-1 calculator
Description: This part contain main function and use of SHA1() function.
Author: Lord Hypersonic
Email: lordhypersonic.522@gmail.com
Website: www.lordhypersonic.blogspot.com
Github: https://github.com/LordHypersonic
*/
#include "SHA_1.h"

int main()
{
    string message = "";
    cout<<"Enter Message to encrypt: "; getline(cin,message);
    cout<<"SHA-1("<<message<<") : "<<SHA1(message)<<endl;
    return 0;
}
