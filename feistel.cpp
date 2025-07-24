#include <iostream>
#include <string>
#include <map>
#include <cmath>
using namespace std;

const int base = 3;
const int rounds = 4;

int stringToValue(string s, map<char, int>& charSet) {
    int size = s.size();
    int value = 0;

    for (int i = 0; i < size; ++i) {
        value += (charSet[s[size - 1 - i]] * pow(base, i));
    }

    return value;
}

string valToString(int val, map<int, char>& intSet, int size = 2) {
    /* if (val == 0) return std::string(1, intSet[0]);
    
    std::string result;
    while (val > 0) {
        int digit = val % base;
        result = intSet[digit] + result; // prepend character
        val /= base;
    }
    return result; */

    int maxVal = static_cast<int>(pow(base, size)); // 3^2 = 9
    val %= maxVal;

    string result(size, intSet[0]); // Start with "AA"

    for (int i = size - 1; i >= 0 && val > 0; --i) {
        result[i] = intSet[val % base];
        val /= base;
    }

    return result;
}

int F(string s, map<char, int> charSet, int key) {
    int size = s.size();
    int sum = 0;

    for (int i = 1; i <= size; ++i) {
        sum += (charSet[s[i - 1]] * pow(key, i));
    }

    return sum % static_cast<int>(pow(base, size));
}

string feistelEncode(map<char, int>& charSet, map<int, char>& intSet, string s) {
    // 1) Split string s into sections L0 and R0
    string L0 = s.substr(0, s.size() / 2), R0 = s.substr(s.size() / 2);
    string encoded, left, right;

    // Begin Feistel Rounds
    for (int i = 1; i <= rounds; ++i) {
        left = R0;
        right = valToString(stringToValue(L0, charSet) ^ F(R0, charSet, i), intSet, R0.size());

        L0 = left, R0 = right;
        //cout << L0 << ' ' << R0 << endl;
        encoded = R0 + L0;
    }

    cout << encoded << endl;
    return encoded;
}

int main() {
    map<char, int> charSet;
    map<int, char> intSet;
    
    // Set to associate each letter with a number value
    for (int i = 0; i < base; ++i) {
        charSet['A' + i] = i;
        intSet[i] = 'A' + i;
    }

    string plaintext = "CBBA";
    map<string, int> codes;
    codes[plaintext] = 1;
    
    while (true) {
        string newText = feistelEncode(charSet, intSet, plaintext);

        if (codes.count(newText) == 0) {
            codes[newText] = 1;
            plaintext = newText;
        } else {
            cout << codes.size() << endl;
            break;
        }
    }
}