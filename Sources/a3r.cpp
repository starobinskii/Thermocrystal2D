//-----------------------------------------------------------------------------------
//
//	Saving and loading particle coordinates in A3R format
//
//	Anton M. Krivtsov
//
//	29.10.2001
//
//-------------------------------------------------------------------------------------------

#include "a3r.h"
//#include "colors.h"
#include <fstream>
using namespace std;

//-------------------------------------------------------------------------------------------

A3R_HEADER::A3R_HEADER() 
: count(0)
, r(0)
, count_1(0)
{ 
	strcpy(file_type, "a3r"); 
	strcpy(version, "a"); 
	data_start = sizeof(A3R_HEADER);
}

//-------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------

Vect3D* Load_A3R(const char* file_name, LONG& n, FLT& r)	
{
	filebuf file;

#ifdef UNIX
	if(!file.open(file_name, ios::in | ios::nocreate)) return NULL;
#else
	if(!file.open(file_name, ios::in  | ios::binary)) return NULL;
#endif

	A3R_HEADER header;

	file.sgetn((char*)&header, sizeof(A3R_HEADER));
	if(strcmp(header.file_type, "a3r")) return NULL;
	n = header.count;
	r = header.r;

	Vect3D::SFLOAT* buf = new Vect3D::SFLOAT[n];
	Vect3D::SFLOAT* j = buf;

	file.sgetn((char*)buf, sizeof(Vect3D::SFLOAT) * n);

	file.close();
	
	Vect3D* start = new Vect3D[n];
	Vect3D* stop = start + n;
	for (Vect3D* i = start; i != stop; i++) *i = *j++;
	delete [] buf;
	
	return start;
}

//-------------------------------------------------------------------------------------------

