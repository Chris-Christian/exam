#include <iostream>
using namespace std;

string encrypt(string text, string key) {
    string result = "";
    int n = text.length();

    key += text;
    key = key.substr(0, n);

    for (int i = 0; i < n; i++) {
        char enc = ((text[i] - 'A') + (key[i] - 'A')) % 26 + 'A';
        result += enc;
    }

    return result;
}

string decrypt(string text, string key) {
    string result = "";
    int n = text.length();

    for (int i = 0; i < n; i++) {
        char dec = ((text[i] - 'A') - (key[i] - 'A') + 26) % 26 + 'A';
        result += dec;
        key += dec;
    }

    return result;
}

int main() {
    string text = "HELLO";
    string key = "KEY";

    string encrypted = encrypt(text, key);
    cout << "Encrypted: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
