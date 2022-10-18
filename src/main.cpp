

#include "../include/converterJSON.h"
#include "../include/invertedIndex.h"
#include "../include/searchServer.h"
#include "gtest/gtest.h"
#define SEARCHENGINE
//#define USEMAIN

#if defined(SEARCHENGINE)

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto converter = new ConverterJSON();

    return RUN_ALL_TESTS();

}

#elif defined(USEMAIN)

int main() {


    std::string command = "read";
    std::vector<std::vector<Entry>> expected;
    auto converter = new ConverterJSON();
    //std::cin>>command;
    //converter->onlyWord(command);
    //std::cout<<command;
    InvertedIndex idx;
    idx.updateDocumentBase(converter->getTextDocuments());
    SearchServer srv(idx);




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
         auto searchResult = srv.search(converter->getRequests());
         for(auto relVec: searchResult){
             for(auto rIdx: relVec){
                 std::cout<<rIdx.doc_id<<" "<< rIdx.rank<<std::endl;
             }
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

#endif