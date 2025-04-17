#pragma once
#include<bits/stdc++.h>
using namespace std;
class node{
    public:
    int data;
    char ch;
    node*left;
    node*right;
    node(int data,char ch){
        this->ch=ch;
        this->data=data;
        left=NULL;
        right=NULL;
    }
};
vector<node*> frequency(string str){
    map<char,int> mp;
    int i=0;
    while(i<str.length()){
        char c=str[i];
        mp[c]++;
        i++;
    }
    vector<node*> ele;
    map<char, int>::iterator it = mp.begin();
    while(it!=mp.end()){
        int element1=it->second;
        int element2=it->first;
        node* temp=new node(element1,element2);
        ele.push_back(temp);
        it++;
    }
    return ele;
}