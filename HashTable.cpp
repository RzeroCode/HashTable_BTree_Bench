/**

* Construct the hash table.

*/

template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj & notFound, int size ): ITEM_NOT_FOUND( notFound ), theLists( nextPrime( size ) )
{
	currentSize=0;
}

/**

* Internal method to test if a positive number is prime.

* Not an efficient algorithm.

*/
template <class HashedObj>
bool HashTable<HashedObj>::isPrime( int n )
{
	if ( n == 2 || n == 3 )
		return true;
	if ( n == 1 || n % 2 == 0 )
		return false;
	for ( int i = 3; i * i <= n; i += 2 )
		if ( n % i == 0 )
			return false;

	return true;
}

/**

* Internal method to return a prime number

* at least as large as n. Assumes n > 0.

*/
template <class HashedObj>
int HashTable<HashedObj>::nextPrime( int n )
{
	if ( n % 2 == 0 )
		n++;
	for ( ; ! isPrime( n ); n += 2 )
		;
	return n;
}

/**

* Make the hash table logically empty.

*/

template <class HashedObj>

void HashTable<HashedObj>::makeEmpty( )

{

	for(unsigned int i = 0; i < theLists.size( ); i++ )

		theLists[ i ].makeEmpty( );

	// destroy the lists but not the vector!

}

/**

* Insert item x into the hash table. If the item is

* already present, then do nothing.

*/

template <class HashedObj>

void HashTable<HashedObj>::insert( const HashedObj & x )

{

	// hash the given object and locate the list it should be on
	List<HashedObj> & whichList = theLists[ Hash( x, theLists.size( ) ) ];

	// locate the object in the list (using List’s find)

	ListItr<HashedObj> itr = whichList.find( x );

	// insert the new item at the head of the list if not found!

	if ( itr.isPastEnd( ) )

		whichList.insert( x, whichList.zeroth( ) );

	if ( ++currentSize >= (double(theLists.size( )) *0.5) )        //rehash if load factor is not satisfied
		rehash( );

}

/**

* Remove item x from the hash table.

*/

template <class HashedObj>

void HashTable<HashedObj>::remove( const HashedObj & x )

{

	// remove from the appropriate list

	theLists[ Hash( x, theLists.size( ) ) ].remove( x );
	currentSize--;

}

/**

* Find item x in the hash table.

* Return the matching item or ITEM_NOT_FOUND if not found

*/

template <class HashedObj>

const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) const
{
	ListItr<HashedObj> itr;

	// locate the approriate list and search there

	itr = theLists[ Hash( x, theLists.size( ) ) ].find( x );

	// retrieve from the located position

	if ( itr.isPastEnd( ) )

		return ITEM_NOT_FOUND;

	return itr.retrieve( );

}
/**

* Expand the hash table.

*/

template <class HashedObj>

void HashTable<HashedObj>::rehash( )

{

	vector<List<HashedObj>> oldArray = theLists;
	const int oldSize=theLists.size();

	// Create new double-sized, empty table

	theLists.resize( nextPrime( 2 * oldArray.size( ) ) );
	makeEmpty();


	// Copy table over

	currentSize = 0;

	for (unsigned int i = 0; i < oldArray.size( ); i++ )

	{
		List<HashedObj> list=oldArray[ i ];
		ListItr<HashedObj> itr=list.first();
		for( ; !itr.isPastEnd( ); itr.advance( ) )
		{
			insert( itr.retrieve() );
		}	
	}
	cout<<"rehashed..."<<endl;
	cout<<"previous table size:"<<oldSize<<", new table size: "<<theLists.size()<<", current unique word count "<<currentSize<<","<<endl;
	cout<<"current load factor: "<<double(currentSize)/double(tableSize())<<endl;

}

template <class HashedObj>   //debug
void HashTable<HashedObj>::printSize()
{
	for(int i=0;i<theLists.size();i++)
	{
		int sum=0;
		ListItr<HashedObj> itr=theLists[i].first();
		for( ; !itr.isPastEnd( ); itr.advance( ) )
		{
			sum++;
		}
		cout<<i<<":  "<<sum<<endl;
	}
}

template <class HashedObj>   
int HashTable<HashedObj>::tableSize()
{
	return theLists.size();
}