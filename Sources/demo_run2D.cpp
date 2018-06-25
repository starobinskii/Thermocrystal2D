//-----------------------------------------------------------------------------------
#include "run2D.h"		// 2D simulation functions
#include "timer.h"
#include "util.h"
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>

#include <sstream>

string IntToString_2(int a)
{
    ostringstream temp;
    temp << a;
    return temp.str();
}

//----------------------------------------------------------------------------------
Box2D Create_triangular_lattice(Atom2D* as_0, FLT porosity, LONG nx, LONG ny, LONG n_0, FLT a0, FLT aequiv, FLT v0, FLT a_cut, FLT f0, LONG krand, FLT dt, const LONG n_div);
void elimination(Atom2D* as_0, Atom2D* as, LONG n_0, LONG n);
//-----------------------------------------------------------------------------------
const FLT ao = 1;							// particle radius
const FLT co = 1;
const FLT Do = co*ao*ao/72.;
const FLT fo = 12.*Do/ao;	// interparticle force magnitude
const FLT To = 2 * PI * sqrt(ao / 6 / fo);	// Oscillation period
const FLT vo = sqrt(6 * fo * ao);	// vo = a*omega_0		// Long-wave velocity
const FLT Bo = 2 * sqrt(6 * fo / ao);		// Critical friction
//-----------------------------------------------------------------------------------

void Run2D_Demo(const int iter, const int rank)
{
    const FLT a0	 = 1.*ao; // 0.95*ao;
         LONG n1	 = 1000;			// number of particles in a single x-row    было 50, затем 1000
         LONG n2	 = 1000;			// number of particles in a single y-row 1
	const LONG n_div = 10;           // number of particles              // было 10
	const FLT dt	 = 0.5	* To / 100;	// time step for computation
	const FLT v0     = 0.01*vo;      //было 0.1*vo,
	const FLT a_cut  = 1.25 * ao;
	const FLT s_max  = 200*round(To/dt);		// max number of calculation steps
	      int ds_a3r = 100;
            LONG n0  = n1*n2 + 1000;
//--------------------------------------------------------

    FLT  Temperature = 0;
    FLT *pTemp = &Temperature;
    Timer timer;
    srand(time(0));

//  -----   Initial conditions   -------------------------------
    Atom2D* as0 = new Atom2D[n0];	// array containing particles
    Box2D box  = Create_triangular_lattice(as0, 0, n1, n2, n0, a0, ao, v0, a_cut, fo, 1, dt, n_div);
    LONG count_n = 0;
    for (Atom2D* i = as0; i!= as0+n0; i++)  if (i->real != 0)	count_n++;
    const LONG n = count_n;//
    Atom2D* as = new Atom2D[n];	// array containing particles
    elimination(as0, as, n0, n);



// -------------------------------------------------------------
    fstream clear_file("Results/energy" + IntToString_2(iter) + ".txt", ios::out);
    clear_file.close();

    double Ex0;
    double Ey0;

    for (LONG s1 = 1; s1 <= s_max; s1++)
    {

        if (s1 == 1)
        {
            Ex0 = 0;
            Ey0 = 0;
        }
        if (s1 == 2)
        {
            Ex0 = getEx0();
            Ey0 = getEy0();
        }

        //std::cout << "MEOW" << std::endl;

        RunBoxPeriodic_no_3NL(as, n, dt, ao, a_cut, fo, box, pTemp,s1, iter, Ex0, Ey0, To, n1, n2); // Fast 2D simulation (uses space) + periodic boundaries; does not use 3rd Newton Law


        if (s1 == 1 || s1 % ds_a3r == 0)
        {
            char file_name[10];
            sprintf(file_name, "a%08u.a3r", s1);
           //Save_A3R(file_name, as, n, ao / 2);
        }

 //       if (s1 == 1 || s1 % 100 == 0)      cout << s1 << "\t" << flush;                      //вывод пошагово
       if (rank==0&&( s1 == 1 || s1 % 10 == 0))      cout << "iter: " << iter << " " << s1 * dt / To << " To" << endl;                      //вывод пошагово

    }
    delete [] as;

    FLT time = timer.GetTime();
if(rank==0){
    char file_name1[21];
    sprintf(file_name1, "calculation-time.txt");
    FILE* fv_BB  = fopen(file_name1,"a");
    fprintf(fv_BB, "%s%f%s", "time per step per particle [nano seconds] = ", 10E9*time/(s_max * n), " \t");
    fprintf(fv_BB, "%s", "\n");
    fclose(fv_BB);

	cout << "\n\n";
	cout << "Time of calculation  = " << time << " s\n";
	cout << "Time for single step = " << 1000 * time / s_max << " ms\n";
}
}
//-------------------------------------------------------------------------------------------

void elimination(Atom2D* as_0, Atom2D* as, LONG n_0, LONG n)             //elimination - устранение, исключение
{
		Vect2D v_sr = VECT2D_0;

		Atom2D* j = as;
		Atom2D* j_end;
		LONG num_par = 0;

        for (Atom2D* i = as_0; i != as_0 + n_0; i++)
		{
             if (i->real > 0)
			 {
				 j->r = i->r;
				 j->v = i->v;
				 j++;
				 num_par++;
				 j_end = j;
			 }
		}
	delete [] as_0;
}
