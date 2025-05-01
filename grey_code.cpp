#include <iostream>
#include <vector>
using namespace std;

void fillColumnWithBinaryPattern(vector<vector<int>>& gray_codes, int column, int rows_to_fill) {
    for (int i = 0; i < rows_to_fill / 2; ++i) {
        gray_codes[i][column] = 0;
        gray_codes[rows_to_fill / 2 + i][column] = 1;
    }
}

void mirrorAndCopyCodes(vector<vector<int>>& gray_codes, int current_column, int rows_to_copy) {
    int source_row = rows_to_copy - 1;

    for (int i = 0; i < current_column + 1; ++i) {
        for (int j = 0; j < rows_to_copy; ++j) {
            gray_codes[rows_to_copy + j][i] = gray_codes[source_row][i];
            source_row--;
        }
        source_row = rows_to_copy - 1;
    }
}

void reverseBitsInRows(vector<vector<int>>& gray_codes, int bits_count, int total_rows) {
    for (int i = 0; i < total_rows; ++i) {
        int left = 0;
        int right = bits_count - 1;

        while (left < right) {
            swap(gray_codes[i][left], gray_codes[i][right]);
            left++;
            right--;
        }
    }
}

int main() {
    int bits_count;
    cin >> bits_count;

    int total_codes = 1;
    for (int i = 0; i < bits_count; ++i) {
        total_codes *= 2;
    }

    vector<vector<int>> gray_codes(total_codes, vector<int>(bits_count, 0));

    int current_rows = 2;
    for (int column = 0; column < bits_count; ++column) {
        fillColumnWithBinaryPattern(gray_codes, column, current_rows);
        current_rows *= 2;
    }

    int rows_to_copy = 1;
    for (int column = 0; column < bits_count - 1; ++column) {
        rows_to_copy *= 2;
        mirrorAndCopyCodes(gray_codes, column, rows_to_copy);
    }

    reverseBitsInRows(gray_codes, bits_count, total_codes);

    for (const auto& code : gray_codes) {
        for (int bit : code) {
            cout << bit;
        }
        cout << endl;
    }

    return 0;
}