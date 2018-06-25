//-----------------------------------------------------------------------------------
//
//	2D Tens class
//
//-----------------------------------------------------------------------------------
#ifndef ___Tens2D_h___
#define ___Tens2D_h___


#define Tens2D_ const Tens2D&

#include "def.h"
//#include "vect3D.h"
#include "vect2D.h"

#include <iostream>
using namespace std;

//-----------------------------------------------------------------------------------

class Tens2D
{
public:
	struct	 SFLOAT								{ float xx;	float xy; float yx; float yy;};
	struct	 SDOUBLE							{ double xx;	double xy; double yx;	double yy;};

	Tens2D()									{};		
	Tens2D(FLT xx, FLT xy, FLT yx, FLT yy)	{this->xx = xx; this->xy = xy; this->yx = yx; this->yy = yy;};
	Tens2D(Vect2D a, Vect2D b)					{this->xx = a.x*b.x; this->xy = a.x*b.y; this->yx = a.y*b.x; this->yy = a.y*b.y;};
	
	FLT Trace()  							{return (this->xx + this->yy);};
	Tens2D operator -()					const	{ Tens2D A = Tens2D(-xx, -xy, -yx, -yy); return A;}

	Tens2D& operator +=(Tens2D_ r)				{ xx += r.xx;	xy += r.xy; yx += r.yx;	yy += r.yy; return *this; }
	Tens2D& operator -=(Tens2D_ r)				{ xx -= r.xx;	xy -= r.xy; yx -= r.yx;	yy -= r.yy; return *this; }

	FLT  xx,	 xy,  yx,	 yy;
};

//-----------------------------------------------------------------------------------

static const Tens2D  Tens2D_0(0, 0, 0, 0);		// zero vector

//-----------------------------------------------------------------------------------

static inline Vect2D operator *(Vect2D r1, Tens2D_ r2)	{ Vect2D rr = Vect2D(r1.x*r2.xx + r1.y*r2.yx, r1.x*r2.xy + r1.y*r2.yy);	return rr;	}
//static inline Tens2D operator *(FLT r1, Tens2D_ r2)	{ Tens2D rr = Tens2D(r1*r2.xx, r1*r2.xy, r1*r2.yx, r1*r2.yy);	return rr;	}

static inline Tens2D operator *(FLT r1, Tens2D_ r2)	{ Tens2D rr = Tens2D(r1*r2.xx, r1*r2.xy, r1*r2.yx, r1*r2.yy);	return rr;	}
static inline Tens2D operator /(Tens2D_ r2, FLT r1)	{ Tens2D rr = Tens2D(r2.xx/r1, r2.xy/r1, r2.yx/r1, r2.yy/r1);	return rr;	}
static inline Tens2D operator +(Tens2D_ r1, Tens2D_ r2)	{ Tens2D rr = Tens2D(r1.xx+r2.xx, r1.xy+r2.xy, r1.yx+r2.yx, r1.yy+r2.yy);	return rr;	}
static inline Tens2D operator -(Tens2D_ r1, Tens2D_ r2)	{ Tens2D rr = r1 + (-r2);	return rr;	}

//-----------------------------------------------------------------------------------

#endif //___Vect2D_h___

