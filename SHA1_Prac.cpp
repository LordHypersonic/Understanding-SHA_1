#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>

using namespace std;

//function to convert a string to binary digits of 8-bit
string StringtoBinary(string message)
{
    string binary_of_message = "";
    for (int i = 0; i < message.size(); i++)
        binary_of_message += bitset<8>(message[i]).to_string();
    return binary_of_message;
}

//function to convert integer to binary
string IntegertoBinary(int number)
{
    string BinaryDigit = "";
    while(number != 0)
    {
        if (number % 2 == 0)
        {
            number = number / 2;
            BinaryDigit.push_back('0');
        }
        else
        {
            number = number / 2;
            BinaryDigit.push_back('1');
        }
    }
    reverse(BinaryDigit.begin(), BinaryDigit.end());
    return BinaryDigit;
}

//function to set up binary digits upto pad the binary message with zeros until its length is 512 % 448
string paddingBinarywithZero_448Length(string BinaryMessage)
{
    BinaryMessage.push_back('1');
    while (BinaryMessage.size()%512 != 448) //adding zeros until length become 448
    {
        BinaryMessage.push_back('0');
    }
    return BinaryMessage;
}

int main()
{
    string message = "A Test", binary_of_message = "";
    string BinaryOfMessageCharacters[message.size()]; //binary of each character in message
    for (int i = 0; i < message.size(); i++)//splitting characters of message and converting into binary
    {
        string TempMessageCharacter;
        TempMessageCharacter = message[i];
        BinaryOfMessageCharacters[i] = StringtoBinary(TempMessageCharacter);
        cout<<BinaryOfMessageCharacters[i]<<endl;
    }
    binary_of_message = StringtoBinary(message); //finding binary of message
    string binaryAfterAdding448_0 = paddingBinarywithZero_448Length(binary_of_message);
    string BinaryOfBinaryMessageLength = IntegertoBinary(binary_of_message.size()); // finding binary of length of binary of message.
    while (BinaryOfBinaryMessageLength.size() != 64) //adding 0 in front of binary of binary of message until its length become 64
    {
        BinaryOfBinaryMessageLength = "0" + BinaryOfBinaryMessageLength;
    }
    cout<<BinaryOfBinaryMessageLength<<endl<<endl;
    string Adding448StringWith64string = binaryAfterAdding448_0 + BinaryOfBinaryMessageLength;
    string _512MessageChunks[Adding448StringWith64string.size() / 512]; //array of chunk of 512 characters
    int pos = 0;
    for (int i = 0; i < Adding448StringWith64string.size() / 512; i++)//breaking previous result into chunks of 512 bits
    {

        _512MessageChunks[i] = Adding448StringWith64string.substr(pos, 512);
        cout<<_512MessageChunks[i]<<endl;
        pos += 512;
    }
    return 0;
}
