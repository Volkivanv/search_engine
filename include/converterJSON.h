//
// Created by Ivan on 02.09.2022.
//
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include "nlohmann/json.hpp"


class ConverterJSON {
private:
    nlohmann::json config;
    nlohmann::json requestsJson;
    nlohmann::json answers;
    std::vector<std::string> texts;

    std::vector<std::pair<int, float>> relevance;


public:
  //  ConverterJSON() = default;
    ConverterJSON();

    nlohmann::json readConfig(std::string url);

    void writeConfig(std::string url);
    void writeRequests(std::string url);


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
    void putAnswers(std::vector<std::vector<std::pair<int, float>>>
                    answers);
private:
    bool checkFile(std::string path);
    void readRequests(std::string url);
    static std::string readTextFile(std::string url);
    static void onlyWord(std::string & word);
};