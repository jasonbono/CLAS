#include <cmath>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <TLorentzVector.h>
#include <TMath.h>

using std::ifstream;
using std::fmod;
using std::string;
using std::vector;

int proton_id = 14;
int piplus_id = 8;
int piminus_id = 9;
int kplus_id = 11;
int kminus_id = 12;

float proton_mass = 0.938272;
float pion_mass = 0.139570;
float kaon_mass = 0.493667;

void read_pcor(double pcor_map[5][6][2]) 
{ 

ifstream fin("./pcor.txt");
if ( fin.good() ) cout << "File Exists and Found." << endl;

string partid;
int sec;
double p1;
double p0;

////Using a temporary PID scheme since I cannot get map of vectors of vectors to compile right in root
////SO I switch to arrays and redfine the PID as PID_M
//// proton = 0
//// KPlus = 1
//// KMinus = 2
//// PiPlus = 3
//// PiMinus = 4

while (fin >> partid >> sec >> p1 >> p0)
{
    //fin >> partid >> sec >> p1 >> p0;
    cout << partid << " : " << sec << " : " << p1 << " : " << p0 << endl;
    int id = 100;

    if (partid == "p")
    {
        id = 0;
    }
    else if (partid == "k+")
    {
        id = 1;
    }
    else if (partid == "k-")
    {
        id = 2;
    }
    else if (partid == "pi+")
    {
        id = 3;
    }
    else if (partid == "pi-")
    {
        id = 4;
    }
    pcor_map[id][sec][0]=p0;
    pcor_map[id][sec][1]=p1;
    cout << "id : sec : p0 : p1 ::: " << id << ":" << sec << ":" << p0 << ":" << p1 << endl;
    cout << "___" << pcor_map[id][sec][0] << "___" << pcor_map[id][sec][1] << endl;
}

cout << "Done reading pcor....." << endl;

//for (int ii = 0; ii < 5; ii++)
//for (int jj = 0; jj < 6; jj++)
//for (int kk = 0; kk < 2; kk++)
//{
//cout << "pcor_map_element: " << ii << ":" << jj << ":" << kk << " ::: " << pcor_map[ii][jj][kk] << endl;
//}

}

float pcor( float& p, float& phi, int& mpart_id)
    {
     ////Not sure about the Relationship between the pcor phi and sectors and data phi and sectors. 
     ////There is an ambiguity in the two in my head. So accounting for both cases
        
        ////// W A R N I N G :: Use only one method to define the angle phi from your data //////
        //Redifining Phi - Method 1 -- UnComment this if you want phi between {0,360} from data and the sector 1 center to be zero
        phi=phi+180.;
        //Redifining phi - Method2  -- UnComment this if you want phi between {-180,180} and the sector 1 center to be zero
        //if ( phi < -30. ) phi = 360 + phi;
        
        float phi_shifted = fmod((phi+30.),360);
        int sec = int(phi_shifted / 60.);
        phi_shifted = fmod(phi_shifted,60) - 30.;
        //cout << "pcor_array[" << mpart_id << "][" << sec << "][0] : " << pcor_array[mpart_id][sec][0] << endl;
        double pcorrection = (pcor_array[mpart_id][sec][1] * phi_shifted) + pcor_array[mpart_id][sec][0];
        return ( p + (float)pcorrection / 1000. );
    }

TLorentzVector Calc_new_fourVec( TLorentzVector In_fourVec, int PID_M )
{
    float ptheta = In_fourVec.Vect().Theta();
    float pphi = In_fourVec.Vect().Phi();
    //cout << "theta:phi :: " << ptheta << " :: " << pphi << endl;
    float pmag = fabs(pcor((In_fourVec.Vect().Mag()), pphi*57.2957795, PID_M));
    float pX = pmag * TMath::Sin(ptheta) * TMath::Cos(pphi);
    float pY = pmag * TMath::Sin(ptheta) * TMath::Sin(pphi);
    float pZ = pmag * TMath::Cos(ptheta);
    
    if ( PID_M == 0 ) float PID_mass = proton_mass;
    else if ( (PID_M == 1) || (PID_M == 2) ) float PID_mass = kaon_mass;
    else if ( (PID_M == 3) || (PID_M == 4) ) float PID_mass = pion_mass;
          
    float pE = sqrt( PID_mass*PID_mass + pmag*pmag );

    TLorentzVector Out_fourVec;
    Out_fourVec.SetPxPyPzE( pX, pY, pZ, pE);

    //cout << PID_M << " :: " << Out_fourVec.Mag() << endl;
    return Out_fourVec; 
}
