#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

const char PARITY_BIT_PLACEHOLDER = '2';

// Вычисляет позиции контрольных битов в коде Хэмминга
vector<int> calculateControlBitPositions(int data_length) {
    vector<int> positions;
    int bit_position = 1;
    while (bit_position <= data_length) {
        positions.push_back(bit_position);
        bit_position <<= 1; // Умножаем на 2
    }
    return positions;
}

// Вычисляет количество контрольных битов для заданной длины данных
int calculateRequiredControlBits(int data_length) {
    int control_bits = 0;
    while ((1 << control_bits) < data_length + control_bits + 1) {
        control_bits++;
    }
    return control_bits;
}

// Проверяет код Хэмминга и находит позицию ошибки
int detectErrorPosition(const char* hamming_code, int code_length, int control_bits_count) {
    int error_position = 0;

    for (int i = 0; i < control_bits_count; ++i) {
        int control_bit_pos = 1 << i; // 2^i
        int parity = 0;

        // Проверяем все биты, которые включают текущий контрольный бит
        for (int j = control_bit_pos; j <= code_length; j += 2 * control_bit_pos) {
            for (int k = j; k < min(j + control_bit_pos, code_length + 1); ++k) {
                if (hamming_code[k] != PARITY_BIT_PLACEHOLDER) {
                    parity ^= (hamming_code[k] - '0');
                }
            }
        }

        // Если контрольный бит не совпадает с вычисленной четностью
        if ((hamming_code[control_bit_pos] - '0') != parity) {
            error_position += control_bit_pos;
        }
    }

    return error_position;
}

// Исправляет ошибку в коде Хэмминга
void correctHammingCode(char* hamming_code, int error_pos) {
    if (error_pos > 0 && error_pos < strlen(hamming_code)) {
        hamming_code[error_pos] = (hamming_code[error_pos] == '0') ? '1' : '0';
    }
}

// Извлекает исходные данные из кода Хэмминга
string extractOriginalData(const char* hamming_code, int code_length) {
    string original_data;
    int next_control_bit = 1;

    for (int i = 1; i <= code_length; ++i) {
        if (i == next_control_bit) {
            next_control_bit <<= 1;
            continue;
        }
        original_data += hamming_code[i];
    }

    return original_data;
}

void processHammingCode(const string& input_code) {
    vector<char> hamming_code(input_code.size() + 1, PARITY_BIT_PLACEHOLDER);
    copy(input_code.begin(), input_code.end(), hamming_code.begin() + 1);

    int control_bits_count = calculateRequiredControlBits(input_code.size());
    int error_position = detectErrorPosition(hamming_code.data(), input_code.size(), control_bits_count);

    if (error_position != 0) {
        correctHammingCode(hamming_code.data(), error_position);
    }

    string original_data = extractOriginalData(hamming_code.data(), input_code.size());
    cout << original_data << endl;
}

int main() {
    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        string input_code;
        cin >> input_code;
        processHammingCode(input_code);
    }

    return 0;
}