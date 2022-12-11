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

};