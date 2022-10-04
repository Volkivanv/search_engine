//
// Created by Ivan on 30.09.2022.
//

#include "invertedIndex.h"


void InvertedIndex::updateDocumentBase(std::vector<std::string> input_docs) {
    docs = input_docs;
  //  std::string word = "you";
  //  freq_dictionary.insert(std::make_pair(word, getWordCount(word)));

}

std::vector<Entry> InvertedIndex::getWordCount(const std::string &word) {
    std::vector<Entry> gWC;
    int i = 0;
    for(std::string text:docs){
        std::stringstream textStream;
        Entry oneTextEntry;
        textStream<<text;
        int k = 0;
        while(!textStream.eof()){
            std::string buffer;
            textStream>>buffer; //May be optimized
            if(buffer == word){
                k++;
            }
        }
        oneTextEntry.doc_id = i;
        oneTextEntry.count = k;
        gWC.push_back(oneTextEntry);
        i++;


    }
    for(Entry g:gWC){
        std::cout<<g.doc_id<<" "<<g.count<<std::endl;
    }
    return gWC;
}
