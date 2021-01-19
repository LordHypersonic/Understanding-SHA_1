#include "SHA_1.h"

int main()
{
    string message = "";
    cout<<"Enter Message to encrypt: "; getline(cin,message);
    cout<<"SHA-1("<<message<<") : "<<SHA1(message)<<endl;
    return 0;
}
