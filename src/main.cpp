#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include "Heap.hpp"

using namespace std;

struct compare {
    bool operator()(pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    }
};

bool isValidWord(string s) {
    auto expAcents = {"--", "^", "-", " — ", " —", "—", "”", "“", "-”", "——"};

    auto expChar = {'-', '"', '\xE2', '\x80', '\x9D', '\x9C', '\x94'};

    for (auto a : expAcents) {
        if (s.find(a) != s.npos) return false;
    }

    for (auto a : expChar) {
        if (s.find(a) != s.npos) return false;
    }

    return true;
}

bool isValidChar(char c) {
    string acents = "áàâãéèêíïóôõúüçÁÀÂÃÉÈÊÍÏÓÔÕÚÜÇ";

    if (acents.find(c) != acents.npos) return true;

    return iswalnum(c);
}

void loadStopWords(map<string, int>& sw) {
    std::ifstream arq("../dataset/stopwords.data");

    if (!arq.is_open()) {
        std::cerr << "Error opening arq" << std::endl;
        exit(1);
    }

    string line;

    while (getline(arq, line)) {
        sw[line]++;
    }

    arq.close();
}

void countWords(map<string, int>& freq_table) {
    FILE* file = fopen("../dataset/input.data", "r");

    if (file == 0) {
        std::cerr << "Error opening arq" << std::endl;
        exit(1);
    }

    char aux;
    string word;

    while (fscanf(file, "%c", &aux) > 0) {
        if (isValidChar(aux)) {
            word += tolower(aux);
        } else {
            if (aux == '-' || aux == '/' || aux == '_') continue;

            if (!word.empty() and isValidWord(word)) {
                freq_table[word]++;
            };

            word = "";
        }
    }

    fclose(file);
}

void initializeHeapWithKElements(Heap& heap, map<string, int>& freq_table,
                                 map<string, int> sw, int k) {
    int counter = 0;

    for (auto w : freq_table) {
        if (counter == k) break;

        if (sw[w.first] == 0) {
            heap.push(w);
            counter++;
        }
    }
}

void insertRemainingWordsInHeap(Heap& heap, map<string, int>& freq_table,
                                map<string, int> sw) {
    for (auto w : freq_table) {
        auto menor = heap.top();

        if (w.second > menor.second) {
            if (sw[w.first] == 0) {
                heap.pop();
                heap.push(w);
            }
        }
    }
}

vector<string> getHeapElements(Heap& heap) {
    vector<string> ans;

    while (!heap.empty()) {
        auto top = heap.top();
        ans.push_back(top.first);
        heap.pop();
    }

    return ans;
}

void showElementsInCorrectOrder(vector<string>& ans) {
    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] << endl;
}

int main() {
    int k = 20;

    map<string, int> sw;
    loadStopWords(sw);

    map<string, int> freq_table;
    countWords(freq_table);

    Heap heap;

    initializeHeapWithKElements(heap, freq_table, sw, k);

    insertRemainingWordsInHeap(heap, freq_table, sw);

    vector<string> ans = getHeapElements(heap);

    // showElementsInCorrectOrder(ans);

    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] << " " << freq_table[ans[i]] << endl;

    return 0;
}