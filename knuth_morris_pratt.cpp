#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> findSubstringPositions(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.size(), m = pattern.size();
    if (m == 0 || n < m) return positions;

    for (int i = 0; i <= n - m; ++i) {
        int j;
        for (j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) break;
        }
        if (j == m) positions.push_back(i);
    }
    return positions;
}

int main() {
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);

    vector<int> positions = findSubstringPositions(text, pattern);

    cout << positions.size() << endl;
    for (int pos : positions) {
        cout << pos << ' ';
    }
    cout << endl;

    return 0;
}