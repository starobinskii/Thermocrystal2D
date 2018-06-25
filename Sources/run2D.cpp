#include "run2D.h"
#include "array.h"
#include "_list.h"
#include "a3r.h"
#include "vect3D.h"
#include "util.h"
#include <fstream>
#include <math.h>

#include <sstream>

string IntToString(int a)
{
    ostringstream temp;
    temp << a;
    return temp.str();
}

//------------------------------------------------------------------------------------------

void RunBoxPeriodic_no_3NL(Atom2D* as, LONG n, FLT dt, FLT a, FLT a_cut, FLT f0,  Box2D area, FLT* pTemp, LONG s, const int iter, double Ex0, double Ey0, double To, LONG nnnx, LONG nnny) // !!!
{
    FLT aa = a * a,		    aa_cut = a_cut * a_cut;
	FLT f1 = f0 * dt / a;
	FLT		ax = area.Width(),		ay = area.Height();
	FLT		x0 = area.X1(),			y0 = area.Y1();
	// --- Calculating the space parameters ---
	LONG	nx = LONG(ax / a_cut),	ny = LONG(ay / a_cut);
//	if (!(nx && ny))	{ Run(as, n, dt, a, a_cut, f0, B, pressure); return; }	// Space is not needed

	FLT		cx = ax / nx,			cy = ay / ny;
	Atom2D* i;		Atom2D* i_end = as + n;
	LONG ix, iy;

	// --- Creating the space ---
	Array2D< _List<Atom2D> > space(nx + 2, ny + 2);

    LONG ab_n;	// size of the array containing boundary particles
	{
		FLT boundary_volume = 2 * (nx + ny + 2) * cx * cy;
		FLT Vo = sqrt(3.) / 2 * a * a;
		FLT safety_coefficient = 2;
		ab_n = LONG(safety_coefficient * boundary_volume / Vo);
	}

	Atom2D*	ab = new Atom2D[ab_n];
	Atom2D* ab_i = ab;

	    /// -----------------------------------запись в файл энергии-------------------------------------------------

	const double PI = 4.*atan(1.);

	double vx_part = 0;
	double vy_part = 0;
	double vsum_part = 0;
	double vmin_part = 0;
	double Ex_sum = 0;
	double Ey_sum = 0;
	double E_sum = 0;
    double Eres = 0;

    double E1 = 0;
    double E2 = 0;
    double E3 = 0;
    double E4 = 0;
    double E5 = 0;
    double E6 = 0;
    double E7 = 0;
    double E8 = 0;
    double E9 = 0;
    double E10 = 0;
    double E11 = 0;
    double E12 = 0;
    double E13 = 0;
    double E14 = 0;
    double E15 = 0;

    double E16 = 0;
    double E17 = 0;
    double E18 = 0;
    double E19 = 0;
    double E20 = 0;
    double E21 = 0;


//    for (i = as; i != i_end; i++)
//	{
//        vx_part = i->v.x;
//		vy_part = i->v.y;
//		Ex_sum += vx_part * vx_part; ///\* sin(PI );       ///          забить правильное умножение
//		Ey_sum += vy_part * vy_part;
//	}
//	std::cout << "meow " << Ex_sum << std::endl;


	size_t middle = floor(nx/2);

    i = as;
	for (size_t ky=0; ky < nnny; ky++)
	{

		for (size_t kx = 0; kx < nnnx; kx++)
		{
		    vx_part = i->v.x;
            vy_part = i->v.y;
            vsum_part = sqrt(vx_part * vx_part + vy_part * vy_part);
            vmin_part = sqrt(vx_part * vx_part - vy_part * vy_part);

            E1 += vx_part * vx_part;
            E2 += vy_part * vy_part;
            E3 += vsum_part * vsum_part;
            //E4 += vmin_part * vmin_part;
            E4 += vx_part * vx_part - vy_part * vy_part;


            E5 += vx_part * vx_part * sin(PI * (double) ky / ((double) nnny));
            E6 += vy_part * vy_part * sin(PI * (double) ky / ((double) nnny));
            E7 += vsum_part * vsum_part * sin(PI * (double) ky / ((double) nnny));

            E8 += vx_part * vx_part * sin(PI * (double) ky / ((double) nnny)) + vy_part * vy_part;
            E9 += vy_part * vy_part * sin(PI * (double) ky / ((double) nnny)) + vx_part * vx_part;

            E16 += pow(vx_part * sin(PI * (double) ky / ((double) nnny)), 2);
            E17 += pow(vy_part * sin(PI * (double) ky / ((double) nnny)), 2);
            E18 += pow(vsum_part * sin(PI * (double) ky / ((double) nnny)), 2);
            E19 += pow(vx_part * sin(PI * (double) ky / ((double) nnny)) + vy_part, 2);
            E20 += pow(vy_part * sin(PI * (double) ky / ((double) nnny)) + vx_part, 2);
            E21 += pow((vx_part + vy_part) * sin(PI * (double) ky / ((double) nnny)), 2);


		    if (kx == middle){

                //Ex_sum += pow(vx_part * sin(PI * (double) ky / ((double) nnny)), 2); //pow(vx_part * sin(PI * (double) ky / ((double) nnny)), 2);
                //Ey_sum += vy_part * vy_part;

                //E5 += vx_part * sin(PI * (double) ky / ((double) nnny));
                //E6 += vy_part;

                E10 += pow(vx_part * sin(PI * (double) ky / ((double) nnny)), 2);
                E11 += pow(vy_part * sin(PI * (double) ky / ((double) nnny)), 2);
                E12 += pow(vsum_part * sin(PI * (double) ky / ((double) nnny)), 2);
                E13 += pow(vx_part * sin(PI * (double) ky / ((double) nnny)) + vy_part, 2);
                E14 += pow(vy_part * sin(PI * (double) ky / ((double) nnny)) + vx_part, 2);
                E15 += pow((vx_part + vy_part) * sin(PI * (double) ky / ((double) nnny)), 2);
		    }
		    //std::cout << "meow " << Ex_sum << std::endl;

		    //E1 = Ex

            i++;

		}
	}
	//Ex_sum = Ex_sum * Ex_sum;
	//Ey_sum = Ey_sum * Ey_sum;

    if (s == 1)                //запоминание Ex0 и Ey0
    {
        setEx0(Ex_sum);
        setEy0(Ey_sum);
        Ex0 = Ex_sum;
        Ey0 = Ey_sum;
    }
    //считаем сумму
    //Eres = (Ex_sum + Ey_sum)/(Ex0 + Ey0);

    Eres = Ex_sum / (Ex0 + Ey0);

    char file_name1[21];
    const std::string filename = "Results/energy" + IntToString(iter) + ".txt";
    sprintf(file_name1, filename.c_str());
    FILE* fv_BB  = fopen(file_name1,"a");
    //fprintf(fv_BB, "%s%d%s%f%s%f", "Step: ", s, " E_x: ", Ex_sum, " E_y: ", Ey_sum);
    fprintf(fv_BB, "%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f", s*dt/To, " ", E1, " ", E2, " ", E3, " ", E4, " ", E5, " ", E6, " ", E7, " ", E8, " ", E9, " ", E10, " ", E11, " ", E12, " ", E13, " ", E14, " ", E15, " ", E16, " ", E17, " ", E18, " ", E19, " ", E20, " ", E21);  //текущее
//    fprintf(fv_BB, "%f%s%f%s%f", s*dt/To, " ", Ex_sum/Ex0, " ", Ey_sum/Ex0);     //вывод по отдельности
    fprintf(fv_BB, "%s", "\n");

    //fprintf(fv_BB, "%s", "\n");
    fclose(fv_BB);
    /// -----------------------------------конец записи в файл-----------------------------------------------

	for (i = as; i != i_end; i++)
	{
		while (i->r.x <  area.X1()) i->r.x += ax;
		while (i->r.x >= area.X2()) i->r.x -= ax;
		while (i->r.y <  area.Y1()) i->r.y += ay;
		while (i->r.y >= area.Y2()) i->r.y -= ay;

		ix = 1 + LONG((i->r.x - x0) / cx);
		iy = 1 + LONG((i->r.y - y0) / cy);

		space[ix][iy].Insert(i);

		FLT dx = 0, dy = 0;
		LONG iix, iiy;

		if (ix == 1)  { dx = ax;  iix = nx + 1; }
		if (ix == nx) { dx = -ax; iix = 0; }
		if (iy == 1)  { dy = ay;  iiy = ny + 1; }
		if (iy == ny) { dy = -ay; iiy = 0; }

		if (dx)		{ *ab_i = *i; ab_i->r.x += dx; space[iix][iy ].Insert(ab_i++); }
		if (dy)		{ *ab_i = *i; ab_i->r.y += dy; space[ix ][iiy].Insert(ab_i++);
						if (dx)
					{ *ab_i = *i; ab_i->r.x += dx;
					              ab_i->r.y += dy; space[iix][iiy].Insert(ab_i++);} }
	}



/// ------------------------------------------------------------------------------------


	for (i = as; i != i_end; i++)
	{
		ix = 1 + LONG((i->r.x - x0) / cx);
		iy = 1 + LONG((i->r.y - y0) / cy);

		LONG jx, jy;
		LONG _ix = ix - 1, _iy = iy - 1;
		LONG ix_ = ix + 1, iy_ = iy + 1;

		for(jx = _ix;	jx <= ix_;	jx++)
		for(jy = _iy;	jy <= iy_;	jy++)
		{
			_List<Atom2D>* lj = &space[jx][jy];
			BOOL more = lj->Restore();
			while(more)
			{
				Atom2D* j = lj->Iterate(more);
				if (i == j) continue;//
				//if (i == j) { jx = nx + 2; jy = ny + 2; break; };	// for 3rd Newton law
				Vect2D dr = i->r - j->r;
				if (fabs(dr.x) < a_cut && fabs(dr.y) < a_cut)
				{
					FLT dd = dr.Sqr();
					if (dd < aa_cut)
					{
						FLT ss = aa / dd;
						FLT s4  = ss * ss; FLT F = (1 - ss * s4) * s4 * s4;	// LJ 6-12: s^8 - s^14
						Vect2D f = (f1 * F) * dr;
						i->v -= f;
						//j->v += f; // for 3rd Newton law
					} // if
				} // if
			} // while
		} // for
	} // for

//-----------------------------------------------------------


	for (i = as; i != i_end; i++)
	{
		i->r += i->v * dt;
		while (i->r.x <  area.X1()) i->r.x += ax;
		while (i->r.x >= area.X2()) i->r.x -= ax;
		while (i->r.y <  area.Y1()) i->r.y += ay;
		while (i->r.y >= area.Y2()) i->r.y -= ay;
	}


    delete [] ab;
}

double Exo;
double Eyo;
double getEx0()
{
   return Exo;
}

double getEy0()
{
   return Eyo;
}

void setEx0(double Ex0)
{
    Exo = Ex0;
}

void setEy0(double Ey0)
{
    Eyo = Ey0;
}

//-----------------------------------------------------------------------------------

Box2D GetBoundBox(Atom2D* as, LONG n)
{
	Atom2D* i = as;
	Atom2D* i_end = as + n;

	FLT x1, x2, y1, y2;
	x1 = x2 = i->r.x;
	y1 = y2 = i->r.y;

	for (i = as + 1; i != i_end; i++)
	{
		if(i->r.x < x1) x1 = i->r.x;
		if(i->r.x > x2) x2 = i->r.x;
		if(i->r.y < y1) y1 = i->r.y;
		if(i->r.y > y2) y2 = i->r.y;
	}

	return Box2D(x1, y1, x2, y2);
}

//-------------------------------------------------------------------------------------------

#include <fstream>
using namespace std;


//-------------------------------------------------------------------------------------------

#define RGB(r, g ,b) (r + 256 * g + 65536 * b)

//----------------------------------------------------------------

static const int C0		=   0;
static const int C1		=  64;
static const int C2		= 128;
static const int C3		= 192;
static const int C4		= 255;

BOOL Save_A3R(const char* file_name, Atom2D* as, LONG n, FLT r)
{
	filebuf file;

#ifdef UNIX
	if(!file.open(file_name, ios::out)) return FALSE;
#else
	if(!file.open(file_name, ios::out | ios::binary)) return FALSE;
#endif


	LONG nreal = n;
	/*for (Atom2D* i = as; i != as + n; i++)
	{
		if (i->real != 0) nreal++;
	}*/

	A3R_HEADER header;
	header.count = nreal;
	header.r = r;

	file.sputn((char*) &header, sizeof(header));
	for (Atom2D* i = as; i != as + n; i++)
	{
		//if (i->real != 0)
		//{
			Vect3D r(i->r.x, i->r.y, 0);
			r.RotateX(DEG * .001);
			r.RotateY(DEG * .001);
			Vect3D::SFLOAT sr = r;
			file.sputn((char*) &sr, sizeof(Vect3D::SFLOAT));
		//}
	}

	file.close();

	return TRUE;
}




BOOL Save_A3R(const char* file_name, Vect3D* start, LONG n, FLT r)
{
	filebuf file;

#ifdef UNIX
	if(!file.open(file_name, ios::out)) return FALSE;
#else
	if(!file.open(file_name, ios::out | ios::binary)) return FALSE;
#endif




	A3R_HEADER header;
	header.count = n;
	header.r = r;

	file.sputn((char*) &header, sizeof(header));
	for (Vect3D* i = start; i != start + n; i++)
	{

		Vect3D::SFLOAT sr = *i;
			file.sputn((char*) &sr, sizeof(Vect3D::SFLOAT));
	}

	file.close();

	return TRUE;
}

//-------------------------------------------------------------------------------------------

BOOL SaveMarked_A3R(const char* file_name, Atom2D* as, LONG n, FLT r)
{
	filebuf file;

#ifdef UNIX
	if(!file.open(file_name, ios::out)) return FALSE;
#else
	if(!file.open(file_name, ios::out | ios::binary)) return FALSE;
#endif

	Atom2D* i;
	LONG n_marked = 0;
	for (i = as; i != as + n; i++) if(i->c) n_marked++;

	A3R_HEADER header;
	header.count = n_marked;
	header.r = r;

	file.sputn((char*) &header, sizeof(header));
	for (i = as; i != as + n; i++)
	{
		if(i->c)
		{
			Vect3D r(i->r.x, i->r.y, 0);
			r.RotateX(DEG * .001);
			r.RotateY(DEG * .001);
			Vect3D::SFLOAT sr = r;
			file.sputn((char*) &sr, sizeof(Vect3D::SFLOAT));
		}
	}

	file.close();

	return TRUE;
}

//-------------------------------------------------------------------------------------------

BOOL Get_count_A3R(const char* file_name, LONG& n)
{
	filebuf file;

#ifdef UNIX
	if(!file.open(file_name, ios::in | ios::nocreate)) return FALSE;
#else
	if(!file.open(file_name, ios::in | ios::binary)) return FALSE;
#endif

	A3R_HEADER header;
	file.sgetn((char*)&header, sizeof(A3R_HEADER));
	if(strcmp(header.file_type, "a3r")) return FALSE;
	n = header.count;

	return TRUE;
}

//-------------------------------------------------------------------------------------------

BOOL Load_A3R(const char* file_name, Atom2D* as, LONG& n, FLT& r)
{
	filebuf file;

#ifdef UNIX
	if(!file.open(file_name, ios::in | ios::nocreate)) return FALSE;
#else
	if(!file.open(file_name, ios::in | ios::binary)) return FALSE;
#endif

	A3R_HEADER header;
	file.sgetn((char*)&header, sizeof(A3R_HEADER));
	if(strcmp(header.file_type, "a3r")) return FALSE;
	n = min(n, header.count);
	r = header.r;

	for (Atom2D* i = as; i != as + n; i++)
	{
		Vect3D::SFLOAT sr;
		file.sgetn((char*) &sr, sizeof(Vect3D::SFLOAT));
		i->r.Set(sr.x, sr.y);
		i->v.Set(0, 0);
	}

	file.close();

	return TRUE;
}

//-----------------------------------------------------------------------------------

