//  _List.h
/******************************************************************************

	  class _List<Type>

		Tsaplin V.

******************************************************************************/

#ifndef _ListTemplate_h_
#define _ListTemplate_h_

#include "def.h"

#include <iostream>
using namespace std;

class _ListNode;

class _ListHeader {
protected:
	_ListHeader() : head(0), cursor(&head), count(0)	{}
	~_ListHeader();
	void Insert(void* const d);
	void* Iterate(BOOL& More);
	void Move(_ListHeader* const to);
	BOOL Restore();								//	return TRUE, if _List not empty
	void* Delete(BOOL& More);

	void* GetData() const;
	LONG GetCount()	const							{ return count; }
private:
	_ListNode* head;
	_ListNode** cursor;
	LONG count;
}; 

//_____________________________________________________________________________

template<class Type>
class _List: private _ListHeader {
public:
	_List(): _ListHeader()			{}
	~_List()							{}
	void Insert(Type* const d)		{ _ListHeader::Insert((void*)d); }
	Type* Iterate(BOOL& More)		{ return ((Type*)_ListHeader::Iterate(More)); }
	void Move(_List<Type>* const to)	{ _ListHeader::Move(to); }
	BOOL Restore()					{ return _ListHeader::Restore(); }
	Type* Delete(BOOL& More)		{ return (Type*)_ListHeader::Delete(More); }

	Type* operator->() const		{ return (Type*)_ListHeader::GetData(); }
	LONG GetCount() const			{ return _ListHeader::GetCount(); }
}; 

//_____________________________________________________________________________
//_____________________________________________________________________________


template<class Type> 
ostream &operator <<(ostream& stream, _List<Type>& List)
{ 
	BOOL More = List.Restore();
	Type *r;
	while (More)
	{
		r = List.Iterate(More);
		cout << *r << "\n";
	}

	return cout;
}

//_____________________________________________________________________________

#endif //___ListTemplate_h__