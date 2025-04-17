#include<iostream>
#include<fstream>// it provides tools for i/p and o/p operations
#include<string>
#include"csv_txt.h"
#include"pdf_txt.h"
#include"frequency_map.h"
#include"frequency_chunk_map.h"
#include"hauffmann_compression.h"
#include"splitting_file.h"
#include"merging_maps.h"
#include"element_creation.h"
using namespace std;
int main(){

    /*================================================================================================================
    ofstream is for creating and writing in files
    ifstream is for reading files
    fstream is combination of ofstream and ifstream
    */
    // ofstream new_file("filename.txt");//new_file is variable or object of the ofstream class of type ofstream
    // new_file<<"I am going to create a txt file compressor using hauffmann algo";
    // new_file.close();

    //since the file is created its time for reading the file for this i will store it in string
    // string text;
    // ifstream file("filename.txt");
    // while (getline(file,text))
    // {
    //     cout<<text;
    // }
    /*NOTE:-getline is basically for reading the input if getline(cin,string)then it will read input 
            from user and put it onto a string and here it reads from the .txt file and put it onto string text*/
    // file.close();
    //================================================================================================================
    
    //opening a csv file and reading it 
    string csv_filepath="/Users/vedantgoyal/Desktop/CODING/PYTHON/customers.csv";
    ifstream csv(csv_filepath);
    if (!csv.is_open())
    {
        cout<<"Unable to open the file"<<csv_filepath<<endl;
        return 1;
    }

    char delim=',';

    //conversion of .csv to .txt file:
    ofstream converted_csv("csv_txt.txt");
    string line;
    while(getline(csv,line)){
        vector<string> temp=split(line,delim);
        string final=combine(temp);
        converted_csv<<final<<endl;
    }
    csv.close();
    converted_csv.close();

    //====================================================================================================================
    // csv.clear() it clears the EOF flag
    // csv.seekg(0,ios::beg) it again make the pointer to point at beginning
    //====================================================================================================================

    // now i will convert pdf to txt
    ofstream converted_pdf("pdf_txt.txt");
    string pdf_filepath="/Users/vedantgoyal/Documents/ECED.pdf";
    conversion(pdf_filepath,converted_pdf);
    converted_pdf.close();   

    // now i will pass these .txt files to hauffmann and make them .huff 
    auto start_single = chrono::high_resolution_clock::now();
    ofstream compressed_csv("compressed_csv.huff", ios::binary);
    string csv_txt_filepath="/Users/vedantgoyal/Desktop/CODING/FILE_COMP/csv_txt.txt";
    ifstream csv_txt(csv_txt_filepath);
    if (!csv_txt.is_open())
    {
        cout << "Unable to open the file" << csv_filepath << endl;
        return 1;
    }
    string csv_content((istreambuf_iterator<char>(csv_txt)),istreambuf_iterator<char>());
    vector<node*> ele=frequency(csv_content);
    node* top=huffmann_tree(ele);
    vector<pair<char,string> > ans;
    encoded(ans,top);
    map<char, string> huffman_map;
    for (auto& p : ans) {
       huffman_map[p.first] = p.second;
    }

    //Conversion of 0 and 1 in bits
    unsigned char buffer = 0;
    int bit_count = 0;

    for (char ch : csv_content) {
        string code = huffman_map[ch];
        for (char bit : code) {
            buffer <<= 1;
            if (bit == '1') buffer |= 1;
            bit_count++;
            if (bit_count == 8) {
                compressed_csv.put(buffer); // write full byte
                buffer = 0;
                bit_count = 0;
            }
        }
    }

    // Write remaining bits, if any, padding them with 0s
    if (bit_count > 0) {
        buffer <<= (8 - bit_count);
        compressed_csv.put(buffer);
    }
    
    cout << "Compression done. Output written to compressed_csv.huff"<<endl;
    float compression_ratio=(float)csv_txt.tellg()/compressed_csv.tellp();
    cout<<"Compression ratio is :- "<<compression_ratio<<":1"<<endl;
    compressed_csv.close();
    huffman_map.clear();

    auto end_single = chrono::high_resolution_clock::now();
    auto duration_single = chrono::duration_cast<chrono::milliseconds>(end_single - start_single).count();
    cout << "Single-threaded time: " << duration_single << " ms" << endl;

    //====================================================================================================================
    /* Now i will use multi threading in order to fasten up the compression and 
       not messing with the compression ratio either. First i will split the file 
       in chunks and will make frequency_map for each chunk  then i will merge the maps
       after that will build a single huffmann tree from it and encoding will be again done 
       parallely*/
    //====================================================================================================================
    auto start_multi = chrono::high_resolution_clock::now();

    vector<string> c;
    ifstream csv_ttxt(csv_txt_filepath);
    ofstream compressed_csv_threaded("compressed_csv_threaded.huff",ios::binary);
    c=split(csv_ttxt);

    vector<map<char,int>>mp=chunk_map(c);
    map<char,int> final_map=merging_map(mp);
    vector<node*> element=element_creation(final_map);
    node* root=huffmann_tree(element);
   
    map<char, string> huffman_maps;
    vector<pair<char,string>> ans_threaded;
    encoded(ans_threaded, root);
    for (auto& p : ans_threaded) {
        huffman_maps[p.first] = p.second;
    }

    vector<string> encoded_chunks(c.size());
    auto encode_chunk = [&](int index) {
    for (char ch : c[index]) {
        encoded_chunks[index] += huffman_maps[ch];
    }
    };

    vector<thread> encode_threads;
    for (int i = 0; i < c.size(); ++i) {
        encode_threads.emplace_back(encode_chunk, i);
    }
    for (auto& t : encode_threads) {
    t.join();
    }

    //converting all the encoded codes form diff chunks to a single string
    string final_encodeds;
    for (const auto& encoded : encoded_chunks) {
        final_encodeds += encoded;
    }

    //Conversion of 0 and 1 in bits
    for (char bit : final_encodeds) {
    buffer <<= 1;
    if (bit == '1') buffer |= 1;
    bit_count++;
    if (bit_count == 8) {
        compressed_csv_threaded.put(buffer);
        buffer = 0;
        bit_count = 0;
    }
    }
    if (bit_count > 0) {
        buffer <<= (8 - bit_count);
        compressed_csv_threaded.put(buffer);
    }   

    cout << "Compression done. Output written to compressed_csv_threaded.huff"<<endl;
    compression_ratio=(float)csv_ttxt.tellg()/compressed_csv_threaded.tellp();
    cout<<"Compression ratio is :- "<<compression_ratio<<":1"<<endl;
    csv_ttxt.close();
    compressed_csv.close();
    
    auto end_multi = chrono::high_resolution_clock::now();
    auto duration_multi = chrono::duration_cast<chrono::milliseconds>(end_multi - start_multi).count();
    cout << "Multithreaded time: " << duration_multi << " ms" << endl;
    
}

//====================================================================================================================
/* *****NOTE***** */
//No of threads = no of cores if extra thread are created then they will be time sliced
//Since one thread can run in a core at A POINT OF TIME no two cores can run simultaneously on a same core
//====================================================================================================================


/*g++ -std=c++17 read_file.cpp -o read_fileension -I/opt/homebrew/include -L/opt/homebrew/lib -lpoppler-cpp
./read_fileension*/