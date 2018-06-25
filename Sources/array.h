//-----------------------------------------------------------------------------------
//
//	Array<TYPE> class
//
//	Anton M. Krivtsov
//
//	13.06.2001
//
//-----------------------------------------------------------------------------------

#ifndef ___Array_H___
#define ___Array_H___

#ifndef NULL
#define NULL 0
#endif

template<class TYPE> class Array
{
public:
	Array()								{ data = NULL;	count = 0; }
	~Array()							{ RemoveAll(); }

	int  GetCount() const				{ return count; }
	void Create(int n);
	void RemoveAll();

	// Direct Access to the element data (may return NULL)
	const TYPE* GetData() const			{ return (const TYPE*)data; }
	TYPE* GetData()						{ return (TYPE*)data; }

	TYPE  operator[](int i) const		{ return data[i]; }
	TYPE& operator[](int i)				{ return data[i]; }

protected:

	TYPE* data;		// the actual array of data
	int count;		// number of elements (upper bound - 1)
};

//---------------------------------------------------------------------------

template<class TYPE> void Array<TYPE>::RemoveAll()
{

	if (data != NULL) delete [] data;
	data = NULL;
	count = 0;
}

template<class TYPE> void Array<TYPE>::Create(int n)
{
	RemoveAll();
	if (n == 0) return;
	data = new TYPE[n];
	count = n;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template<class TYPE> class Array2D : public Array< Array<TYPE> >
{
public:
	Array2D() : Array< Array<TYPE> > ()		{};
	Array2D(int n1, int n2)					{ Create(n1, n2); }

	int  GetCount() const					{ return ((Array< Array<TYPE> > *)this)->GetCount() * this->data->GetCount(); }
	void Create(int n1, int n2);

protected:
};


//---------------------------------------------------------------------------

template<class TYPE> void Array2D<TYPE>::Create(int n1, int n2)
{
	((Array< Array<TYPE> > *)this)->Create(n1);
	for (int i = 0; i < n1; i++) (*this)[i].Create(n2);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template<class TYPE> class Array3D : public Array< Array2D<TYPE> >
{
public:
	Array3D() : Array< Array2D<TYPE> > ()	{};
	Array3D(int n1, int n2, int n3)			{ Create(n1, n2, n3); }

	int GetCount() const					{ return ((Array< Array2D<TYPE> > *)this)->GetCount() * this->data->GetCount(); }
	void Create(int n1, int n2, int n3);

protected:
};


//---------------------------------------------------------------------------

template<class TYPE> void Array3D<TYPE>::Create(int n1, int n2, int n3)
{
	((Array< Array2D<TYPE> > *)this)->Create(n1);
	for (int i = 0; i < n1; i++) (*this)[i].Create(n2, n3);
}

//---------------------------------------------------------------------------

#endif //___Array_H___

//---------------------------------------------------------------------------
