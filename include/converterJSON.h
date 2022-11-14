//
// Created by Ivan on 02.09.2022.
//
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include "nlohmann/json.hpp"

std::string makeReqName(int i);


struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};


class ConverterJSON {
private:
    nlohmann::json config;
    nlohmann::json requestsJson;
    nlohmann::json answers;
    std::vector<std::string> texts;
    bool configSuit = false;
    const std::string appName = "MySearchEngine";

  //  std::vector<std::pair<int, float>> relevance;


public:
  //  ConverterJSON() = default;
    ConverterJSON();

    nlohmann::json readConfig(const std::string& url);

    void writeConfig(const std::string& url);
    static void writeRequests(const std::string& url);


/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    std::vector<std::string> getTextDocuments();
/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();
/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    std::vector<std::string> getRequests();
/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(const std::vector<std::vector<RelativeIndex>>&
                    answers);
    bool getConfigSuit();
private:
    static bool checkFile(const std::string& path);
    void readRequests(const std::string& url);
    static std::string readTextFile(std::string url);
    static void onlyWord(std::string & word);

};