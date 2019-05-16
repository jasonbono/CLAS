#include <cmath>
#include <iostream>
#include <string>

#include "g12_ecor.hpp"
#include "g12_pcor.hpp"


using namespace std;


int main()
{
    string parms_dir = ".";


    /// Initialization of Momentum Correction Parameters
    clog << "Reading in momentum correction parameters...\n";
    clas::g12::MomentumCorrection pcor(parms_dir);

    /// loop over events
    {
        /// example event with typical numbers
        float run = 56363;
        float ebeam = 1.2;

        /// Beam energy correction /////////////////////////////////////
        float new_ebeam = clas::g12::corrected_beam_energy(run, ebeam);
        /// ////////////////////////////////////////////////////////////


        float id = 14; // proton (geant 3 ID codes)
        float p = 1.1; // total momentum
        float px = 0.3;
        float py = 0.4;

        float pz = sqrt(p*p - px*px - py*py);
        float phi = atan2(py,px);
        float theta = acos(pz/p);

        /// Momentum correction ////////////////////////////////////////
        float new_p = p + pcor.pcor(phi,id);
        /// ////////////////////////////////////////////////////////////

        float new_px = (new_p / p) * px;
        float new_py = (new_p / p) * py;
        float new_pz = (new_p / p) * pz;

        float new_phi = atan2(new_py,new_px);
        float new_theta = acos(new_pz/new_p);

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
