#include <iostream>
#include <string>
#include <bitset>

using namespace std;

//function to convert a string to binary digits of 8-bit
string ToBinary(string message)
{
    string binary_of_message = "";
    for (int i = 0; i < message.size(); i++)
        binary_of_message += bitset<8>(message[i]).to_string();
    return binary_of_message;
}

//function to set up binary digits upto pad the binary message with zeros until its length is 512 % 448
string paddingBinarywithZero_448Length(string BinaryMessage)
{
    BinaryMessage.push_back('1');
    while (BinaryMessage.size()%512 != 448)
    {
        BinaryMessage.push_back('0');
    }
    return BinaryMessage;
}

int main()
{
    string message = "A Test", binary_of_message = "";
    binary_of_message = ToBinary(message);
    binary_of_message = paddingBinarywithZero_448Length(binary_of_message);
    cout<<binary_of_message<<endl<<binary_of_message.size()<<endl;
    return 0;
}
