#pragma once
#include<bits/stdc++.h>
#include<string>
using namespace std;
vector<map<char,int>> chunk_map(vector<string> chunks){
    // vector<map<char,int>> mp;
    // for(int i=0;i<chunks.size();i++){
    //     map<char,int> mpp;
    //     string temp=chunks[i];
    //     int j=0;
    //     while(j<temp.length()){
    //         char c=temp[j];
    //         mpp[c]++;
    //         j++;
    //     }
    //     mp.push_back(mpp);
    // }
    /* **** ANOTHER WAY **** */
    // for(const auto& chunk :chunks){
    //     map<char,int> mpp;
    //     for (auto c : chunk)
    //     {
    //         mpp[c]++;
    //     }
    //     mp.push_back(mpp);
    // }
    
    // Above two methods are for single thread
    vector<map<char,int>> mp(chunks.size());
    vector<thread> threads;
    //Lambda function
    auto count_freq = [](const string& chunk, map<char,int>& freq_map) {
    for (char c : chunk) {
        freq_map[c]++;
    }
    };

    for (int i = 0; i < chunks.size(); ++i) {
        threads.emplace_back(count_freq, ref(chunks[i]), ref(mp[i]));
    }

    for (auto& t : threads) {
        t.join();
    }
    return mp;
}
