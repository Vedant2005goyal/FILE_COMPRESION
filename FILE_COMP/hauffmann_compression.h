#pragma once
#include<bits/stdc++.h>
using namespace std;
string str;
void encoded(vector<pair<char,string> > &ans, node*& top){/* '*&' because mai pointer ko callby refernce kar rha hu */
    if(top->right ==NULL && top->left ==NULL){  
        ans.push_back(make_pair(top->ch,str));
        return;
        }
    str.push_back('0');
    encoded(ans,top->left);
    str.pop_back();
    str.push_back('1');
    encoded(ans,top->right);
    str.pop_back();
}
struct CompareNode {
    bool operator()(node* a, node* b) {
        return a->data > b->data;
    }
};

node* huffmann_tree(vector<node*>ele){
    priority_queue<node*,vector<node*>,CompareNode> pq(ele.begin(),ele.end());
    while(pq.size()>1){
        node *x=pq.top();//pehla min element ki node
        int ele1=x->data;//pehle min element ki node ka data
        pq.pop();
        node *y=pq.top();//dusra min element ki node
        int ele2=y->data;//dusra min element ki node ka data
        pq.pop();
        int z=ele1+ele2;//addition of frequency of x and y
        node *ptr=new node(z,'N');
        ptr->left=x;
        ptr->right=y;
        pq.push(ptr);
    }
    node *top=pq.top();
    return top;
}