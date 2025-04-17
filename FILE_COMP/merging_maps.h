#pragma once
#include<bits/stdc++.h>
using namespace std;
map<char,int> final_map;
map<char,int> merging_map(vector<map<char,int>> mp){
    for (const auto& mp_chunk : mp)
    {
        for (const auto& [character,frequency] : mp_chunk)
        {
            final_map[character]+=frequency;
        }
        
    }
    return final_map;   
}
/* **** NOTE ***** */
/* There is also an stl way to merge two maps by merge() 
    but it merges only when there are no same keys in two different maps */