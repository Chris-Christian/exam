#include <iostream>
using namespace std;

int main() {
    string arr1 = "qwertyuiopasdfghjklzxcvbnm";
    string arr2 = "QWERTYUIOPASDFGHJKLZXCVBNM";
    string temp = "Cyber Security";
    string encrypt;
    string decrypt;

    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] >= 'a') {
            if (temp[i] != ' ') {
                int index = temp[i] - 97;
                encrypt += arr1[index];
            } else {
                encrypt += ' ';
            }
        } else {
            if (temp[i] != ' ') {
                int index = temp[i] - 65;
                encrypt += arr2[index];
            } else {
                encrypt += ' ';
            }
        }
    }

    cout << "Encrypted text : " << encrypt << endl;

    for (int i = 0; i < encrypt.length(); i++) {
        int temp2 = 0;
        int j = 0;
        if (encrypt[i] >= 'a') {
            if (encrypt[i] != ' ') {
                while (arr1[j] != encrypt[i]) {
                    temp2++;
                    j++;
                }
                decrypt += char(temp2 + 97);
            } else {
                decrypt += ' ';
            }
        } else {
            if (encrypt[i] != ' ') {
                while (arr2[j] != encrypt[i]) {
                    temp2++;
                    j++;
                }
                decrypt += char(temp2 + 65);
            } else {
                decrypt += ' ';
            }
        }
    }

    cout << "Decrypted text : " << decrypt;
    return 0;
}
