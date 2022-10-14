//
// Created by Ivan on 30.09.2022.
//

#include "invertedIndex.h"



void InvertedIndex::updateDocumentBase(std::vector<std::string> input_docs) {
    docs = input_docs;
    for(std::string text: docs){


        std::stringstream textStream;

        textStream<<text;
        std::vector<std::string> words;
        while(!textStream.eof()){

            std::string buffer;
            textStream>>buffer;
            words.push_back(buffer);

        }
        docsVectors.push_back(words);
    }
  //  std::string word = "you";
  //  freq_dictionary.insert(std::make_pair(word, getWordCount(word)));

}
/*
std::vector<Entry> InvertedIndex::getWordCount(const std::string &word) {
    std::vector<Entry> gWC;
    int i = 0;
    std::vector<std::thread> threadVec;
    for(std::string text:docs){

        threadVec.push_back(std::thread([&gWC, text, word, i, this]{
            Entry oneTextEntry;
            oneTextEntry.doc_id = i;
            oneTextEntry.count = getOneTextCount(text, word);
            freq_dictionary_mutex.lock();
            if(oneTextEntry.count > 0){
                gWC.push_back(oneTextEntry);
            }
            freq_dictionary_mutex.unlock();
        }));
        i++;
    }
    for(std::thread & th: threadVec){
        th.join();
    }



    std::sort(gWC.begin(), gWC.end(),compare);

    for(Entry g:gWC){
        std::cout<<"{"<<g.doc_id<<", "<<g.count<<"}"<<", ";
    }
    std::cout<<std::endl;

    return gWC;
}
*/
std::vector<Entry> InvertedIndex::getWordCount(const std::string &word) {
    std::vector<Entry> gWC;
    int i = 0;
    std::vector<std::thread> threadVec;
    for(std::vector<std::string> text: docsVectors){

        threadVec.push_back(std::thread([&gWC, text, word, i, this]{
            Entry oneTextEntry;
            oneTextEntry.doc_id = i;
            oneTextEntry.count = std::count(text.begin(), text.end(), word);
            freq_dictionary_mutex.lock();
            if(oneTextEntry.count > 0){
                gWC.push_back(oneTextEntry);
            }
            freq_dictionary_mutex.unlock();
        }));
        i++;
    }
    for(std::thread & th: threadVec){
        th.join();
    }



    std::sort(gWC.begin(), gWC.end(),compare);
/*
    for(Entry g:gWC){
        std::cout<<"{"<<g.doc_id<<", "<<g.count<<"}"<<", ";
    }
    std::cout<<std::endl;
*/
    return gWC;
}

int InvertedIndex::getOneTextCount(const std::string& text, const std::string& word) {
    int k = 0;

        std::cout<<text<<std::endl;

        std::cout<<"check: "<< word<<std::endl;
        std::stringstream textStream;

        textStream<<text;

        while(!textStream.eof()){
            std::string buffer;
            textStream>>buffer; //May be optimized
            if(buffer == word){
                k++;
            }
        }

  //  k = std::count(text.begin(), text.end(), 'c');

    return k;
}

bool InvertedIndex::compare( Entry a, Entry b){
    return(a.doc_id<b.doc_id);
};
