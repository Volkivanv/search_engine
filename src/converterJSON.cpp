//
// Created by Ivan on 02.09.2022.
//




#include "converterJSON.h"

class ConfigFileMissingException: public std::exception{
    [[nodiscard]]
    const char* what() const noexcept override{
        return "Config file is missing";
    }
};
class ConfigMissingException: public std::exception{
    [[nodiscard]]
    const char* what() const noexcept override{
        return "Config file is empty";
    }
};

class FileMissingException: public std::exception{
    [[nodiscard]]
    const char* what() const noexcept override{
        return "File is missing";
    }
};

class RequestsFileMissingException: public std::exception{
    [[nodiscard]]
    const char* what() const noexcept override{
        return "Requests file is missing";
    }
};

class RequestMissingException: public std::exception{
    [[nodiscard]]
    const char* what() const noexcept override{
        return "Request file is empty";
    }
};


ConverterJSON::ConverterJSON() {
    try {
        readConfig("config.json");
        readRequests("requests.json");
    }
    catch (const std::exception &x) {
        std::cerr << "Caught exception: " << x.what() << std::endl;
    }
}

nlohmann::json ConverterJSON::readConfig(const std::string& url) {
    std::ifstream rFile(url);



    if(rFile) {
        rFile >> config;
        if(config["config"].empty()){
            throw ConfigMissingException();
        }else{
            configSuit = true;
            std::cout<<config["config"]["name"]<<std::endl;
            std::cout<<config["config"]["version"]<<std::endl;
            std::stringstream version;
            version << VERSION_CMAKE_PROJECT;
            if(version.str() != config["config"]["version"])
                std::cerr << "config.json has incorrect file version" << std::endl;

            std::cout<<GetResponsesLimit()<<std::endl;
            for (auto it = config["files"].begin(); it != config["files"].end(); ++it){
                try {
                    if(checkFile(it.value())){
                        std::cout<<it.value()<<" found"<<std::endl;
                        texts.push_back(readTextFile(it.value()));
                    }
                }
                catch (const std::exception &x) {
                    std::cerr << "Caught exception: " << it.value()<<" "<< x.what() << std::endl;
                    texts.emplace_back("");
                }
            }
        }



    }else{
        throw ConfigFileMissingException();

    }
    rFile.close();
    return config;
}

void ConverterJSON::readRequests(const std::string& url) {
    std::ifstream rFile(url);



    if(rFile) {
        rFile >> requestsJson;
        if(requestsJson["requests"].empty()){
            throw RequestMissingException();
        }

    }else{
        throw RequestsFileMissingException();

    }
    rFile.close();

}

bool ConverterJSON::checkFile(const std::string& path) {
    std::ifstream textFile(path);
    if(!textFile)throw FileMissingException();
    return textFile.is_open();
}

int ConverterJSON::GetResponsesLimit() const{
    return config["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::getRequests(){
    std::vector<std::string> requests;
    int requestNum = 0;

    for (auto it = requestsJson["requests"].begin(); it != requestsJson["requests"].end(); ++it){
        std::string requestRaw = it.value();
        onlyWord(requestRaw);
        requests.push_back(requestRaw);
        requestNum++;
        if(requestNum > maxRequestNum) break;
    }
    return requests;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>>& inRelevance) {
    int i = 0;
    for(const auto& reqSearch: inRelevance){
        i++;
        bool searchResult = !reqSearch.empty();
        nlohmann::json resultPair;
        resultPair["result"] = searchResult;

        if(!searchResult) {
            answers["answers"][makeReqName(i)] = resultPair;
        }else if(searchResult) {
            if(reqSearch.size() == 1) {
                nlohmann::json relevancePair;
                relevancePair["docid"] = reqSearch[0].doc_id;
                relevancePair["rank"] = std::round(reqSearch[0].rank * 1000)/1000;
                answers["answers"][makeReqName(i)] = {resultPair, relevancePair};

            } else {
                nlohmann::json relevanceList;
                for (auto relevance: reqSearch) {

                    nlohmann::json relevancePair;
                    relevancePair["docid"] = relevance.doc_id;
                    relevancePair["rank"] = std::round(relevance.rank * 1000)/1000 ;

                    relevanceList.push_back(relevancePair);


                }

                nlohmann::json requestAnswerPair;
                requestAnswerPair["relevance"] = relevanceList;
                answers["answers"][makeReqName(i)] = {resultPair,requestAnswerPair};

            }
        }
    }



    std::ofstream file("answers.json");
    if(file) {
        file << answers.dump(4);
        std::cout <<"answers.json is written"<< std::endl;

    } else {
        std::cerr<<"file answers.json is not opened";
    }
    file.close();
}

std::vector<std::string> ConverterJSON::getTextDocuments() const {

    return texts;
}

std::string ConverterJSON::readTextFile(const std::string& url) {
    std::ifstream notebook;
    std::string answer;
    notebook.open(url);
    if(notebook) {
        int n = 0;

        while ((!notebook.eof()) && (n < 1000)) {
            std::string wordFind;
            notebook >> wordFind;
            onlyWord(wordFind);
            answer+=wordFind+" ";
            n++;
        }
    } else {
        std::cerr << "File is not found!"<< std::endl;
    }
    notebook.close();
    return answer;
}



bool ConverterJSON::getConfigSuit() const{
    return configSuit;
}

std::string makeReqName(int i) {
    std::string s = std::to_string(i+1000);
    s = "request"+s.erase(0,1);
    return s;
}

void ConverterJSON::onlyWord(std::string &word) {


    for (int i = word.length() - 1; i >= 0; i--) {

        char c = word[i];
        if (isalpha(c) && !islower(c)) word[i] = tolower(c);

        if (!(std::isalnum(c) || (c == '-') || std::isspace(c))) {
            word.erase(i, 1);
        }
    }
}




