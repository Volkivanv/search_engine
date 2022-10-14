

#include "../include/converterJSON.h"
#include "../include/invertedIndex.h"
#include "gtest/gtest.h"
#define SEARCHENGINE
//#define USEMAIN

#if defined(SEARCHENGINE)

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

#elif

int main() {


    std::string command = "read";
    std::vector<std::vector<Entry>> expected;
    auto converter = new ConverterJSON();
    //std::cin>>command;
    //converter->onlyWord(command);
    //std::cout<<command;
    InvertedIndex idx;
  //  idx.updateDocumentBase(converter->getTextDocuments());
    const std::vector<std::string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    idx.updateDocumentBase(docs);
    const std::vector<std::string> requests = {"london", "the"};

    for(std::string request: requests){
        std::stringstream requestStream;
        requestStream<<request;
        std::cout<<request;
        while(!requestStream.eof()) {
            std::string word;
            requestStream>>word;
            std::cout<<word;
            std::vector<Entry> wordCount = idx.getWordCount(word);
        }
    }


/*
    while(true) {
        std::cout<<"input command: write config, read or exit, "
                   "WR (write requests), SHR(show requests)"<<std::endl;
        std::cin.clear();
        std::cin>>command;
        if(command == "write") {
            converter -> writeConfig("config.json");
        } else if(command == "read") {

            //выяснить почему файлы не читаются
            for(std::string x:converter->getTextDocuments()){
                std::cout<<x<<std::endl;
            }
        } else if(command == "WR") {
            converter->writeRequests("requests.json");
        } else if(command == "SHR"){
            for(std::string s: converter->getRequests()){
                std::cout<<s<<std::endl;
            }
        } else if(command == "exit") {
            break;
        } else {
            std::cout<<"Unknown command"<<std::endl;
        }
        command = "exit";
    }

   delete converter;
    return 0;
}
 */
#endif