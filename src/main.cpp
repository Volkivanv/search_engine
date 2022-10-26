

#include "../include/converterJSON.h"
#include "../include/invertedIndex.h"
#include "../include/searchServer.h"
#include "gtest/gtest.h"
//#define USETESTS
#define USEMAIN

#if defined(USETESTS)

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}

#elif defined(USEMAIN)

int main() {
    std::cout<<PROJECT_VERSION<<std::endl;


    std::string command;

    auto converter = new ConverterJSON();

    InvertedIndex idx;
    idx.updateDocumentBase(converter->getTextDocuments());
    SearchServer srv(idx);
    srv.setMaxResponses(converter->GetResponsesLimit());





    while(true) {
        std::cout<<"input command:  result (execute search engine and write answer.json), "
                   "exit for exit"<<std::endl;
        std::cin.clear();
        std::cin>>command;
      //  if(command == "write") {
      //      converter -> writeConfig("config.json");
       // } else
//       if(command == "read") {
//
//            for(const std::string& x:converter->getTextDocuments()){
//                std::cout<<x<<std::endl;
//            }
//        } else if(command == "WR") {
//            converter->writeRequests("requests.json");
//        } else
            if(command == "result"){
         auto searchResult = srv.search(converter->getRequests());
         int i=0;
         int sum = 0;
         for(const auto& relVec: searchResult){
             i++;
             std::cout<<makeReqName(i)<<" number of result: "<< relVec.size() << std::endl;
             sum+=relVec.size();
         }
         std::cout<<"Total of result "<< sum <<std::endl;
         converter->putAnswers(searchResult);
         std::cout<<"The job is done!"<<std::endl;
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