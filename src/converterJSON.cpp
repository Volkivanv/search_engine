//
// Created by Ivan on 02.09.2022.
//
#include <cmath>

#include "../include/converterJSON.h"

class ConfigFileMissingException: public std::exception{
    // [[nodiscard]]
    const char* what() const noexcept override{
        return "Config file is missing";
    }
};
class ConfigMissingException: public std::exception{
   // [[nodiscard]]
    const char* what() const noexcept override{
        return "Config file is empty";
    }
};

class FileMissingException: public std::exception{
   // [[nodiscard]]
    const char* what() const noexcept override{
        return "File is missing";
    }
};

class RequestsFileMissingException: public std::exception{
   // [[nodiscard]]
    const char* what() const noexcept override{
        return "Requests file is missing";
    }
};

class RequestMissingException: public std::exception{
   // [[nodiscard]]
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
            std::cout<<config["config"]["name"]<<std::endl;
            std::cout<<config["config"]["version"]<<std::endl;
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
        };


        rFile.close();
    }else{
        throw ConfigFileMissingException();

    }

    return config;
}

void ConverterJSON::readRequests(const std::string& url) {
    std::ifstream rFile(url);



    if(rFile) {
        rFile >> requestsJson;
        if(requestsJson["requests"].empty()){
            throw RequestMissingException();
        };

        rFile.close();
    }else{
        throw RequestsFileMissingException();

    }

}

void ConverterJSON::writeConfig(const std::string& url) {

    nlohmann::json config;
    config["config"]["name"] = "MySearchEngine";
    config["config"]["version"] = "0.1";
    config["config"]["max_responses"] = 5;
    config["files"] = {"resources/file001.txt",
                       "resources/file002.txt",
                       "resources/file003.txt",
                       "resources/file004.txt"};


    std::ofstream file(url);
    if(file) {
        file << config;
    } else {
        std::cerr<<"file is not opened";
    }
    file.close();


}
void ConverterJSON::writeRequests(const std::string& url) {
    nlohmann::json requests;

    std::vector<std::string> req = {"nkdghd oiop bnm",
                                    "London asdfsa oa df is capital of Great Britain",
                                    "Studying at the university is so much fun because you meet a lot of unique people",
                                    "After that you register for the compulsory and optional subjects",
                                    "Only the best graduates receive jobs at international companies so take your time and study hard"};

    for(std::string &r:req){
        onlyWord(r);
        requests["requests"].push_back(r);
    }

    std::ofstream file(url);
    if(file) {
        file << requests;
    } else {
        std::cerr<<"file is not opened";
    }
    file.close();

}
bool ConverterJSON::checkFile(const std::string& path) {
    std::ifstream textFile(path);
    if(textFile){
        textFile.close();
        return true;
    } else {
        throw FileMissingException();
        return false;

    }


}

int ConverterJSON::GetResponsesLimit() {
    return config["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::getRequests() {
    std::vector<std::string> requests;

    for (auto it = requestsJson["requests"].begin(); it != requestsJson["requests"].end(); ++it){
        requests.push_back(it.value());
    }
    return requests;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>>& inRelevance) {
    int i = 0;
    for(const auto& reqSearch: inRelevance){
        i++;
        bool searchResult = !reqSearch.empty();

        answers["answers"][makeReqName(i)]["result"] = searchResult;
        if(searchResult) {
            nlohmann::json relevanceList;
            for (auto relevance: reqSearch) {

                nlohmann::json relevancePair;
                relevancePair["docid"] = relevance.doc_id;
                relevancePair["rank"] = std::round(relevance.rank * 1000) / 1000;
                relevanceList.push_back(relevancePair);

            }

            answers["answers"][makeReqName(i)]["relevance"] = relevanceList;
        }
    }

    std::ofstream file("answers.json");
    if(file) {
        file << answers;
        std::cout<<"answers.json is written"<<std::endl;

    } else {
        std::cerr<<"file answers.json is not opened";
    }
    file.close();
}

std::vector<std::string> ConverterJSON::getTextDocuments() {

    return texts;
}

std::string ConverterJSON::readTextFile(std::string url) {
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
        notebook.close();
    } else {
        std::cerr << "File is not found!"<< std::endl;
    }
    return answer;
}

void ConverterJSON::onlyWord(std::string &word) {



    for(int i = word.length()-1; i >= 0; i-- ){
        char c = word[i];
        if(!(((c >= 'a')&&(c <= 'z'))||((c >= 'A')&&(c <='Z'))||((c >= '0')&&(c <='9'))||(c == '-')||(c == ' ')))
        {
            word.erase(i,1);
        }
    }

}

std::string makeReqName(int i) {
    std::string s = std::to_string(i+1000);
    s = "request"+s.erase(0,1);
    return s;
}






