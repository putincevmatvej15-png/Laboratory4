#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct VoteGroup {
    int count;           
    vector<char> ranks;  
};

// метод Борда
void runBorda(int n, const vector<char>& candidates, const vector<VoteGroup>& groups) {
    map<char, int> scores;
    for (char c : candidates) scores[c] = 0;

    for (const auto& group : groups) {
        for (int i = 0; i < n; ++i) {
            char cand = group.ranks[i];
            int points = (n - 1) - i; 
            scores[cand] += points * group.count;
        }
    }

    cout << "Результаты  Борда " << endl;
    char winner = candidates[0];
    for (char c : candidates) {
        cout << "Кандидат " << c << ": " << scores[c] << " очков" << endl;
        if (scores[c] > scores[winner]) winner = c;
    }
    cout << "Победитель: " << winner << " (" << scores[winner] << " очков)" << endl << endl;
}

// метод Кондорсе
void runCondorcet(int n, const vector<char>& candidates, const vector<VoteGroup>& groups) {
    cout << "Результаты метода Кондорсе " << endl;
    char winner = ' ';
    bool found = false;

    for (char a : candidates) {
        bool beats_all = true;
        for (char b : candidates) {
            if (a == b) continue;

            int votes_for_a = 0;
            int votes_for_b = 0;

            for (const VoteGroup& group : groups) {
                auto pos_a = find(group.ranks.begin(), group.ranks.end(), a);
                auto pos_b = find(group.ranks.begin(), group.ranks.end(), b);

                if (pos_a < pos_b) votes_for_a += group.count;
                else votes_for_b += group.count;
            }

            if (votes_for_a <= votes_for_b) {
                beats_all = false;
                break;
            }
        }

        if (beats_all) {
            winner = a;
            found = true;
            break;
        }
    }

    if (found) cout << "Победитель: " << winner << endl;
    else cout << "Победитель не определён" << endl;
    cout << endl;
}

int main() {
    int n = 3;
    vector<char> candidates = {'A', 'B', 'C'};
    vector<VoteGroup> groups = {
        {10, {'B', 'A', 'C'}},
        {8, {'B', 'C', 'A'}},
        {5, {'A', 'C', 'B'}}
    };

    runBorda(n, candidates, groups);
    runCondorcet(n, candidates, groups);

    return 0;
}