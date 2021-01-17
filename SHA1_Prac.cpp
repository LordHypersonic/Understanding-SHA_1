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
    string BinaryOfMessageCharacters[message.size()]; //binary of each character in message
    for (int i = 0; i < message.size(); i++)//splitting characters of message and converting into binary
    {
        string TempMessageCharacter;
        TempMessageCharacter = message[i];
        BinaryOfMessageCharacters[i] = ToBinary(TempMessageCharacter);
        cout<<BinaryOfMessageCharacters[i]<<endl;
    }
    binary_of_message = ToBinary(message); //finding binary of message
    binary_of_message = paddingBinarywithZero_448Length(binary_of_message);
    string _512MessageChunks[message.size()]; //array of chunk of 512 characters
    for (int i = 0; i < message.size(); i++) //calculating chunk for each character in message
    {
        string TempMessageCharacterBinary = BinaryOfMessageCharacters[i];
        while (TempMessageCharacterBinary.size() != 64) //making binary of each character to 64-bit by adding 0 in front of previous binary
            TempMessageCharacterBinary = "0" + TempMessageCharacterBinary;
        _512MessageChunks[i] = binary_of_message + TempMessageCharacterBinary;
    }
    return 0;
}
