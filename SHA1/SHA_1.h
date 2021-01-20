#include <iostream>
#include <string>
#include <bitset>
#include <map>

using namespace std;

class SHA_1 {
private:
    unsigned int h0,h1,h2,h3,h4,a,b,c,d,e;
    int numberof512chunks, MessageLength;
    string Message, finalHash;

public:
    SHA_1(string M)
    {
        h0 = 0x67452301;
        h1 = 0xEFCDAB89;
        h2 = 0x98BADCFE;
        h3 = 0x10325476;
        h4 = 0xC3D2E1F0;
        a = h0; b = h1; c = h2; d = h3; e = h4;
        numberof512chunks = 0;
        Message = M;
        finalHash = "";
        MessageLength = 0;
    }

    //Starting the process of finding hash
    void Start()
    {
        string Binary_of_Message = "";
        //finding binary string of message
        for (int i = 0; i < Message.size(); i++)
            Binary_of_Message += bitset<8>(Message[i]).to_string();

        //finding binary string of length of message
        MessageLength = Binary_of_Message.size();
        string Binary_of_MessageLength = bitset<64>(MessageLength).to_string();

        string Binary_after448_0 = Binary_of_Message + "1"; //appending 1 at the end of binary of message
        while(Binary_after448_0.size() % 512 != 448)//appending 448 % 512 0 at binary message
        {
            Binary_after448_0 += "0";
        }
        string FullBinaryMessage = Binary_after448_0 + Binary_of_MessageLength; //adding message length binary to message binary
        numberof512chunks = FullBinaryMessage.size() / 512;
        string Chunksof_512bits[numberof512chunks];
        int pos = 0;
        //Breaking message into chunks of 512
        for (int i = 0; i < numberof512chunks; i++)
        {
            Chunksof_512bits[i] = FullBinaryMessage.substr(pos, 512);
            pos += 512;
        }
        unsigned int _80Words [numberof512chunks][80];//2D array to store 32bit words from each chunk.
        //finding first 16 32-bit words for each chunk
        for (int row = 0; row < numberof512chunks; row++)
        {
            pos = 0;
            for(int column = 0; column < 16; column++)
            {
                for(int i = 0; i < numberof512chunks; i++)
                {
                    _80Words[row][column] = bitset<32>(Chunksof_512bits[i].substr(pos, 32)).to_ullong();
                    pos += 32;
                }
            }
        }
        //finding rest of 32-bit words for each chunk
        for (int row = 0; row < numberof512chunks; row++)
        {
            for(int column = 16; column < 80; column++)
            {
                // Words[i] = Word[i-3] XOR Word[i-8] XOR Word[i-14] XOR Word[i-16] -> Left rotate by 1
                _80Words[row][column] = WordsAfter16(_80Words,row,column);
            }
        }
        Update(_80Words);
    }

    //left rotate function
    unsigned int LeftRotate(unsigned int toRotate, unsigned int times = 1)
    {
        return ((toRotate << times) | (toRotate >> (32-times)));
    }

    //function to calculate 16-80 32-bit words
    unsigned int WordsAfter16(unsigned int Words[][80], int currentR, int currentC)
    {
        return LeftRotate(Words[currentR][currentC-3] ^ Words[currentR][currentC-8] ^ Words[currentR][currentC-14] ^ Words[currentR][currentC-16], 1);
    }

    //function updating initial hash to find the hash of given text
    void Update(unsigned int Word80[][80])
    {
        for (int row = 0; row < numberof512chunks; row++)
        {
            for (int column = 0; column < 80; column++)
            {
                unsigned int temp = LeftRotate(a,5) + Fat(column) + e + Kat(column) + Word80[row][column];
                e = d;
                d = c;
                c = LeftRotate(b, 30);
                b = a;
                a = temp;
            }
            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
        }
        Final();
    }

    //function to calculate f in Update
    unsigned int  Fat(int currentC)
    {
        if (currentC < 20)
            return (b & c) | ((~b) & d);
        else if (currentC < 40)
            return b ^ c ^ d;
        else if (currentC < 60)
            return (b & c) | (b & d) | (c & d);
        else
            return b ^ c ^ d;
    }

    //function to calculate k in Update
    unsigned int Kat (int currentC)
    {
        if (currentC < 20)
            return 0x5A827999;
        else if (currentC < 40)
            return 0x6ED9EBA1;
        else if (currentC < 60)
            return 0x8F1BBCDC;
        else
            return 0xCA62C1D6;
    }

    //function for finishing the hash calculation
    void Final ()
    {
        //cout<<h0<<" "<<Integer_to_HexString(h0)<<endl<<h1<<" "<<Integer_to_HexString(h1)<<endl<<h2<<" "<<Integer_to_HexString(h2)<<endl<<h3<<" "<<Integer_to_HexString(h3)<<endl<<h4<<" "<<Integer_to_HexString(h4)<<endl;
        finalHash = Integer_to_HexString(h0) +  Integer_to_HexString(h1) + Integer_to_HexString(h2) + Integer_to_HexString(h3) + Integer_to_HexString(h4);
    }

    //function for converting integer to hex value
    string Integer_to_HexString(unsigned int number)
    {
        map <string,string> hexValeus;
        hexValeus.insert(pair<string,string>("0000","0"));
        hexValeus.insert(pair<string,string>("0001","1"));
        hexValeus.insert(pair<string,string>("0010","2"));
        hexValeus.insert(pair<string,string>("0011","3"));
        hexValeus.insert(pair<string,string>("0100","4"));
        hexValeus.insert(pair<string,string>("0101","5"));
        hexValeus.insert(pair<string,string>("0110","6"));
        hexValeus.insert(pair<string,string>("0111","7"));
        hexValeus.insert(pair<string,string>("1000","8"));
        hexValeus.insert(pair<string,string>("1001","9"));
        hexValeus.insert(pair<string,string>("1010","a"));
        hexValeus.insert(pair<string,string>("1011","b"));
        hexValeus.insert(pair<string,string>("1100","c"));
        hexValeus.insert(pair<string,string>("1101","d"));
        hexValeus.insert(pair<string,string>("1110","e"));
        hexValeus.insert(pair<string,string>("1111","f"));
        string Binary_of_number = Interger_to_BinaryString(number);
        string output = "";
        for (int i = 0; i < Binary_of_number.size(); i += 4)
        {
            output += hexValeus[Binary_of_number.substr(i,4)];
        }
        return output;
    }

    //function to convert integer to binary string
    string Interger_to_BinaryString(unsigned int DecNum)
    {
        string output = bitset<32>(DecNum).to_string();
        return output;
    }

    //function to call the start function and initialize the calculation and return the final hash
    string show()
    {
        Start();
        string output = finalHash;
        return output;
    }
};

//function to calculate SHA-1 hash using class SHA_1
string SHA1(string message)
{
    SHA_1 sha1(message);
    return sha1.show();
}
