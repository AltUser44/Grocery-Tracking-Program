/*
 * GroceryTracker implementation
 *
 * Uses a map<string,size_t> to count frequencies.
 * Items are normalized to lowercase when counted so searches are case-insensitive.
 */

#include "GroceryTracker.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

GroceryTracker::GroceryTracker() = default;

static string trim(const string& s) {
    size_t i = 0, j = s.size();
    while (i < j && isspace((unsigned char)s[i])) ++i;
    while (j > i && isspace((unsigned char)s[j - 1])) --j;
    return s.substr(i, j - i);
}

string GroceryTracker::toLowerCopy(const std::string& s) {
    string r = s;
    std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return std::tolower(c); });
    return r;
}

bool GroceryTracker::loadFromFile(const std::string& filename) {
    freqMap.clear();
    ifstream in(filename);
    if (!in) return false;
    string item;
    while (in >> item) {
        string key = toLowerCopy(trim(item));
        if (key.empty()) continue;
        ++freqMap[key];
    }
    in.close();
    return true;
}

bool GroceryTracker::writeBackup(const std::string& filename) const {
    ofstream out(filename);
    if (!out) return false;
    for (const auto& p : freqMap) {
        out << p.first << ' ' << p.second << '\n';
    }
    out.close();
    return true;
}

size_t GroceryTracker::getFrequency(const std::string& item) const {
    string key = toLowerCopy(item);
    auto it = freqMap.find(key);
    if (it == freqMap.end()) return 0;
    return it->second;
}

void GroceryTracker::printFrequencies() const {
    if (freqMap.empty()) {
        cout << "No items loaded.\n";
        return;
    }
    cout << "\nItem Frequency List\n";
    cout << "-------------------\n";
    for (const auto& p : freqMap) {
        cout << setw(15) << left << p.first << " : " << p.second << '\n';
    }
}

void GroceryTracker::printHistogram() const {
    if (freqMap.empty()) {
        cout << "No items loaded.\n";
        return;
    }
    cout << "\nHistogram\n";
    cout << "---------\n";
    for (const auto& p : freqMap) {
        cout << setw(15) << left << p.first << " ";
        size_t cnt = p.second;
        for (size_t i = 0; i < cnt; ++i) {
            cout << '*';
        }
        cout << '\n';
    }
}
