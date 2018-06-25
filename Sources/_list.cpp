//  _List.h
/******************************************************************************

	  class _List<Type>

		Tsaplin V.

******************************************************************************/

#include "_list.h"

class _ListNode {
	_ListNode* next;
	void* data;
public:
	_ListNode(void* const d, _ListNode* n=0)
		:next(n), data(d)					{}
	~_ListNode()								{ delete next; 	} 
	void* Data()							{ return data; }
	_ListNode*& Next()						{ return next; }
};

//_____________________________________________________________________________

_ListHeader::~_ListHeader()					{ delete head; }

BOOL _ListHeader::Restore()
{ 
	cursor = &head; 
	return (head==0) ? FALSE : TRUE; 
}

void _ListHeader::Insert(void* const d)		{ head = new _ListNode(d,head); count++; }

void* _ListHeader::Iterate(BOOL& More)
{ 
	if (*cursor==0) return 0;
	_ListNode* _cursor_prev = *cursor;
	cursor = &(*cursor)->Next();
	More = (*cursor==0) ? FALSE : TRUE;
	return _cursor_prev->Data();
}

void _ListHeader::Move(_ListHeader* const to) 
{
	if (*cursor==0) return;
	_ListNode* n = *cursor;
	*cursor = (*cursor)->Next(); count--;
	n->Next() = to->head;
	to->head = n; to->count++;
}

void* _ListHeader::Delete(BOOL& More) 
{ 
	if (*cursor==0) return 0;
	_ListNode* n = *cursor;
	void* d = n->Data();
	*cursor = (*cursor)->Next(); count--;
	More = (*cursor==0) ? FALSE : TRUE;
	n->Next() = 0;
	delete n;
	return d;
}

void* _ListHeader::GetData() const
{
	return (*cursor)->Data();
}

//_____________________________________________________________________________
