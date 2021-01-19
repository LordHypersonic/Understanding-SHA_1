/*
This is a practice program which is made to understand the working of SHA-1 algorithm
*/
#include <iostream>
#include <string>
#include <sstream>
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

//function to set up binary digits until the binary message with zeros until its length is 4448%512
string paddingBinarywithZero_448Length(string BinaryMessage)
{
    BinaryMessage.push_back('1');
    while (BinaryMessage.size()%512 != 448) //adding zeros until length become 448
    {
        BinaryMessage.push_back('0');
    }
    return BinaryMessage;
}

//left rotate function
unsigned int LeftRotate(unsigned int toRotate,unsigned int times = 1)
{
    return ((toRotate << times) | (toRotate >> (32-times)));
}

//function to convert Hex to binary
string Integer_to_HexString(unsigned int number)
{
    stringstream output;
    output << hex << (number | 0);
    return output.str();
}

int main()
{
    string message = "Hello World!", binary_of_message = "";
    string BinaryOfMessageCharacters[message.size()]; //binary of each character in message
    for (int i = 0; i < message.size(); i++)//splitting characters of message and converting into binary
    {
        string TempMessageCharacter;
        TempMessageCharacter = message[i];
        BinaryOfMessageCharacters[i] = StringtoBinary(TempMessageCharacter);
    }
    binary_of_message = StringtoBinary(message); //finding binary of message
    string binaryAfterAdding448_0 = paddingBinarywithZero_448Length(binary_of_message);
    string BinaryOfBinaryMessageLength = IntegertoBinary(binary_of_message.size()); // finding binary of length of binary of message.
    while (BinaryOfBinaryMessageLength.size() != 64) //adding 0 in front of binary of binary of message until its length become 64
    {
        BinaryOfBinaryMessageLength = "0" + BinaryOfBinaryMessageLength;
    }
    string Adding448StringWith64string = binaryAfterAdding448_0 + BinaryOfBinaryMessageLength;
    string _512MessageChunks[Adding448StringWith64string.size() / 512]; //array of chunk of 512 characters
    int pos = 0;
    int numberOf512Chunks = Adding448StringWith64string.size() / 512;
    for (int i = 0; i < numberOf512Chunks; i++)//breaking previous result into chunks of 512 bits
    {

        _512MessageChunks[i] = Adding448StringWith64string.substr(pos, 512);
        pos += 512;
    }
    unsigned int _32BitChunks[numberOf512Chunks][80]; //2D array to store 32 bit chunk from 512 bit chunk, rows store which 512 chunk to use and columns stores 32 bit words generated from that chunk
    //storing first 16 words of 32 bit in array.
    for (int row = 0; row < numberOf512Chunks; row++)
    {
        pos = 0;
        for(int column = 0; column < 16; column++)
        {
            for (int i = 0; i < numberOf512Chunks; i++) //splitting 512 bit chunk into 32 bit chunks
            {
                _32BitChunks[row][column] = stoull(_512MessageChunks[i].substr(pos, 32), 0, 2);
                pos += 32;
            }
        }
    }
    //storing rest of the words of 32 bits in array
    for (int row = 0; row < numberOf512Chunks; row++)
    {
        for(int column = 16; column < 80; column++)
        {
            //Current Word = Left Rotate( XOR( XOR( XOR(Word (current index - 3), Word (current index - 8)), Word (current index - 14)), Word (Current index - 16)), 1)
            unsigned int XOR1 = _32BitChunks[row][column-3] ^ _32BitChunks[row][column-8];
            unsigned int XOR2 = XOR1 ^ _32BitChunks[row][column-14];
            unsigned int XOR3 = XOR2 ^ _32BitChunks[row][column-16];
            _32BitChunks[row][column] = LeftRotate(XOR3,1);
        }
    }
    unsigned int h0 = 0x67452301,
                 h1 = 0xEFCDAB89,
                 h2 = 0x98BADCFE,
                 h3 = 0x10325476,
                 h4 = 0xC3D2E1F0;
    unsigned int a = h0, b = h1, c = h2, d = h3, e = h4;
    //for calculating final hash by manipulating the h0, h1, h2, h3 and h4 using 32 bit words calculated previously
    for (int row = 0; row < numberOf512Chunks; row++)
    {
        for(int column = 0; column < 80; column++)
        {
            unsigned int f = 0, k = 0;
            if (column < 20)
            {
                unsigned int BandC =  b & c;
                unsigned int NOTBandD = (~b) & d;
                f = BandC | NOTBandD;
                k = 0x5A827999;
            }
            else if(column < 40)
            {
                unsigned int BxorC = b ^ c;
                f = BxorC ^ d;
                k = 0x6ED9EBA1;
            }
            else if (column < 60)
            {
                unsigned int BandC = b & c;
                unsigned int BandD = b & d;
                unsigned int CandD = c & d;
                unsigned int OR1 = BandC | BandD;
                f = OR1 | CandD;
                k = 0x8F1BBCDC;
            }
            else
            {
                unsigned int BxorC = b ^ c;
                f = BxorC ^ d;
                k = 0xCA62C1D6;
            }
            unsigned int word = _32BitChunks[row][column];
            unsigned int Addition1 = LeftRotate(a,5) + f;
            unsigned int Addition2 = Addition1 + e;
            unsigned int Addition3 = Addition2 + k;
            unsigned int temp = Addition3 + word;
            e = d;
            d = c;
            c = LeftRotate(b,30);
            b = a;
            a = temp;
        }
        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
    }
    string FinalHash = Integer_to_HexString(h0) + Integer_to_HexString(h1) + Integer_to_HexString(h2) + Integer_to_HexString(h3) + Integer_to_HexString(h4);
    cout<<FinalHash<<endl;
    return 0;
}
