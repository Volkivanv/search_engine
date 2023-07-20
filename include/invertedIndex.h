//
// Created by Ivan on 30.09.2022.
//



#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <condition_variable>

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }

};

struct Entry {
    size_t doc_id, count;

    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
    bool operator<(const Entry &other) const
    {
        return (doc_id < other.doc_id);
    }
};
class InvertedIndex {
public:
    InvertedIndex() = default;

    void updateDocumentBase(std::vector<std::string> inputDocs);

    std::vector<Entry> getWordCount(const std::string& word);

    std::map<std::string, std::vector<Entry>> getFreqDictionary(const std::string& request);



private:
    std::vector<std::string> docs;
    std::vector<std::vector<std::string>> docsVectors;
    std::map<std::string, std::vector<Entry>> freqDictionary;

    int maxNumWordInRequest = 10;
    std::mutex freqDictionaryMutex;
    std::condition_variable condition;


};
