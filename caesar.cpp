#include <iostream>
#include <string>

using namespace std;

int main() {
    string encrypt = "";
    string decrypt = "";
    string temp = "Hello world";
    int key = 5;

    for (int i = 0; i < temp.length(); i++) {
        if (isalpha(temp[i])) {  
            char base = isupper(temp[i]) ? 'A' : 'a';
            int index = temp[i] - base;
            int sol = (key + index) % 26;
            encrypt += char(sol + base);
        } else {
            encrypt += temp[i];
        }
    }

    cout << "Encrypted text : " << encrypt << endl;

    for (int i = 0; i < encrypt.length(); i++) {
        if (isalpha(encrypt[i])) {
            char base = isupper(encrypt[i]) ? 'A' : 'a';
            int index = encrypt[i] - base;
            int sol = (index - key + 26) % 26; 
            decrypt += char(sol + base);
        } else {
            decrypt += encrypt[i];
        }
    }

    cout << "Decrypted text : " << decrypt << endl;

    return 0;
}
