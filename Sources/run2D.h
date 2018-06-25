#ifndef ___run2D_h___
#define ___run2D_h___
#include "vect2D.h"		// 2D Vector class
#include "Tens2D.h"		// 2D Vector class
#include "box2D.h"		// 2D Box class
//#include "colors.h"
//-----------------------------------------------------------------------------------

class Atom2D
{
public:
	Vect2D r, v;	// Position and velocity
    BOOL real;
	LONG c;			// Reserved to mark atoms. Can be used as a color.
};

//-----------------------------------------------------------------------------------
// Single step of 2D simulation (for small number of particles: does not use space)
void RunBoxPeriodic_no_3NL(Atom2D* as, LONG n, FLT dt, FLT a, FLT a_cut, FLT f0, Box2D area, FLT* pTemp, LONG s, const int iter, double Ex0, double Ey0, double To, LONG nnnx, LONG nnny);
double getEx0();
double getEy0();
void setEx0(double Ex0);
void setEy0(double Ey0);
//-----------------------------------------------------------------------------------
// Functions to save (load) atoms configuration to (from) A3R file

BOOL Get_count_A3R	(const char* file_name,	LONG& n);
BOOL Save_A3R		(const char* file_name, Atom2D* atoms, LONG  n, FLT  r);
BOOL SaveMarked_A3R	(const char* file_name, Atom2D* atoms, LONG  n, FLT  r);
BOOL Load_A3R		(const char* file_name, Atom2D* atoms, LONG& n, FLT& r);

//-----------------------------------------------------------------------------------

Box2D GetBoundBox(Atom2D* as, LONG n);

//-----------------------------------------------------------------------------------

#endif //___run2D_h___
