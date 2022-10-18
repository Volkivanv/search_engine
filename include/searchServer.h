//
// Created by Ivan on 14.10.2022.
//

#ifndef SEARCH_ENGINE_RELATIVEINDEX_H
#define SEARCH_ENGINE_RELATIVEINDEX_H

#endif //SEARCH_ENGINE_RELATIVEINDEX_H
//#pragma once
#include "invertedIndex.h"


class SearchServer {
public:
/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex& idx) : _index(idx){ };
/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
public:
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
    void setMaxResponses(int maxResp);
private:
    std::vector<RelativeIndex> searchSingle(const std::string& request);
    static bool compare( RelativeIndex a, RelativeIndex b);
private:
    InvertedIndex& _index;
    std::vector<std::vector<RelativeIndex>> relativeIndexes;
    int maxMaxResponses = 5;


};