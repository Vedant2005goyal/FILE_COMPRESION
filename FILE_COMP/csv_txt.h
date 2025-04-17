#pragma once//it tells the compiler to include the file only once even if there are multiple declarations
#include<bits/stdc++.h>
using namespace std;
vector<string> split(string csv, const char& delim){
    vector<string> tokenizer;
    string token;
    int start=0;
    for(int i=0;i<csv.length();i++){//.find() provides only first delim
        if(csv[i]==delim){
            token=csv.substr(start,abs(start-i));
            tokenizer.push_back(token);
            start=i+1;
        }
    }
    tokenizer.push_back(csv.substr(start));
    return tokenizer;
}
string combine(vector<string> wo_delim, string final=""){
    int i=0;
    while(i<wo_delim.size()){
            string temp;
            temp=wo_delim[i];
            final.append(temp);
            final.append(" ");
            i++;
        }
    return final;
}
//a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z 

