#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

// Function to extract words from a file
set<string> extractWordsFromFile(const string &filename) {
    ifstream file(filename);
    set<string> words;
    string word;

    while (file >> word) {
        // Remove non-alphabetic characters and convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());
        if (!word.empty()) {
            words.insert(word);
        }
    }
    return words;
}

// Function to calculate Jaccard Similarity between two sets of words
double calculateJaccardSimilarity(const set<string> &set1, const set<string> &set2) {
    set<string> intersection;
    set<string> union_set;

    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersection, intersection.begin()));
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(union_set, union_set.begin()));

    return (double)intersection.size() / union_set.size();
}

int main() {
    string book1File, book2File;
    cout << "Enter the name of the first book file: ";
    cin >> book1File;
    cout << "Enter the name of the second book file: ";
    cin >> book2File;

    // Extract words from both books
    set<string> book1Words = extractWordsFromFile(book1File);
    set<string> book2Words = extractWordsFromFile(book2File);

    // Calculate and display the similarity
    double similarity = calculateJaccardSimilarity(book1Words, book2Words);
    cout << "The Jaccard Similarity between the two books is: " << similarity << endl;

    return 0;
}