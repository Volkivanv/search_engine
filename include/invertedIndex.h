//
// Created by Ivan on 30.09.2022.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H


#endif //SEARCH_ENGINE_INVERTEDINDEX_H


#pragma once
#include "converterJSON.h"
#include <sstream>
#include <thread>
#include <mutex>



struct Entry {
    size_t doc_id, count;
// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
    bool operator<(const Entry &other) const
    {
        return (doc_id < other.doc_id &&
               count < other.count);
    }
};
class InvertedIndex {
public:
    InvertedIndex() = default;
/**
* Обновить или заполнить базу документов, по которой будем совершать
поиск*
@param texts_input содержимое документов
*/
    void updateDocumentBase(std::vector<std::string> inputDocs);
/**
 *
 * @return
 */
    /* Метод определяет количество вхождений слова word в загруженной базе
            документов
    * @param word слово, частоту вхождений которого необходимо определить
    * @return возвращает подготовленный список с частотой слов
    */
    std::vector<Entry> getWordCount(const std::string& word);

    std::map<std::string, std::vector<Entry>> getFreqDictionary(const std::string& request);

private:

  //  static bool compare( Entry a, Entry b);
private:
    std::vector<std::string> docs; // список содержимого документов
    std::vector<std::vector<std::string>> docsVectors;
    std::map<std::string, std::vector<Entry>> freqDictionary; // частотный словарь


    std::mutex freqDictionaryMutex;

};
