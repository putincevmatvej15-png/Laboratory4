#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


float f(float x) {  // исходная функция f(x) = 2ln(x) — 0.5x +1 = 0
    return 2.0 * log(x) - 0.5 * x + 1.0;
}

float df(float x) {     // производная для метода Ньютона
    return 2.0 / x - 0.5;
}

float phi(float x) {    // ф-я x = phi(x) для метода простых итераций
    return 4.0 * log(x) + 2.0;
}

// использую метод половинного деления
void bisection(float a, float b, float eps) {
    cout << "\nМетод половинного деления:" << endl;
    cout << "| N | an | bn | bn - an |" << endl;
    cout << "----------------------------------------------------" << endl;
    int n = 0;
    while ((b - a) > eps) {
        float c = (a + b) / 2.0;
        cout << "| " << setw(1) << n++ << " | " << fixed << setprecision(6) 
             << setw(12) << a << " | " << setw(12) << b << " | " << setw(12) << (b - a) << " |" << endl;
        if (f(a) * f(c) < 0) b = c;
        else a = c;
    }
    cout << "Корень: " << (a + b) / 2.0 << endl;
}

// использую метод Ньютона
void newton(float x0, float eps) {
    cout << "\nМетод Ньютона:" << endl;
    cout << "| N | xn | xn+1 | xn+1 - xn |" << endl;
    cout << "----------------------------------------------------" << endl;
    float x = x0;
    int n = 0;
    while (true) {
        float x_next = x - f(x) / df(x);
        float diff = abs(x_next - x);
        cout << "| " << setw(1) << n++ << " | " << fixed << setprecision(6) 
             << setw(12) << x << " | " << setw(12) << x_next << " | " << setw(12) << diff << " |" << endl;
        if (diff < eps) {
            x = x_next;
            break;
        }
        x = x_next;
    }
    cout << "Корень (Ньютон): " << x << endl;
}

// использую метод простых итераций
void simpleIterations(float x0, float eps) {
    cout << "\nМетод простых итераций:" << endl;
    cout << "| N | xn | xn+1 | xn+1 - xn |" << endl;
    cout << "----------------------------------------------------" << endl;
    float x = x0;
    int n = 0;
    while (true) {
        float x_next = phi(x);
        float diff = abs(x_next - x);
        cout << "| " << setw(1) << n++ << " | " << fixed << setprecision(6) 
             << setw(12) << x << " | " << setw(12) << x_next << " | " << setw(12) << diff << " |" << endl;
        if (diff < eps) break;
        x = x_next;
        if (n > 100) {
            cout << "Метод не сходится!" << endl;
            break;
        }
    }
    cout << "Корень: " << x << endl;
}

int main() {
    float eps = 0.0001;

    cout << "=== ПОИСК ПЕРВОГО КОРНЯ (отрезок [0, 1]) ===" << endl;
    bisection(0.1, 1.0, eps);
    newton(0.5, eps);
    simpleIterations(0.5, eps);

    cout << "\n=== ПОИСК ВТОРОГО КОРНЯ (отрезок [10, 11]) ===" << endl;
    bisection(11.0, 12.0, eps);
    newton(11.0, eps);
    simpleIterations(11.0, eps);

    return 0;
}