//
// Created by Ivan on 30.09.2022.
//

#include "invertedIndex.h"


void InvertedIndex::updateDocumentBase(std::vector<std::string> inputDocs) {
    docs = std::move(inputDocs);
    for(std::string& text: docs){


        std::stringstream textStream;

        textStream<<text;
        std::vector<std::string> words;
        int numWordInRequest = 0;
        while(!textStream.eof() && numWordInRequest < maxWordsInRequest){

            std::string buffer;
            textStream >> buffer;
            onlyWord(buffer);
            words.push_back(buffer);
            numWordInRequest++;
        }
        docsVectors.push_back(words);
    }


}

std::vector<Entry> InvertedIndex::getWordCount(const std::string &word) {
    std::vector<Entry> gWC;
    int processNumberLimit = 4;
    int processNumber = 0;
    int i = 0;
    std::vector<std::thread> threadVec;
    for(const std::vector<std::string>& text: docsVectors){
        threadVec.emplace_back([&gWC, text, word, i, &processNumber, processNumberLimit, this]{
            if (processNumber > processNumberLimit) {
                std::unique_lock<std::mutex> lck(freqDictionaryMutex);
                while (processNumber > processNumberLimit) {
                condition.wait(lck);
                }
            }
            processNumber++;
           Entry oneTextEntry{};
            oneTextEntry.doc_id = i;
            oneTextEntry.count = std::count(text.begin(), text.end(), word);

            if(oneTextEntry.count > 0){
                gWC.push_back(oneTextEntry);
            }

            processNumber--;
            condition.notify_all();
        });
        i++;

    }
    for(std::thread & th: threadVec){
        th.join();
    }



    std::sort(gWC.begin(), gWC.end());

    return gWC;
}

std::map<std::string, std::vector<Entry>> InvertedIndex::getFreqDictionary(const std::string &request) {
    std::map<std::string, std::vector<Entry>> freqDict;
    std::stringstream textStream;
    textStream << request;
    while (!textStream.eof()) {
        std::string buffer;
        textStream >> buffer;
        freqDict.insert(std::make_pair(buffer, getWordCount(buffer)));
    }
    return freqDict;
}

void InvertedIndex::onlyWord(std::string &word) {


    for (int i = word.length() - 1; i >= 0; i--) {

        char c = word[i];
        if (isalpha(c) && !islower(c)) word[i] = tolower(c);

        if (!(std::isalnum(c) || (c == '-') || std::isspace(c))) {
            word.erase(i, 1);
        }
    }
}