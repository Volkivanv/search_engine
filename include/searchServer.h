//
// Created by Ivan on 14.10.2022.
//


#pragma once
#include "invertedIndex.h"



class SearchServer {
public:

    explicit SearchServer(InvertedIndex& idx) : index(idx){ };

public:
    [[nodiscard]] std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queriesInput) const;
    void setMaxResponses(int inMaxResponses);
private:
    [[nodiscard]] std::vector<RelativeIndex> searchSingle(const std::string& request) const;

private:
    InvertedIndex& index;
    std::vector<std::vector<RelativeIndex>> relativeIndexes;
    int maxResponses = 5;


};