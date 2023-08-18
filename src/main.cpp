#include <stdlib.h>
#include <time.h>

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

void loadStopWords(unordered_map<string, int>& stopWordsTable) {
    ifstream file("./dataset/stopwords.data");

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

void readFile(string src, unordered_map<string, int>& freqWordsTable) {
    ifstream file(src);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << src << "!" << endl;
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

void readAllFilesInDatasetFolder(unordered_map<string, int>& freqWordsTable) {
    for (auto& p : filesystem::directory_iterator("./dataset")) {
        string path = p.path().string();

        if (path == "./dataset/stopwords.data") continue;

        readFile(path, freqWordsTable);
    }
}

void readFile(string src, Hash& freqWordsTable) {
    ifstream file(src);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << src << "!" << endl;
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

void insertElementsOnHeap(Heap& heap, unordered_map<string, int>& freq_table,
                          unordered_map<string, int>& stopWordsMap) {
    int counter = 0;

    for (auto w : freq_table) {
        if (stopWordsMap[w.first] > 0) continue;

        if (counter < K) {
            heap.push(w);
            counter++;
            continue;
        }

        auto menor = heap.top();

        if (w.second > menor.second) {
            heap.pop();
            heap.push(w);
            counter++;
        }
    }
}

void insertElementsOnHeap(Heap& heap, Hash& freq_table, Hash& stopWordsMap) {
    int counter = 0;

    for (string w : freq_table.keys) {
        if (stopWordsMap.at(w).second > 0) continue;

        pair<string, int> res = freq_table.at(w);

        if (counter < K) {
            // cout << res.first << " " << res.second << endl;
            heap.push(res);
            counter++;
            continue;
        }

        auto menor = heap.top();

        if (res.second > menor.second) {
            heap.pop();
            heap.push(res);
            counter++;
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

    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] << "\t";
    }

    cout << endl;
}

int main() {
    // unordered_map implemantion

    clock_t startExe, endExe;
    double execution_time;
    startExe = clock();

    unordered_map<string, int> sw;
    loadStopWords(sw);

    unordered_map<string, int> freq_table;
    readAllFilesInDatasetFolder(freq_table);

    Heap heap;
    insertElementsOnHeap(heap, freq_table, sw);

    heap.showHeapArray();

    //

    endExe = clock();
    execution_time = ((double)(endExe - startExe)) / CLOCKS_PER_SEC;

    printf("Time taken to execute in seconds : %f\n", execution_time);

    // vector<string> ans;
    // getHeapElements(heap, ans);

    // cout << "Elementos em ordem crescente: \n";

    // for (size_t i = 0; i < ans.size(); i++) {
    //     cout << ans[i] << " " << freq_table[ans[i]] << endl;
    // }

    // cout << endl;

    // Hash Middle square

    startExe = clock();

    Hash stopWordsHash;
    loadStopWords(stopWordsHash);

    Hash wordsFreq;
    readAllFilesInDatasetFolder(wordsFreq);

    Heap h;
    insertElementsOnHeap(h, wordsFreq, stopWordsHash);

    h.showHeapArray();

    //

    endExe = clock();
    execution_time = ((double)(endExe - startExe)) / CLOCKS_PER_SEC;

    printf("Time taken to execute in seconds : %f\n", execution_time);

    return 0;
}