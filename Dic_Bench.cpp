#include "Btree.h"
#include "HashTable.h"
#include<fstream>
#include<iostream>
#include<sstream>	
#include<sstream>
#include<chrono>
#include<vector>
using namespace std;

int main()
{
	auto tHash=long(0);
	auto tBtree=long(0);
	vector<string> vecQuery;

	Entry notFound("","");
	BinarySearchTree<string> mtree(""); //main tree
	HashTable<Entry> hTable(notFound);  //hash table
	ifstream input;    //dict file
	string filename="dict.txt"; 
	input.open(filename.c_str()); 
	string line;
	bool firstLine=true;   //For parsing utf characters
	
	cout<<"Building a binary tree for dict.txt..."<<endl;
	cout<<"Building a hash table for dict.txt..."<<endl;
	while(getline(input,line))    //read line by line
	{
		istringstream sLine(line);
		if(firstLine)    //ignore utf file special characters
		{
			sLine.get();
			sLine.get();
			sLine.get();
			firstLine=false;
		}
		string eng;   //english word
		sLine>>eng;
		string tur="";
		char chr=sLine.get(); 
		chr=sLine.get();
		while(chr!=-1)    //get turkish word till end of the string
		{
			tur+=chr;
			chr=sLine.get();
		}
		mtree.insert(eng,tur);   //insert word and it's translation
		Entry e(eng,tur);
		hTable.insert(e);
	}
	cout<<"After preprocessing, the unique word count is "<<hTable.currentSize<<". Current load ratio is "<<double(hTable.currentSize)/double(hTable.tableSize())<<endl;
	cout<<"Running queries in query1.txt..."<<endl;
	cout<<endl;

	ifstream fQuery;
	filename="query1.txt"; 
	fQuery.open(filename.c_str()); 
	string meaning="";
	Entry m;
	while(getline(fQuery,line))   //read line by line
	{
		istringstream sLine(line);
		string eng;   //english word
		sLine>>eng;
		vecQuery.push_back(eng);   //push to query vector
	}
	fQuery.close();
	
	cout<<"***********************************************"<<endl;
	cout<<"Benchmark results for Binary Search Tree (BST):"<<endl;
	cout<<"***********************************************"<<endl;
	auto time1=0;
	int count1=0;
	for(int k=0;k<vecQuery.size();k++)    //read line by line
	{  
		auto start1 = std::chrono::high_resolution_clock::now(); //time start
		meaning=mtree.findT(vecQuery.at(k));
		time1 += (std::chrono::high_resolution_clock::now() - start1).count();  //time for 1 line of query
		count1++;
	}
	cout<<"+ Elapsed time: "<<time1<<" ns"<<endl;
	cout<<"+ Average query time: "<<time1/count1<<" ns"<<endl;   //average of queries
	cout<<endl;

	cout<<"***********************************************"<<endl;
	cout<<"Benchmark results for Hash Table:"<<endl;
	cout<<"***********************************************"<<endl;
	auto time2=0;
	int count2=0;
	for(int k=0;k<vecQuery.size();k++)    //read line by line
	{  
		Entry temp(vecQuery.at(k));
		auto start2 = std::chrono::high_resolution_clock::now(); //time start
		m=hTable.find(temp);
		time2 += (std::chrono::high_resolution_clock::now() - start2).count();  
		count2++;
	}
	cout<<"+ Elapsed time: "<<time2<<" ns"<<endl;
	cout<<"+ Average query time: "<<time2/count2<<" ns"<<endl;
	cout<<"+ Speed up: "<<(time1/double(count1))/(time2/double(count2))<<"x"<<endl;   //speed up between bst and ht
	cout<<endl;




	cout<<"Time measurements in ns (N, 4096N):"<<endl;
	cout<<"*****************************"<<endl;

	ofstream outB;
	filename="bst_result.txt";
	outB.open(filename);        //bst output
	cout<<"bst"<<endl;
	cout<<"N"<<"\t"<<"time"<<endl;
	for(int i=1;i<4097;i*=2){   //for n=1,2,4,8....
		auto time1=0;

		for(int j=0;j<i;j++){           //run query for n times
			for(int k=0;k<vecQuery.size();k++)    //read line by line
			{  
				auto start1 = std::chrono::high_resolution_clock::now(); //time start
				meaning=mtree.findT(vecQuery.at(k));
				time1 += (std::chrono::high_resolution_clock::now() - start1).count();
				if(i==1)
				{

					outB<<vecQuery.at(k)<<"\t"<<meaning<<endl;   //write to output
				}
			}
		}

		cout<<i<<"\t"<<time1<<endl;
	}
	cout<<endl;
	outB.close();

	//almost same as binary tree s output algorithm
	ofstream outH;
	filename="ht_result.txt";
	outH.open(filename);
	cout<<"ht"<<endl;
	cout<<"N"<<"\t"<<"time"<<endl;
	for(int i=1;i<4097;i*=2){
		auto time2=0;
		//time start
		for(int j=0;j<i;j++){

			for(int k=0;k<vecQuery.size();k++)    
			{  
				Entry temp(vecQuery.at(k));  //create temporary entry object
				auto start2 = std::chrono::high_resolution_clock::now();
				m=hTable.find(temp);                               
				time2 += (std::chrono::high_resolution_clock::now() - start2).count();

				if(i==1)
				{

					outH<<vecQuery.at(k)<<"\t"<<m.meaning<<endl;
				}
			}
		}

		cout<<i<<"\t"<<time2<<endl;
	}
	outH.close();

	return 0;
}