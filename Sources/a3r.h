//-----------------------------------------------------------------------------------
//
//	Saving and loading particle coordinates in A3R format
//
//	Anton M. Krivtsov
//
//	11.04.2001
//
//-----------------------------------------------------------------------------------

#ifndef ___a3r_h___
#define ___a3r_h___

#include "vect3D.h"
#include <string.h>
#include "run2D.h"

//-----------------------------------------------------------------------------------

struct A3R_HEADER
{
	A3R_HEADER();		// Initialization of the structure members


//	Box3D box;


	char file_type[4];	// "a3r"
	LONG count;			// number of particles
	LONG data_start;	// address of the start of the particles data
	char version[10];	// version of a3r format
	double r;			// particle radius
	LONG count_1;		// reserved for the future use;
};

//-----------------------------------------------------------------------------------

BOOL Save_A3R(const char* file_name, Vect3D* start, LONG n, FLT r);

//BOOL  Save_A3R_col(const char* file_name, Atom2D* start, LONG n, FLT r,  BOOL use_color); // default box = BOX3D_0

Vect3D* Load_A3R(const char* file_name, LONG& n, FLT& r);	

//-----------------------------------------------------------------------------------

#endif //___a3r_h___
