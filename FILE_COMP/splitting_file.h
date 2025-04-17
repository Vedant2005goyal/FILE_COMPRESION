#pragma once
#include<bits/stdc++.h>
#define no_of_chunks 8
using namespace std;
vector<string> chunks;
vector<string> split(ifstream &file){
    string file_content((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
    int size_of_chunk=file_content.size()/no_of_chunks;
    int start=0;
    for(int i=0; i<no_of_chunks; i++){
        string temp=file_content.substr(start,size_of_chunk);
        start=start+size_of_chunk+1;
        if(i==no_of_chunks-1)
            start=start+size_of_chunk;
        chunks.push_back(temp);
    }
    return chunks;
}