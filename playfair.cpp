#include <iostream>
#include <vector>
using namespace std;

void maketbl(string key, char table[5][5]) {
    string remaining = "";
    int temp[26] = {0};

    for (int i = 0; i < key.length(); i++) {
        int temp2 = key[i] - 'a';
        if (key[i] != 'j' && temp[temp2] == 0) {
            char c = temp2 + 'a';
            remaining += c;
            temp[temp2] = 1;
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        int temp2 = c - 'a';
        if (c != 'j' && temp[temp2] == 0) {
            remaining += c;
        }
    }

    int i1 = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            table[i][j] = remaining[i1];
            i1++;
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}

int rowfinder(char table[5][5], char c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == c) {
                return i;
            }
        }
    }
}

int columnfinder(char table[5][5], char c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == c) {
                return j;
            }
        }
    }
}

void success(char table[5][5], string pt) {
    vector<string> pair;
    string new_pt = "", encrypt = "", decrypt = "";
    int flag = 0;

    for (int i = 0; i < pt.length(); i++) {
        if (pt[i] != ' ') {
            new_pt += pt[i];
        }
    }

    int j = 0;
    while (j < new_pt.length()) {
        if (new_pt[j] == new_pt[j + 1]) {
            string s1 = "";
            for (int i = 0; i <= j; i++) {
                s1 += new_pt[i];
            }
            s1 += 'x';
            for (int t = j + 1; t < new_pt.length(); t++) {
                s1 += new_pt[t];
            }
            new_pt = s1;
            j = 0;
        } else {
            j++;
        }
    }

    int parts;
    if (new_pt.length() % 2 == 0) {
        parts = new_pt.length() / 2;
    } else {
        parts = (new_pt.length() / 2) + 1;
        flag = 1;
    }

    if (flag == 1) {
        new_pt += 'x';
    }

    cout << "Plain text : ";
    for (int i = 0; i < parts; i++) {
        string temp3 = "";
        for (int j = (i * 2); j < ((i + 1) * 2); j++) {
            temp3 += new_pt[j];
        }
        cout << temp3;
        pair.push_back(temp3);
    }
    cout << endl;

    for (int i = 0; i < pair.size(); i++) {
        int row1 = rowfinder(table, pair[i][0]);
        int row2 = rowfinder(table, pair[i][1]);
        int col1 = columnfinder(table, pair[i][0]);
        int col2 = columnfinder(table, pair[i][1]);

        if (row1 == row2) {
            int newcol1 = (col1 + 1) % 5;
            int newcol2 = (col2 + 1) % 5;
            encrypt += table[row1][newcol1];
            encrypt += table[row2][newcol2];
        } else if (col1 == col2) {
            int newrow1 = (row1 + 1) % 5;
            int newrow2 = (row2 + 1) % 5;
            encrypt += table[newrow1][col1];
            encrypt += table[newrow2][col2];
        } else {
            encrypt += table[row1][col2];
            encrypt += table[row2][col1];
        }
    }

    cout << "Encrypted text : " << encrypt << endl;

    for (int i = 0; i < encrypt.size(); i += 2) {
        int row1 = rowfinder(table, encrypt[i]);
        int row2 = rowfinder(table, encrypt[i + 1]);
        int col1 = columnfinder(table, encrypt[i]);
        int col2 = columnfinder(table, encrypt[i + 1]);
        int newcol1, newcol2, newrow1, newrow2;

        if (row1 == row2) {
            newcol1 = (col1 - 1 + 5) % 5;
            newcol2 = (col2 - 1 + 5) % 5;
            decrypt += table[row1][newcol1];
            decrypt += table[row2][newcol2];
        } else if (col1 == col2) {
            newrow1 = (row1 - 1 + 5) % 5;
            newrow2 = (row2 - 1 + 5) % 5;
            decrypt += table[newrow1][col1];
            decrypt += table[newrow2][col2];
        } else {
            decrypt += table[row1][col2];
            decrypt += table[row2][col1];
        }
    }

    if (flag == 1) {
        string temp2 = "";
        for (int i = 0; i < decrypt.length() - 1; i++) {
            temp2 += decrypt[i];
        }
        decrypt = temp2;
    }

    int r = 0;
    while (r < decrypt.length()) {
        if (decrypt[r] == decrypt[r + 2] && decrypt[r + 1] == 'x') {
            string s1 = "";
            for (int e = 0; e <= r; e++) {
                s1 += decrypt[e];
            }
            for (int v = r + 2; v <= decrypt.length(); v++) {
                s1 += decrypt[v];
            }
            decrypt = s1;
            r = 0;
        } else {
            r++;
        }
    }

    cout << "Decrypted text : " << decrypt;
}

int main() {
    string key = "monarchy";
    string pt = "move forward";
    char table[5][5];

    cout << "The table formed : " << endl;
    maketbl(key, table);
    success(table, pt);

    return 0;
}
