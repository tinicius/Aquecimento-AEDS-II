#include <stdlib.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "Hash.hpp"
#include "Heap.hpp"

using namespace std;

#define K 20

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

void loadStopWords(Hash& stopWordsTable) {
    ifstream file("./dataset/stopwords.data");

    if (!file.is_open()) {
        cerr << "Erro ao abrir um dos arquivos de entrada!" << std::endl;
        exit(1);
    }

    string line;

    while (getline(file, line)) {
        stopWordsTable.insert(line);
    }

    file.close();
}

void readFile(string src, Hash& freqWordsTable) {
    ifstream file(src);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << src << "!" << endl;
        exit(1);
    }

    char aux;
    string word;

    int aa = 0;

    while (file) {
        file.get(aux);

        if (isValidChar(aux)) {
            word += tolower(aux);
        } else {
            if (aux == '-' || aux == '/' || aux == '_') continue;

            if (!word.empty() and isValidWord(word)) {
                aa++;
                cout << aa << endl;
                freqWordsTable.insert(word);
            };

            word = "";
        }
    }

    file.close();
}

void readAllFilesInDatasetFolder(Hash& freqWordsTable) {
    for (auto& p : filesystem::directory_iterator("./dataset")) {
        string path = p.path().string();

        if (path == "./dataset/stopwords.data") continue;

        readFile(path, freqWordsTable);
    }
}

void initializeHeapWithKElements(Heap& heap, Hash& freq_table, Hash& sw,
                                 int items) {
    int counter = 0;

    for (auto w : freq_table.entries) {
        if (counter == items) break;

        auto res = freq_table.at(w);

        heap.push(res);
        counter++;
    }
}

void insertRemainingWordsInHeap(Heap& heap, Hash& freq_table, Hash& sw) {
    for (auto w : freq_table.entries) {
        auto menor = heap.top();

        auto res = freq_table.at(w);

        if (res.second > menor.second) {
            heap.pop();
            heap.push(res);
        }
    }
}

void getHeapElements(Heap& heap, vector<string>& ans) {
    while (!heap.empty()) {
        auto top = heap.top();
        ans.push_back(top.first);
        heap.pop();
    }
}

void showElementsInCorrectOrder(vector<string>& ans) {
    cout << "Elementos em ordem crescente: \n";

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << "\n";
    }

    cout << endl;
}

int main() {
    Hash sw;
    loadStopWords(sw);

    Hash freq_table;
    readAllFilesInDatasetFolder(freq_table);

    Heap heap;

    initializeHeapWithKElements(heap, freq_table, sw, K);
    insertRemainingWordsInHeap(heap, freq_table, sw);

    heap.showHeapContainer();

    vector<string> ans;
    getHeapElements(heap, ans);

    showElementsInCorrectOrder(ans);

    return 0;
}