#include <iostream>
#include <string>
#include <map>
#include <cmath>
using namespace std;

const int base = 3;
const int length = 4;

/* ------------------------------------

- Character set limited to 3 (A = 0, B = 1, C = 2)
- String is 4 characters in length (AAAA, AAAB, ..., CCCC)
  => Total 81 different combinations (3^4)

------------------------------------ */

int stringToValue(string s, map<char, int>& charSet) {
    int size = s.size();
    int value = 0;

    for (int i = 0; i < size; ++i) {
        value += (charSet[s[size - 1 - i]] * pow(base, i));
    }

    return value;
}

string valToString(int val, map<int, char>& intSet) {
    int maxVal = static_cast<int>(pow(base, length));
    val %= maxVal;

    string result(length, intSet[0]);

    for (int i = length - 1; i >= 0 && val > 0; --i) {
        result[i] = intSet[val % base];
        val /= base;
    }

    return result;


}

string PRP(map<char, int>& charSet, map<int, char>& intSet, string s) {
    int code = stringToValue(s, charSet);
    int newValue = ((10 * code) + 7) % static_cast<int>(pow(base, length));
    string encoded = valToString(newValue, intSet);

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

    string start = "CBBA";
    map<string, int> codes;
    
    while (true) {
        string newText = PRP(charSet, intSet, start);

        if (codes.count(newText) == 0) {
            cout << "adding: " << newText << endl;
            codes[newText] = 1;
            start = newText;
        } else {
            cout << "ending with size: " << codes.size() << endl;
            break;
        }
    }
}