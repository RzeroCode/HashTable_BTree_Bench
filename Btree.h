#ifndef BTREE_H
#define BTREE_H

#include<iostream>
#include<string>
using namespace std;


template <class Comparable>

class BinarySearchTree;

template <class Comparable>

class BinaryNode

{
	Comparable element;
	Comparable meaning;
	BinaryNode *left;
	BinaryNode *right;
	BinaryNode( const Comparable & theElement,const Comparable & tur,BinaryNode *lt=nullptr, BinaryNode *rt=nullptr ): element( theElement ),meaning(tur),left( lt ), right( rt ) { }
	friend class BinarySearchTree<Comparable>;
};
template <class Comparable>

class BinarySearchTree

{

public:

	explicit BinarySearchTree( const Comparable & notFound );
	BinarySearchTree( const BinarySearchTree & rhs );
	~BinarySearchTree( );
	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	const Comparable & find( const Comparable & x ) const;
	const Comparable & findT( const Comparable & x ) const;
	bool isEmpty( ) const;
	void printTree( ) const;
	void makeEmpty( );
	void insert( const Comparable & x,const Comparable & y);
	void remove( const Comparable & x );
	const BinarySearchTree & operator=( const BinarySearchTree & rhs );
private:

	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
	const Comparable & translationAt (BinaryNode<Comparable> *t ) const;
	void insert( const Comparable & x,const Comparable & y, BinaryNode<Comparable> * & t ) ;
	void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * find( const Comparable & x,BinaryNode<Comparable> *t ) const;
	void makeEmpty( BinaryNode<Comparable> * & t ) const;
	void printTree( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;

};

#include "Btree.cpp"

#endif