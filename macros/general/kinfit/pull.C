
#include "kinfit.hpp" //at the beginning of the program

//after general analysis cuts and apply eloss
vector<clasParticle> cp_ppippimg {p, pip, pim};
kinfit_output_t kfit_ppippimg = kinematic_fit(beam, PROTON_MASS,
cp_ppippimg, eta_mass, "g12", vert);

//fill parameters with new fitted values
fourVec kfp = kfit_ppippimg.parts[0];
fourVec kfpip = kfit_ppippimg.parts[1];
fourVec kfpim = kfit_ppippimg.parts[2];
fourVec kfbeam = kfit_ppippimg.beam;

double kf_prob = kfit_ppippimg.prob;
double kf_chi2 = kfit_ppippimg.chi2;
double kf_pull_beam = kfit_ppippimg.pull_beam;



//now jasons version

//after general analysis cuts and apply eloss
vector<clasParticle> cp_kpkppim {kp1, kp2, pim};
kinfit_output_t kfit_kpkppim = kinematic_fit(beam, PROTON_MASS,
cp_kpkppim, LAMBDA_MASS, "g12", Vert);

//fill parameters with new fitted values
fourVec kfp = kfit_kpkppim.parts[0];
fourVec kfpip = kfit_kpkppim.parts[1];
fourVec kfpim = kfit_kpkppim.parts[2];
fourVec kfbeam = kfit_kpkppim.beam;

double kf_prob = kfit_kpkppim.prob;
double kf_chi2 = kfit_kpkppim.chi2;
double kf_pull_beam = kfit_kpkppim.pull_beam;
