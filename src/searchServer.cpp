//
// Created by Ivan on 14.10.2022.
//

#include "searchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queriesInput) {
    std::vector<std::vector<RelativeIndex>> searchIndex;
    for(std::string request: queriesInput){

    searchIndex.push_back(searchSingle(request));
    }
    return searchIndex;
}

std::vector<RelativeIndex> SearchServer::searchSingle(const std::string &request) {
    std::vector<RelativeIndex> relIdxes;
    std::map<size_t , size_t> relIdxMap;
    auto freqDict = index.getFreqDictionary(request);

    for(auto it = freqDict.begin();it!=freqDict.end();++it){
   //     std::cout<<it->first <<" ";
        for(auto p: it->second){
            auto ItMap = relIdxMap.find(p.doc_id);
            if(ItMap!=relIdxMap.end()){
                ItMap->second += p.count;
            } else {
                relIdxMap.insert(std::make_pair(p.doc_id,p.count));
            }

     //       std::cout<<"{"<<p.doc_id<<","<<p.count<<"}, ";

        }
    //    std::cout<<std::endl;

    }
    float max = 0;
    for(auto mPair: relIdxMap){
   //     std::cout<<mPair.first<<" "<<mPair.second<<std::endl;
        RelativeIndex rIdx;
        if(mPair.second > 0){
            if(mPair.second > max) max = mPair.second;
            rIdx.doc_id = mPair.first;
            rIdx.rank = mPair.second;
            relIdxes.push_back(rIdx);
        }

    }
    std::sort(relIdxes.begin(), relIdxes.end(),compare);


    for(auto& rIdx: relIdxes){
        rIdx.rank/=max;

    }

    // WRITE
    if(relIdxes.size() > maxResponses) relIdxes.resize(maxResponses);

    return relIdxes;
}

bool SearchServer::compare(RelativeIndex a, RelativeIndex b) {
    if( a.rank == b.rank) return a.doc_id < b.doc_id;
    else return (a.rank > b.rank);
}

void SearchServer::setMaxResponses(int inMaxResponses) {
    maxResponses = inMaxResponses;

}



