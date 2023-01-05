
#include "converterJSON.h"
#include "invertedIndex.h"
#include "searchServer.h"
//#include "gtest/gtest.h"

int main() {

    std::string command;


    auto converter = new ConverterJSON();
    if (!converter->getConfigSuit()) {
        std::cout << "Config file error. Fix problem and try again!" << std::endl;
          return 0;
    }

    InvertedIndex idx;
    idx.updateDocumentBase(converter->getTextDocuments());
    SearchServer srv(idx);
    srv.setMaxResponses(converter->GetResponsesLimit());



    while (true) {
        std::cout << "If you want to execute search engine and write answer.json, please input \"result\"." << std::endl;
        std::cout << "If you want to exit, please input \"exit\"." << std::endl;
        std::cin.clear();
        std::cin >> command;

        if (command == "result") {
            auto searchResult = srv.search(converter->getRequests());
            int i = 0;
            int sum = 0;
            for (const auto &relVec: searchResult) {
                i++;
                std::cout << makeReqName(i) << " number of result: " << relVec.size() << std::endl;
                sum += relVec.size();
            }
            std::cout << "Total of result " << sum << std::endl;
            converter->putAnswers(searchResult);
            std::cout << "The job is done!" << std::endl;
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
        command = "exit";
    }

    delete converter;


    return 0;
}


