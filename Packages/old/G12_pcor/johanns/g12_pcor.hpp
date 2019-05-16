#ifndef __CLAS6_RUN_PERIODS_G12_PCOR_HPP__
#define __CLAS6_RUN_PERIODS_G12_PCOR_HPP__

#include <cmath>
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace clas6
{
namespace g12 {

using std::ifstream;
using std::fmod;
using std::string;
using std::vector;

class MomentumCorrection
{
  private:
    std::map<int, vector< vector<float> > > pcor_map;

    static const int proton_id = 14;
    static const int piplus_id = 8;
    static const int piminus_id = 9;
    static const int kplus_id = 11;
    static const int kminus_id = 12;

  public:
    MomentumCorrection(const string& parms_dir = "/group/clas/parms")
    {
        pcor_map[proton_id] = vector<vector<float> >(6);
        pcor_map[piplus_id] = vector<vector<float> >(6);
        pcor_map[piminus_id] = vector<vector<float> >(6);
        pcor_map[kplus_id] = vector<vector<float> >(6);
        pcor_map[kminus_id] = vector<vector<float> >(6);


        string infile = parms_dir+"/pcor/g12/pcor.txt";
        ifstream fin(infile);

        /// ignore first line
        fin.ignore('\n');

        string partid;
        int sec;
        float p1;
        float p0;

        while (fin >> partid >> sec >> p1 >> p0)
        {
            int id = 0;

            if (partid == "p")
            {
                id = proton_id;
            }
            else if (partid == "pi+")
            {
                id = piplus_id;
            }
            else if (partid == "pi-")
            {
                id = piminus_id;
            }
            else if (partid == "k+")
            {
                id = kplus_id;
            }
            else if (partid == "k-")
            {
                id = kminus_id;
            }

            pcor_map[id][sec].push_back(p1);
            pcor_map[id][sec].push_back(p0);
        }
    }

    inline
    float pcor(const float& p, const float& phi, const int& part_id)
    {
        /// adjust phi so it goes from -30 to 30
        /// sector number is from 0 to 5
        float phi_shifted = fmod((phi+30.),360);
        int sec = int(phi_shifted / 60.);
        phi_shifted = fmod(phi_shifted,60) - 30.;

        float pcorrection = (pcor_map[part_id][sec][0] * phi_shifted) + pcor_map[part_id][sec][1];

        /// set the new total momentum without changing the
        /// direction of the three-vector.
        return (p + pcorrection);
    }

  private:
};



} /* namespace clas6::g12 */
} /* namespace clas6 */

#endif /* __CLAS6_RUN_PERIODS_G12_PCOR_HPP__ */
