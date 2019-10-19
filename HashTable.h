#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include<string>
#include<vector>
#include"LinkedList.h"
#include<iostream>
using namespace std;

class Entry      //entry class for hash table inserts

{
public:
	string element;
	string meaning;
	Entry( const string & theElement="",const string & tur="" ): element( theElement ),meaning(tur) { }
	Entry( const Entry &e ) {element=e.element; meaning=e.meaning; }
	bool operator==(const Entry &rhs) const

	{ return(element == rhs.element);  }

	bool operator!=(const Entry &rhs) const

	{ return ! (*this == rhs); }

};

int Hash( const Entry & key, int tableSize ){   //hash function using polynomial method with prime numbers
	long long sum=13;
	for(unsigned int i=0;i<(key.element).size();i++)
	{
		sum=sum*31+(key.element).at(i);
	}
	if(sum<0)
		sum=(-1)*sum+tableSize;
	return sum %tableSize;
}

template <class HashedObj>
class HashTable

{

public:

	HashTable( const HashedObj & notFound,int size = 53 );

	HashTable( const HashTable & rhs ): ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),theLists( rhs.theLists ) {currentSize=0; }

	const HashedObj & find( const HashedObj & x ) const;

	void makeEmpty( );

	void insert( const HashedObj & x );

	void remove( const HashedObj & x );

	const HashTable & operator=( const HashTable & rhs);

	void printSize();  //debug

	int currentSize;  //size of elements currently inserted
	
	int tableSize();  //for returning size of the table
private:

	// The array of Lists
	vector<List<HashedObj>> theLists;

	const HashedObj ITEM_NOT_FOUND;

	void rehash();
	int nextPrime( int n ) ;
	bool isPrime( int n );
};

#include "HashTable.cpp"


#endif 