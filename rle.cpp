#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void initializeArrays(int length, int* numbers, char* symbols) {
    for (int i = 0; i < length; ++i) {
        numbers[i] = -1;
        symbols[i] = '1';
    }
}

void parseString(int length, int* numbers, char* symbols, const string& inputString) {
    int symbolIndex = 0;
    int numberIndex = 0;
    string tempNumber;

    for (int i = 0; i < length; i++) {
        if (i == 0) {
            symbols[symbolIndex] = inputString[i];
            symbolIndex++;
        }
        else if(isdigit(inputString[i])) {
            tempNumber += inputString[i];
        }
        else {
            numbers[numberIndex] = stoi(tempNumber);
            tempNumber = "";
            symbols[symbolIndex] = inputString[i];
            symbolIndex++;
            numberIndex++;
        }
    }
    numbers[numberIndex] = stoi(tempNumber);
}

int main() {
    int length1, length2, maxDifference;
    string string1, string2;
    cin >> length1 >> length2 >> maxDifference >> string1 >> string2;

    int numbers1[length1], numbers2[length2];
    char symbols1[length1], symbols2[length2];

    initializeArrays(length1, numbers1, symbols1);
    initializeArrays(length2, numbers2, symbols2);

    parseString(length1, numbers1, symbols1, string1);
    parseString(length2, numbers2, symbols2, string2);

    int differenceCount = 0;
    int index1 = 0, index2 = 0;

    while(index1 < length1 && index2 < length2) {
        if(numbers1[index1] == -1 || numbers2[index2] == -1) {
            break;
        }

        int minCount = min(numbers1[index1], numbers2[index2]);

        if(symbols1[index1] != symbols2[index2]) {
            differenceCount += minCount;
        }

        numbers1[index1] -= minCount;
        numbers2[index2] -= minCount;

        if (numbers1[index1] == 0) {
            index1++;
        }
        else {
            index2++;
        }
    }

    if(differenceCount < maxDifference) {
        cout << "Yes";
    }
    else {
        cout << "No";
    }

    return 0;
}
