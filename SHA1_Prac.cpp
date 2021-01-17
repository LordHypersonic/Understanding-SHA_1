#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main()
{
    string message = "A Test", binary_of_message = "";
    for (int i = 0; i < message.size(); i++)
        binary_of_message += bitset<8>(message[i]).to_string();
    binary_of_message.push_back('1');
    while (binary_of_message.size()%512 != 448)
    {
        binary_of_message.push_back('0');
    }
    cout<<binary_of_message<<endl;
    return 0;
}
