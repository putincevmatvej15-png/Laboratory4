#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //для swap

using namespace std;

void rc4_generator(string key_str, int N) {
    vector<int> K;
    for (char c : key_str) {
        K.push_back((unsigned char)c);
    }
    int key_length = K.size();

    vector<int> S(256);
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + K[i % key_length]) % 256;
        swap(S[i], S[j]);
    }

    int i = 0;
    j = 0;
    cout << "Выведем значения для ключа \"" << key_str << "\":" << endl;

    for (int step = 0; step < N; ++step) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        swap(S[i], S[j]);

        int t = (S[i] + S[j]) % 256;
        int K_byte = S[t]; 

        cout << K_byte << " ";
    }
    cout << endl;
}

int main() {
    string key;
    int n;

    cout << "Введите ключ: ";
    cin >> key;
    cout << "Введи кол-во чисел: ";
    cin >> n;

    rc4_generator(key, n);

    return 0;
}