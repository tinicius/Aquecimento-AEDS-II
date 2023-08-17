#include <stdlib.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
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

void loadStopWords(unordered_map<string, int>& stopWordsTable) {
    ifstream file("../dataset/DomCasmurro.txt");

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
    for (auto& p : filesystem::directory_iterator("../dataset")) {
        string path = p.path().string();

        if (path == "../dataset/stopwords.data") continue;

        readFile(path, freqWordsTable);
    }
}

void initializeHeapWithKElements(Heap& heap,
                                 unordered_map<string, int>& freq_table,
                                 unordered_map<string, int> sw, int items) {
    int counter = 0;

    for (auto w : freq_table) {
        if (counter == items) break;

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
        cout << ans[i] << "\t";
    }

    cout << endl;
}

int main() {
    Hash h;

    unordered_map<string, int> sw;
    loadStopWords(sw);

    set<size_t> colitions;

    // int t = 40;

    int col = 0;

    for (auto& ws : sw) {
        string w = ws.first;

        size_t aux = h.hash(w);

        // cout << aux << " ";

        if (colitions.find(aux) != colitions.end()) {
            // cout << "Colisao!\n";
            // cout << w << endl << endl;

            cout << aux << " ";
            col++;
        }

        colitions.insert(aux);
    }

    cout << endl;
    cout << col<< endl;

    return 0;

    unordered_map<string, int> freq_table;
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