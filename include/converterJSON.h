//
// Created by Ivan on 02.09.2022.
//

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "nlohmann/json.hpp"
#include "invertedIndex.h"

std::string makeReqName(int i);





class ConverterJSON {
private:
    nlohmann::json config;
    nlohmann::json requestsJson;
    nlohmann::json answers;
    std::vector<std::string> texts;
    bool configSuit = false;
    const std::string appName = "MySearchEngine";

public:

    ConverterJSON();

    nlohmann::json readConfig(const std::string& url);

    [[nodiscard]] std::vector<std::string> getTextDocuments() const;

    [[nodiscard]] int GetResponsesLimit() const;

    std::vector<std::string> getRequests();

    void putAnswers(const std::vector<std::vector<RelativeIndex>>&
                    answers);
    [[nodiscard]] bool getConfigSuit() const;
private:
    static bool checkFile(const std::string& path);
    void readRequests(const std::string& url);
    static std::string readTextFile(const std::string& url);
    static void onlyWord(std::string & word);
    int maxRequestNum = 1000;


};