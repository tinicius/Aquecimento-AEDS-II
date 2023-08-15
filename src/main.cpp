#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "Heap.hpp"

using namespace std;

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

void loadStopWords(unordered_map<string, int>& stopWordsTable) {
    ifstream file("../dataset/stopwords.data");

    if (!file.is_open()) {
        cerr << "Erro ao abrir um dos arquivos de entrada!" << std::endl;
        exit(1);
    }

    string line;

    while (getline(file, line)) {
        stopWordsTable[line]++;
    }

    file.close();
}

void countWords(unordered_map<string, int>& freqWordsTable) {
    ifstream file("../dataset/input.data");

    if (!file.is_open()) {
        cerr << "Erro ao abrir um dos arquivos de entrada!" << std::endl;
        exit(1);
    }

    char aux;
    string word;

    while (file) {
        file.get(aux);

        if (isValidChar(aux)) {
            word += tolower(aux);
        } else {
            if (aux == '-' || aux == '/' || aux == '_') continue;

            if (!word.empty() and isValidWord(word)) {
                freqWordsTable[word]++;
            };

            word = "";
        }
    }

    file.close();
}

void initializeHeapWithKElements(Heap& heap,
                                 unordered_map<string, int>& freq_table,
                                 unordered_map<string, int> sw, int k) {
    int counter = 0;

    for (auto w : freq_table) {
        if (counter == k) break;

        if (sw[w.first] == 0) {
            heap.push(w);
            counter++;
        }
    }
}

void insertRemainingWordsInHeap(Heap& heap,
                                unordered_map<string, int>& freq_table,
                                unordered_map<string, int> sw) {
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

    unordered_map<string, int> sw;
    loadStopWords(sw);

    unordered_map<string, int> freq_table;
    countWords(freq_table);

    Heap heap;

    initializeHeapWithKElements(heap, freq_table, sw, k);

    insertRemainingWordsInHeap(heap, freq_table, sw);

    vector<string> ans = getHeapElements(heap);

    showElementsInCorrectOrder(ans);

    // for (int i = ans.size() - 1; i >= 0; i--)
    //     cout << ans[i] << " " << freq_table[ans[i]] << endl;

    return 0;
}