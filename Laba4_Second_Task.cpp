#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

// создадим генератор, для использования одинаковых последовательностей
random_device rd;
ranlux48 gen(rd());

// задание 1,2,3 связаны общим массивом
vector<int> task1_2_3(int n) {
    uniform_int_distribution<int> dist1(-100, 100);
    vector<int> arr(n);
    cout << "Массив: ";
    for (int i = 0; i < n; ++i) {
        arr[i] = dist1(gen);
        cout << arr[i] << " ";
    }
    cout << endl;

    int max_idx = 0;
    long long prod_neg = 1;
    bool has_neg = false;

    for (int i = 0; i < n; ++i) {
        if (arr[i] > arr[max_idx]) max_idx = i;
        if (arr[i] < 0) {
            prod_neg *= arr[i];
            has_neg = true;
        }
    }

    int sum_before_max = 0;
    for (int i = 0; i < max_idx; ++i) {
        if (arr[i] > 0) sum_before_max += arr[i];
    }
    cout << "Индекс макс. элемента: " << max_idx << endl;
    cout << "Произведение отрицательных: " << (has_neg ? to_string(prod_neg) : "нет") << endl;
    cout << "Сумма положительных до макс. элемента: " << sum_before_max << endl;

    cout << "Локальные максимумы (индекс:значение): ";
    int count = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
            cout << i << ":" << arr[i] << " ";
            count++;
        }
    }
    cout << "\nКоличество локальных максимумов: " << count << endl;
    return arr;
}

// задание 4
void task4() {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    uniform_int_distribution<int> dist(0, alphabet.length() - 1);
    string s = "";
    for (int i = 0; i < 10; ++i) {
        s += alphabet[dist(gen)];
    }

    cout << "\nИсходная строка: " << s << endl;
    for (char &c : s) {
        if (islower(c)) c = toupper(c);
        else if (isupper(c)) c = tolower(c);
    }
    cout << "Строка с измененным регистром: " << s << endl;
}

// задание 5
void task5(int n) {
    if (n < 30) n = 30;
    uniform_int_distribution<int> dist2(-20, 20);
    vector<int> arr(n);
    map<int, int> counts;

    for (int i = 0; i < n; ++i) {
        arr[i] = dist2(gen);
        counts[arr[i]]++;
    }

    int most_frequent = arr[0];
    for (auto const& [num, count] : counts) {
        if (count > counts[most_frequent]) most_frequent = num;
    }

    sort(arr.begin(), arr.end());

    cout << "\nСамое частое число: " << most_frequent
         << " (встречается " << counts[most_frequent] << " раз)" << endl;
    cout << "Отсортированный массив: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian"); 

    int n;
    cout << "Введите размер массива n:";
    cin >> n;
    if (n < 10) {
        cout << "n должно быть не меньше 10." << endl;
        return 1;
    }
    cout << "\n выполнение заданий 1, 2, 3" << endl;
    task1_2_3(n);
    cout << "\n выполнение задания 4 " << endl;
    task4();
    cout << "\n выполнение задания 5 " << endl;
    task5(n);
    return 0;
}