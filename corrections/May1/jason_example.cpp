#include <cmath>
#include <iostream>
#include <string>

#include "g12_ecor.hpp"
#include "g12_pcor.hpp"


using namespace std;


int main()
{
	
	/// Initialization of Momentum Correction Parameters
    string parms_dir = ".";  
    clog << "Reading in momentum correction parameters...\n";
    clas::g12::MomentumCorrection pcor(parms_dir);

    /// loop over events
    {
        /// example event with typical numbers
        double run = 56363;
        double ebeam = 1.2;

        /// Beam energy correction /////////////////////////////////////
        double new_ebeam = clas::g12::corrected_beam_energy(run, ebeam);
        /// ////////////////////////////////////////////////////////////


        double id = 14; // proton (geant 3 ID codes)
        double p = 1.1; // total momentum
        double px = 0.3;
        double py = 0.4;

        double pz = sqrt(p*p - px*px - py*py);
        double phi = atan2(py,px);
        double theta = acos(pz/p);

        /// Momentum correction ////////////////////////////////////////
        double new_p = p + pcor.pcor(phi,id);
        /// ////////////////////////////////////////////////////////////

        double new_px = (new_p / p) * px;
        double new_py = (new_p / p) * py;
        double new_pz = (new_p / p) * pz;

        double new_phi = atan2(new_py,new_px);
        double new_theta = acos(new_pz/new_p);

        cout << "Measured:\n"
         << "  run: " << run << endl
         << "  ebeam: " << ebeam << endl
         << "  p (px,py,pz): " << p << ", ("
         << px << "," << py << "," << pz << ")\n"
         << "  (theta,phi): (" << theta << "," << phi << ")\n"
         << "After Correction:\n"
         << "  ebeam: " << new_ebeam << endl
         << "  p (px,py,pz): " << new_p << ", ("
         << new_px << "," << new_py << "," << new_pz << ")\n"
         << "  (new_theta,new_phi): (" << new_theta << "," << new_phi << ")\n";

    }
}
