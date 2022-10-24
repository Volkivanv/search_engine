//
// Created by Ivan on 30.09.2022.
//

#include "invertedIndex.h"



void InvertedIndex::updateDocumentBase(std::vector<std::string> inputDocs) {
    docs = inputDocs;
    for(std::string text: docs){


        std::stringstream textStream;

        textStream<<text;
        std::vector<std::string> words;
        while(!textStream.eof()){

            std::string buffer;
            textStream >> buffer;
            words.push_back(buffer);

        }
        docsVectors.push_back(words);
    }


}

std::vector<Entry> InvertedIndex::getWordCount(const std::string &word) {
    std::vector<Entry> gWC;
    int i = 0;
    std::vector<std::thread> threadVec;
    for(std::vector<std::string> text: docsVectors){

        threadVec.push_back(std::thread([&gWC, text, word, i, this]{
           Entry oneTextEntry;
            oneTextEntry.doc_id = i;
            oneTextEntry.count = std::count(text.begin(), text.end(), word);
            freqDictionaryMutex.lock();
            if(oneTextEntry.count > 0){
                gWC.push_back(oneTextEntry);
            }
            freqDictionaryMutex.unlock();
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


bool InvertedIndex::compare( Entry a, Entry b){
    return(a.doc_id<b.doc_id);
}



std::map<std::string, std::vector<Entry>> InvertedIndex::getFreqDictionary(const std::string &request) {
    std::map<std::string, std::vector<Entry>> freqDict;
    std::stringstream textStream;
    textStream << request;
    while (!textStream.eof()) {
        std::string buffer;
        textStream >> buffer; //May be optimized
        freqDict.insert(std::make_pair(buffer, getWordCount(buffer)));
    }
    return freqDict;
}

