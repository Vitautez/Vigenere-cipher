#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

void matchingTexts(const string& text, const string& keyword, vector<char>& textArray, vector<char>& keyArray) {
    textArray.clear();
    keyArray.clear();

    int keyIndex = 0;
    int keyLength = keyword.length();

    for (char c : text) {
        textArray.push_back(c);
        if (c != ' ') {
            keyArray.push_back(keyword[keyIndex % keyLength]);
            keyIndex++;
        }
        else {
            keyArray.push_back(' ');
        }
    }
}

const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[{]};:'\",<.>/?`~";

int getAlphabeticIndex(char c) {
    c = toupper(c);
    size_t index = alphabet.find(c);
    if (index != string::npos) {
        return static_cast<int>(index);
    }
    return -1;
}

void encryptTextAlphabet(const vector<char>& textArray, const vector<char>& keyArray, vector<char>& encryptedArray) {
    encryptedArray.clear();

    for (size_t i = 0; i < textArray.size(); i++) {
        if (textArray[i] == ' ') {
            encryptedArray.push_back(' ');
            continue;
        }

        int m_i = getAlphabeticIndex(textArray[i]);
        int k_i = getAlphabeticIndex(keyArray[i]);

        int c_i = (m_i + k_i) % alphabet.size();
        encryptedArray.push_back(alphabet[c_i]);
    }
}

void decryptTextAlphabet(const vector<char>& encryptedArray, const vector<char>& keyArray, vector<char>& decryptedArray) {
    decryptedArray.clear();

    for (size_t i = 0; i < encryptedArray.size(); i++) {
        if (encryptedArray[i] == ' ') {
            decryptedArray.push_back(' ');
            continue;
        }

        int c_i = getAlphabeticIndex(encryptedArray[i]);
        int k_i = getAlphabeticIndex(keyArray[i]);

        int d_i = (c_i - k_i + alphabet.size()) % alphabet.size();
        decryptedArray.push_back(alphabet[d_i]);
    }
}

void encryptTextASCII(const vector<char>& textArray, const vector<char>& keyArray, vector<char>& encryptedArray) {
    encryptedArray.clear();

    for (size_t i = 0; i < textArray.size(); i++) {
        if (textArray[i] == ' ') {
            encryptedArray.push_back(' ');
            continue;
        }

        int m_i = static_cast<int>(textArray[i]);
        int k_i = static_cast<int>(keyArray[i]);

        int c_i = (m_i + k_i) % 256;
        encryptedArray.push_back(static_cast<char>(c_i));
    }
}

void decryptTextASCII(const vector<char>& encryptedArray, const vector<char>& keyArray, vector<char>& decryptedArray) {
    decryptedArray.clear();

    for (size_t i = 0; i < encryptedArray.size(); i++) {
        if (encryptedArray[i] == ' ') {
            decryptedArray.push_back(' ');
            continue;
        }

        int c_i = static_cast<int>(encryptedArray[i]);
        int k_i = static_cast<int>(keyArray[i]);

        int d_i = (c_i - k_i + 128) % 128;
        decryptedArray.push_back(static_cast<char>(d_i));
    }
}

void displayResults(const vector<char>& textArray, const vector<char>& keyArray,
    const vector<char>& encryptedAlphabet, const vector<char>& encryptedASCII) {
    cout << "Text:         ";
    for (char c : textArray) cout << c;
    cout << "\n";

    cout << "Keyword:           ";
    for (char c : keyArray) cout << c;
    cout << "\n";

    cout << "Alphabet Encrypted: ";
    for (char c : encryptedAlphabet) cout << c;
    cout << "\n";

    cout << "ASCII Encrypted:    ";
    for (char c : encryptedASCII) cout << c;
    cout << "\n";
}

int main() {
    string text, keyword, encryptedtext, decryptKey;
    int choice;

    cout << "Please input the text you would like to encrypt: ";
    getline(cin, text);

    cout << "Please input the keyword: ";
    cin >> keyword;

    vector<char> textArray, keyArray, encryptedAlphabet, encryptedASCII;
    matchingTexts(text, keyword, textArray, keyArray);
    encryptTextAlphabet(textArray, keyArray, encryptedAlphabet);
    encryptTextASCII(textArray, keyArray, encryptedASCII);

    displayResults(textArray, keyArray, encryptedAlphabet, encryptedASCII);

    cout << "\nPlease input the encryptedtext to decrypt: ";
    cin.ignore();
    getline(cin, encryptedtext);

    cout << "Please input the keyword for decryption: ";
    cin >> decryptKey;

    cout << "\nChoose decryption method:\n";
    cout << "1. Alphabetic Decryption\n";
    cout << "2. ASCII Decryption\n";
    cout << "Enter choice number: ";
    cin >> choice;

    vector<char> encryptedTextArray, encryptedKeyArray, decryptedAlphabet, decryptedASCII;
    matchingTexts(encryptedtext, decryptKey, encryptedTextArray, encryptedKeyArray);

    if (choice == 1) {
        decryptTextAlphabet(encryptedTextArray, encryptedKeyArray, decryptedAlphabet);
        cout << "\nDecryption Results using Alphabetic: ";
        for (char c : decryptedAlphabet) cout << c;
        cout << "\n";
    }
    else if (choice == 2) {
        decryptTextASCII(encryptedTextArray, encryptedKeyArray, decryptedASCII);
        cout << "\nDecryption Results using ASCII: ";
        for (char c : decryptedASCII) cout << c;
        cout << "\n";
    }
    else {
        cout << "\nIncorrect choice chosen\n";
    }

    return 0;
}















