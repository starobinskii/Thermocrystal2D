//-----------------------------------------------------------------------------------
//
//	2D Box class
//
//	Anton M. Krivtsov
//
//	29.10.2001
//
//-----------------------------------------------------------------------------------

#include "vect2D.h"
#include "box2D.h"
#include <fstream>
using namespace std;


//-----------------------------------------------------------------------------------

void Vect2D::SetRand(const Box2D& box) 
{ 
    SetRand(box.X1(), box.Y1(), box.X2(), box.Y2()); 
}

//-----------------------------------------------------------------------------------

Box2D Box2D::GetZoomed(FLA kx, FLA ky) const
{
	FLT cx = 0.5 * (X2() + X1());
	FLT cy = 0.5 * (Y2() + Y1());
	FLT dx = 0.5 * (X2() - X1()) * kx;
	FLT dy = 0.5 * (Y2() - Y1()) * ky;
	
	return Box2D(cx - dx, cy - dy, cx + dx, cy + dy);  
}

//-----------------------------------------------------------------------------------

BOOL Box2D::Save(const char* file_name) const
{
	filebuf file;
		
#ifdef UNIX
	if(!file.open(file_name, ios::out)) return FALSE;
#else
	if(!file.open(file_name, ios::out | ios::binary)) return FALSE;
#endif

	SDOUBLE box = *this;
	
	file.sputn((char*) &box, sizeof(SDOUBLE));
	file.close();
		
	return TRUE;
}

//-----------------------------------------------------------------------------------

BOOL Box2D::Load(const char* file_name)	
{
	filebuf file;

#ifdef UNIX
	if(!file.open(file_name, ios::in | ios::nocreate)) return FALSE;
#else
	if(!file.open(file_name, ios::in | ios::binary)) return FALSE;
#endif

//	if (file.in_avail() != sizeof(SDOUBLE)) return FALSE;

	SDOUBLE box;

	file.sgetn((char*)&box, sizeof(SDOUBLE));
	file.close();

	*this = box;
	
	return TRUE;
}

//-----------------------------------------------------------------------------------

