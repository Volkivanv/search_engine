//
// Created by Ivan on 14.10.2022.
//

#include "searchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queriesInput) const{
    std::vector<std::vector<RelativeIndex>> searchIndex;
    for(const std::string& request: queriesInput){

    searchIndex.push_back(searchSingle(request));
    }
    return searchIndex;
}

std::vector<RelativeIndex> SearchServer::searchSingle(const std::string &request) const{
    std::vector<RelativeIndex> relIdxes;
    std::map<size_t , size_t> relIdxMap;
    auto freqDict = index.getFreqDictionary(request);

    for(auto & it : freqDict){

        for(auto p: it.second){
            auto ItMap = relIdxMap.find(p.doc_id);
            if(ItMap!=relIdxMap.end()){
                ItMap->second += p.count;
            } else {
                relIdxMap.insert(std::make_pair(p.doc_id,p.count));
            }

        }

    }
    float max = 0;
    for(auto mPair: relIdxMap){

        RelativeIndex rIdx{};
        if(mPair.second > 0){
            if(float (mPair.second) > max) max = float(mPair.second);
            rIdx.doc_id = mPair.first;
            rIdx.rank = float(mPair.second);
            relIdxes.push_back(rIdx);
        }

    }
    std::sort(relIdxes.begin(), relIdxes.end(),[](RelativeIndex a, RelativeIndex b){
        if( a.rank == b.rank) return a.doc_id < b.doc_id;
        else return (a.rank > b.rank);
    });


    for(auto& rIdx: relIdxes){
        rIdx.rank/=max;

    }

    // WRITE
    if(relIdxes.size() > maxResponses) relIdxes.resize(maxResponses);

    return relIdxes;
}



void SearchServer::setMaxResponses(int inMaxResponses) {
    maxResponses = inMaxResponses;

}



