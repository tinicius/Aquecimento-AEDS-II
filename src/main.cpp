#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// struct myComp {
//     constexpr bool operator()(
//         pair<int, int> const& a,
//         pair<int, int> const& b)
//         const noexcept
//     {
//         return a.second < b.second;
//     }
// };

struct compare {
    bool operator()(pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    }
};

bool isValidChar(char c) {
    if (c == ' ' || c == (char)10) return false;

    return true;
}

int main() {
    int k = 10;

    map<string, int> freq_table;

    priority_queue<pair<string, int>, vector<pair<string, int>>, compare> heap;

    FILE* file = fopen("../dataset/input.data", "r");

    char last;
    char aux;
    string word;

    cout << file << endl;

    while (fscanf(file, "%c", &aux) > 0) {
        if (isValidChar(aux)) {
            word += aux;
        } else {
            // Ignorando '-, /, _' no meio de uma palavra
            if (aux == '-' || aux == '/' || aux == '_') continue;

            if (!word.empty()) {
                freq_table[word]++;
            };

            // \n
            if (aux == (char)10) {
                // Linha
            };

            if (last == (char)10 && aux == (char)10) {
                // Parágrafo
            };

            // // fim de uma sentença
            // if (aux == '?' || aux == '!' || aux == '.') {

            // };

            word = "";
        }

        last = aux;
    }

    // TODO: lógica pro final do arquivo.

    // Provalmente desnecessário inserir os 10 primeiros de maneira separada
    int counter = 0;
    for (auto w : freq_table) {
        if (counter == k) break;
        heap.push(w);
        counter++;
    }

    for (auto w : freq_table) {
        auto menor = heap.top();

        cout << w.first << endl;

        if (w.second > menor.second) {
            heap.pop();
            heap.push(w);
        }
    }

    vector<string> ans;

    while (!heap.empty()) {
        auto top = heap.top();
        ans.push_back(top.first);
        heap.pop();
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << " ";
    }

    fclose(file);

    return 0;
}