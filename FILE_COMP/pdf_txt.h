// there is no direct way to dit that's why i am using poppler api for this
#pragma once
#include<bits/stdc++.h>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include<memory>//it is used to include smart pointer
/*================================================================================================================
    It automatically manages the dynamically allocated resources on the heap. Smart pointers 
    are just wrappers around regular old pointers that help you prevent widespread bugs.
/================================================================================================================*/
using namespace std;
using namespace poppler;
void conversion(string pdf_path,ofstream &converted_pdf){
    unique_ptr<document> pdf(document::load_from_file(pdf_path));
    if (!pdf) {
        cerr << "Failed to load PDF: " << pdf_path << endl;
        return ;
    }
    int no_of_pages=pdf->pages();
    for (int i = 0; i < no_of_pages; ++i) {
        unique_ptr<page> current_page(pdf->create_page(i));
        if (!current_page) {
            cerr << "Failed to load page " << i << endl;
            continue;
        }
        auto utf8_text=current_page->text().to_utf8();
        string text(utf8_text.begin(),utf8_text.end());
        converted_pdf << text << endl;
    }
}

//================================================================================================================
/* ****NOTE****
    getline()works only with the stream like cin, ifstream
    but it won't work with unique_ptr and ._utf8 return vector<char> not a string
*/
//================================================================================================================