#include <fstream>
#include "vect3D.h"
#include "run2D.h"
#include "math.h"

//#include <stdlib.h>     /* srand, rand */
using namespace std;


Box2D Create_triangular_lattice(Atom2D* as_0, FLT porosity, LONG nx, LONG ny, LONG n_0, FLT a0, FLT aequiv, FLT v0, FLT a_cut, FLT f0, LONG krand, FLT dt, const LONG n_div)
{
	Atom2D* i = as_0;
	LONG   ix = 0;
    FLT qq = sqrt(3.)/2 * a0;
	FLT d_n = a0*ny/2;
	Vect2D r0;
	r0.x = 1;
	r0.y = 0;
	FLT m1 = -1;

	if (ny % 2 != 0) ny--;

	LONG k;
	LONG number_0 = 0;
	LONG test = 0;

	const double PI = 4.*atan(1.);
	unsigned int counter = 0;

    size_t middle = floor(nx/2);

	for (k=0; k < ny;k++)
	{
		m1 = - m1;
		for (ix = 0;ix < nx;ix++)
		{
                i->r    = r0 * (ix - nx/2) * a0;
				i->r.y  = d_n - k * qq;
				i->r.x += 0.25 * m1 * a0;
				i->v.SetRand(v0);
				//i->v.y = 0;


				//if (ix == middle){
                //    counter++;
                //    i->v.x += 100 * v0 * sin(PI * k / ny);
				//}
				i->v.x += 100 * v0 * sin(PI * k / ny);


				i->real = 1;
				i++;
				test++;
				number_0++;



		}
	}

    Atom2D* iend = i;

	for (i=iend; i!= as_0 +n_0; i++) i->real = 0;


	// elemination of mean velocity

	Vect2D vmean = VECT2D_0;
	for (i = as_0; i!= as_0+n_0; i++)
	{
	    if (i->real == 1) vmean += i->v;
	}
	vmean /=n_0;
	for (i = as_0; i!= as_0+n_0; i++) if (i->real == 1){  i->v -= vmean;}

	//EO  elemination of mean velocity

	// shift the sample
	Atom2D* i_min = as_0;
	for (i = as_0; i!= as_0+n_0; i++)
	{
		if (i->real == 1 && i->r.Abs() < i_min->r.Abs()) {i_min = i;}
	}

	Vect2D dr =  i_min->r;
	for (i = as_0; i!= as_0+n_0; i++) {i->r -= dr;}// }

// determination of bound box
    FLT max_x = -100000000;
    FLT min_x = 100000000;
    FLT max_y = -100000000;
    FLT min_y = 100000000;


	for (i = as_0; i!= as_0+n_0; i++)
	{
	    if (i->real == 1)
	    {
          if (i->r.x > max_x) max_x = i->r.x;
		  if (i->r.x < min_x) min_x = i->r.x;
		  if (i->r.y > max_y) max_y = i->r.y;
		  if (i->r.y < min_y) min_y = i->r.y;
	    }

	}

	FLT da = 0;
	FLT z1_x = min_x - da- 0.25*a0;  //
	FLT z2_x = max_x + da + 0.25*a0; //

	FLT z1_y = min_y - da- sqrt(3.)/4 * a0;  //
	FLT z2_y = max_y + da + sqrt(3.)/4 * a0; //

	return Box2D(z1_x, z1_y, z2_x, z2_y);
}

