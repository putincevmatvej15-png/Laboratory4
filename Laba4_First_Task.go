package main

import (
	"fmt"
	"math"
)

// исходная функция f(x) = 2ln(x) - 0.5x + 1 = 0
func f(x float64) float64 {
	return 2*math.Log(x) - 0.5*x + 1.0
}

// производная для метода Ньютона
func df(x float64) float64 {
	return 2.0/x - 0.5
}

// функция x = phi(x) для метода простых итераций
func phi(x float64) float64 {
	return 4*math.Log(x) + 2.0
}

// метод половинного деления
func bisection(a, b, eps float64) {
	fmt.Println("\nМетод половинного деления:")
	fmt.Println("| N | an | bn | bn - an |")
	fmt.Println("----------------------------------------------------")
	n := 0
	for (b - a) > eps {
		c := (a + b) / 2.0
		fmt.Printf("| %d | %12.6f | %12.6f | %12.6f |\n", n, a, b, b-a)
		if f(a)*f(c) < 0 {
			b = c
		} else {
			a = c
		}
		n++
	}
	fmt.Printf("Корень: %.6f\n", (a+b)/2.0)
}

// метод Ньютона
func newton(x0, eps float64) {
	fmt.Println("\nМетод Ньютона:")
	fmt.Println("| N | xn | xn+1 | xn+1 - xn |")
	fmt.Println("----------------------------------------------------")
	x := x0
	n := 0
	for {
		xNext := x - f(x)/df(x)
		diff := math.Abs(xNext - x)
		fmt.Printf("| %d | %12.6f | %12.6f | %12.6f |\n", n, x, xNext, diff)
		if diff < eps {
			x = xNext
			break
		}
		x = xNext
		n++
	}
	fmt.Printf("Корень (Ньютон): %.6f\n", x)
}

// метод простых итераций
func simpleIterations(x0, eps float64) {
	fmt.Println("\nМетод простых итераций:")
	fmt.Println("| N | xn | xn+1 | xn+1 - xn |")
	fmt.Println("----------------------------------------------------")
	x := x0
	n := 0
	for {
		xNext := phi(x)
		diff := math.Abs(xNext - x)
		fmt.Printf("| %d | %12.6f | %12.6f | %12.6f |\n", n, x, xNext, diff)
		if diff < eps {
			break
		}
		x = xNext
		n++
		if n > 100 {
			fmt.Println("Метод не сходится!")
			break
		}
	}
	fmt.Printf("Корень: %.6f\n", x)
}

func main() {
	eps := 0.0001

	fmt.Println("=== ПОИСК ПЕРВОГО КОРНЯ (отрезок [0, 1]) ===")
	bisection(0.1, 1.0, eps)
	newton(0.5, eps)
	simpleIterations(0.5, eps)

	fmt.Println("\n=== ПОИСК ВТОРОГО КОРНЯ (отрезок [10, 11]) ===")
	bisection(11.0, 12.0, eps)
	newton(11.0, eps)
	simpleIterations(11.0, eps)
}
