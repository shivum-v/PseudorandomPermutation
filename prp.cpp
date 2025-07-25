#include <iostream>
#include <string>
#include <map>
#include <cmath>
using namespace std;

const int base = 34;
const int length = 6;

long long stringToValue(string s, map<char, int>& charSet) {
    int size = s.size();
    long long value = 0;

    for (int i = 0; i < size; ++i) {
        value += (charSet[s[size - 1 - i]] * pow(base, i));
    }

    return value;
}

string valToString(long long val, map<int, char>& intSet) {
    long long maxVal = static_cast<int>(pow(base, length));
    val %= maxVal;

    string result(length, intSet[0]);

    for (int i = length - 1; i >= 0 && val > 0; --i) {
        result[i] = intSet[val % base];
        val /= base;
    }

    return result;
}

string PRP(map<char, int>& charSet, map<int, char>& intSet, string s) {
    long long code = stringToValue(s, charSet);
    long long newValue = ((10 * code) + 7) % static_cast<long long>(pow(base, length));
    string encoded = valToString(newValue, intSet);

    return encoded;
}

int main() {
    map<char, int> charSet;
    map<int, char> intSet;
    
    // Initializing charSet and intSet
    for (int i = 0; i < 10; ++i) {
        charSet['0' + i] = i;
        intSet[i] = '0' + i;
    }

    int ctr = 10;
    for (int i = 0; i < 26; ++i) {
        if (('A' + i) == 'I' || ('A' + i) == 'O') continue;

        charSet['A' + i] = ctr;
        intSet[ctr] = 'A' + i;
        ++ctr;
    }

    string start = "CVMC9P";
    map<string, int> codes;
    long long count = 0;

    while (true) {
        string newText = PRP(charSet, intSet, start);

        if (codes.count(newText) == 0) {
            cout << "adding: " << newText << endl;
            codes[newText] = 1;
            start = newText;
            ++count;

            cout << "total numbers: " << count << endl;
        } else {
            cout << "ending with size: " << count << endl;
            break;
        }
    }
}