package main

import (
	"fmt"
)

// Структура для группы избирателей
type VoteGroup struct {
	count int
	ranks []rune
}

// метод Борда
func runBorda(n int, candidates []rune, groups []VoteGroup) {
	scores := make(map[rune]int)
	for _, c := range candidates {
		scores[c] = 0
	}

	for _, group := range groups {
		for i, cand := range group.ranks {
			points := (n - 1) - i
			scores[cand] += points * group.count
		}
	}

	fmt.Println("Результаты Борда")
	winner := candidates[0]
	for _, c := range candidates {
		fmt.Printf("Кандидат %c: %d очков\n", c, scores[c])
		if scores[c] > scores[winner] {
			winner = c
		}
	}
	fmt.Printf("Победитель: %c (%d очков)\n\n", winner, scores[winner])
}

// метод Кондорсе
func runCondorcet(n int, candidates []rune, groups []VoteGroup) {
	fmt.Println("Результаты метода Кондорсе")
	winner := ' '
	found := false

	for _, a := range candidates {
		beatsAll := true
		for _, b := range candidates {
			if a == b {
				continue
			}

			votesForA := 0
			votesForB := 0

			for _, group := range groups {
				posA := -1
				posB := -1
				for idx, r := range group.ranks {
					if r == a {
						posA = idx
					}
					if r == b {
						posB = idx
					}
				}
				if posA < posB {
					votesForA += group.count
				} else {
					votesForB += group.count
				}
			}

			if votesForA <= votesForB {
				beatsAll = false
				break
			}
		}

		if beatsAll {
			winner = a
			found = true
			break
		}
	}

	if found {
		fmt.Printf("Победитель: %c\n", winner)
	} else {
		fmt.Println("Победитель не определён")
	}
	fmt.Println()
}

func main() {
	n := 3
	candidates := []rune{'A', 'B', 'C'}
	groups := []VoteGroup{
		{12, []rune{'A', 'B', 'C'}},
		{8, []rune{'B', 'C', 'A'}},
		{5, []rune{'B', 'C', 'A'}},
	}

	runBorda(n, candidates, groups)
	runCondorcet(n, candidates, groups)
}
