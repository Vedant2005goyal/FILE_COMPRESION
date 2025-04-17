#pragma once
#include<bits/stdc++.h>
using namespace std;
vector<node*> element_creation(map<char,int> final_map){
    vector<node*> element;
    map<char, int>::iterator it = final_map.begin();
    while(it!=final_map.end()){
        int element1=it->second;
        int element2=it->first;
        node* temp=new node(element1,element2);
        element.push_back(temp);
        it++;
    }
    return element;
}
