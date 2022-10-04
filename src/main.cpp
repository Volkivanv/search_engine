

#include "../include/converterJSON.h"
#include "../include/invertedIndex.h"
#include "gtest/gtest.h"

TEST(sample_test_case, sample_test){
    EXPECT_EQ(1,1);
}

void TestInvertedIndexFunctionality(
        const std::vector<std::string>& docs,
        const std::vector<std::string>& requests,
        const std::vector<std::vector<Entry>>& expected)
        {
std::vector<std::vector<Entry>> result;
InvertedIndex idx;
idx.updateDocumentBase(docs);
for(auto& request : requests) {
std::vector<Entry> word_count = idx.getWordCount(request);
result.push_back(word_count);
}
ASSERT_EQ(result, expected);
}
TEST(TestCaseInvertedIndex, TestBasic) {
    const std::vector<std::string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    const std::vector<std::string> requests = {"london", "the"};
    const std::vector<std::vector<Entry>> expected = {
            {
                    {0, 1}
            }, {
                {0, 1}, {1, 3}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const std::vector<std::string> requests = {"milk", "water", "cappuccino"};
    const std::vector<std::vector<Entry>> expected = {
            {
                    {0, 4}, {1, 1}, {2, 5}
            }, {
                    {0, 2}, {1, 2}, {2, 5}
            }, {
                    {3, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const std::vector<std::string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const std::vector<std::string> requests = {"m", "statement"};
    const std::vector<std::vector<Entry>> expected = {
            {
            }, {
                    {1, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}




int main() {


    std::string command = "read";
    std::vector<std::vector<Entry>> expected;
    auto converter = new ConverterJSON();
    //std::cin>>command;
    //converter->onlyWord(command);
    //std::cout<<command;
  /*  InvertedIndex idx;
    idx.updateDocumentBase(converter->getTextDocuments());

    for(std::string request: converter->getRequests()){
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
*/
   delete converter;
    return 0;
}
