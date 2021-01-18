#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <map>

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

//left rotate function
string LeftRotate(string toRotate, int times = 1)
{
    while (times != 0)
    {
        char temp = toRotate[0];
        for (int i = 0; i < toRotate.size(); i++)
            toRotate[i] = toRotate[i+1];
        toRotate.resize(toRotate.size()-1);
        toRotate.push_back(temp);
        times--;
    }
    return toRotate;
}

//finding XOR of Binary string
string XOR(string binary1, string binary2)
{
    string output="";
    for (int i = 0; i < binary1.size(); i++)
    {
        if(binary1[i] == binary2[i])
            output.push_back('0');
        else output.push_back('1');
    }
    return output;
}

//function for AND operation
string AND (string binary1,string binary2)
{
    string output = "";
    for (int i = 0; i < binary1.size(); i++)
    {
        if (binary1[i] == '1' && binary2[i] == '1')
            output.push_back('1');
        else output.push_back('0');
    }
    return output;
}

//function for OR operation
string OR (string binary1,string binary2)
{
    string output = "";
    for (int i = 0; i < binary1.size(); i++)
    {
        if (binary1[i] == '1' || binary2[i] == '1')
            output.push_back('1');
        else output.push_back('0');
    }
    return output;
}

//function for not operation
string NOT(string binaryString)
{
    string output = "";
    for (int i = 0; i < binaryString.size(); i++)
        if (binaryString[i] == '0') output.push_back('1');
        else output.push_back('0');
    return output;
}

// This function adds two binary strings and return
// result as a third string
string BinaryAddition(string a, string b)
{
    string result = ""; // Initialize result
    /*string Carry =  "0";
    for (int i = 0; i < a.size(); i++)
    {
        string TempA, TempB, TempResult;
        TempA = a[i]; TempB = b[i];
        TempResult = XOR ( XOR(TempA,TempB), Carry);
        Carry = OR( AND(XOR(TempA,TempB),Carry),AND(TempA,TempB));
        //cout<<Carry<<endl;
        result += TempResult;
    }*/
    int s = 0;          // Initialize digit sum

    // Traverse both strings starting from last
    // characters
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1)
    {
        // Compute sum of last digits and carry
        s += ((i >= 0)? a[i] - '0': 0);
        s += ((j >= 0)? b[j] - '0': 0);

        // If current digit sum is 1 or 3, add 1 to result
        result = char(s % 2 + '0') + result;

        // Compute carry
        s /= 2;

        // Move to next digits
        i--; j--;
    }
    return result;
}

//function to convert binary string to hex string
string Binary_to_Hex(string BinaryString)
{
    string output;
    map <string, string> hexValues;
    hexValues.insert(pair<string,string>("0000","0"));
    hexValues.insert(pair<string,string>("0001","1"));
    hexValues.insert(pair<string,string>("0010","2"));
    hexValues.insert(pair<string,string>("0011","3"));
    hexValues.insert(pair<string,string>("0100","4"));
    hexValues.insert(pair<string,string>("0101","5"));
    hexValues.insert(pair<string,string>("0110","6"));
    hexValues.insert(pair<string,string>("0111","7"));
    hexValues.insert(pair<string,string>("1000","8"));
    hexValues.insert(pair<string,string>("1001","9"));
    hexValues.insert(pair<string,string>("1010","a"));
    hexValues.insert(pair<string,string>("1011","b"));
    hexValues.insert(pair<string,string>("1100","c"));
    hexValues.insert(pair<string,string>("1101","d"));
    hexValues.insert(pair<string,string>("1110","e"));
    hexValues.insert(pair<string,string>("1111","f"));
    for(int i = 0; i < BinaryString.size(); i += 4)
    {
        string temp = BinaryString.substr(i, 4);
        output = output + hexValues[temp];
    }
    return output;
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
    for (int i = 0; i < Adding448StringWith64string.size() / 512; i++)//breaking previous result into chunks of 512 bits
    {

        _512MessageChunks[i] = Adding448StringWith64string.substr(pos, 512);
        pos += 512;
    }
    string _32BitChunks[Adding448StringWith64string.size() / 512][80]; //2D array to store 32 bit chunk from 512 bit chunk, rows store which 512 chunk to use and columns stores 32 bit words generated from that chunk
    //storing first 16 words of 32 bit in array.
    for (int row = 0; row < Adding448StringWith64string.size() / 512; row++)
    {
        pos = 0;
        for(int column = 0; column < 16; column++)
        {
            for (int i = 0; i < Adding448StringWith64string.size() / 512; i++) //splitting 512 bit chunk into 32 bit chunks
            {
                _32BitChunks[row][column] = _512MessageChunks[i].substr(pos, 32);
                pos += 32;
            }
        }
    }
    //storing rest of the words of 32 bits in array
    for (int row = 0; row < Adding448StringWith64string.size() / 512; row++)
    {
        for(int column = 16; column < 80; column++)
        {
            //Current Word = Left Rotate( XOR( XOR( XOR(Word (current index - 3), Word (current index - 8)), Word (current index - 14)), Word (Current index - 16)), 1)
            _32BitChunks[row][column] = LeftRotate(XOR(XOR(XOR(_32BitChunks[row][column-3], _32BitChunks[row][column-8]), _32BitChunks[row][column-14]), _32BitChunks[row][column-16]));
        }
    }
    string h0 = "01100111010001010010001100000001",
           h1 = "11101111110011011010101110001001",
           h2 = "10011000101110101101110011111110",
           h3 = "00010000001100100101010001110110",
           h4 = "11000011110100101110000111110000";
    string a = h0, b = h1, c = h2, d = h3, e = h4;
    //for calculating final hash by manipulating the h0, h1, h2, h3 and h4 using 32 bit words calculated previously
    for (int row = 0; row < Adding448StringWith64string.size() / 512; row++)
    {
        for(int column = 0; column < 80; column++)
        {
            string f = "", k = "";
            if (column < 20)
            {
                f = OR( AND(b,c), AND(NOT(b),d));
                k = "01011010100000100111100110011001";
            }
            else if(column < 40)
            {
                f = XOR( XOR(b,c), d);
                k = "01101110110110011110101110100001";
            }
            else if (column < 60)
            {
                f = OR ( OR ( AND(b,c), AND(b,d)), AND(c,d));
                k = "10001111000110111011110011011100";
            }
            else
            {
                f = XOR( XOR(b,c),d);
                k = "11001010011000101100000111010110";
            }
            string temp = BinaryAddition( BinaryAddition( BinaryAddition( BinaryAddition( LeftRotate(a,5),f),e),k),_32BitChunks[row][column]);
            temp.resize(32);
            e = d;
            d = c;
            c = LeftRotate(b, 30);
            b = a;
            a = temp;
            //cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
        }
        h0 = BinaryAddition(h0,a); h0.resize(32);
        h1 = BinaryAddition(h1,b); h1.resize(32);
        h2 = BinaryAddition(h2,c); h2.resize(32);
        h3 = BinaryAddition(h3,d); h3.resize(32);
        h4 = BinaryAddition(h4,e); h4.resize(32);
    }
    cout<<h0<<endl<<h1<<endl<<h2<<endl<<h3<<endl<<h4<<endl;
    string FinalHash = Binary_to_Hex(h0+h1+h2+h3+h4);
    cout<<FinalHash<<endl;
    return 0;
}
