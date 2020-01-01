#include <iostream>
#include "algorithms.h"

char* GetString(char*);

using namespace std;
using namespace Algorithms;
int main()
{
    char* str;
    cout << Cryptography::Encrypt(str = GetString("Enter the string: "));
    cout << "\n Decrypted: "<< Cryptography::Decrypt(str);
    return 0;
}

char* GetString(char* message)
{
    char* str = (char*) malloc(sizeof(char) * 10000);

    cout << message << " \n";
    cin >> str;

    return str;
}