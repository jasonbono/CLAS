#ifndef __KINFIT_HPP__
#define __KINFIT_HPP__

#include <csignal>
#include <iostream>
#include <unistd.h>

extern "C" {
    #include <ntypes.h>
    #include <bostypes.h>
    #include <clas_cern.h>
    #include <particleType.h>
    #include <kinematics.h>
    #include <pdgutil.h>
    #include <pid.h>
    #include <dataIO.h>
    #include <itape.h>
    #include <vertex.h>
    #include <trk.h>
    #include <makebanks.h>
}
//#include <array>
#include <map>
#include <string>
#include <vector>
#include <lorentz.h>
#include <cmath>

#include "Vec.h"
#include "lorentz.h"
#include "pputil.h"
#include "clasEvent.h"
#include "Kstream.h"

typedef struct
{
    double prob;
    double chi2;
    int ndf;

    double pull_beam;
    std::vector<std::vector<double> > pulls;
    std::vector<double> missing_error;

    fourVec beam;
    std::vector<fourVec> parts;

} kinfit_output_t;

kinfit_output_t kinematic_fit(
    const fourVec& tag,
    const double& target_mass,
    std::vector<clasParticle>& input_particles,
    const double& missing_mass,
    const std::string& experiment_name,
    const threeVec vertex)
{
  double rscale = -1;
  double resscale = -1; 

    /// kinfit uses these names for particles
    static std::map<int, std::string> name_map;
    if (name_map.empty())
    {
        name_map.insert(std::make_pair(1,"gamma"));
        name_map.insert(std::make_pair(2,"e-"));
        name_map.insert(std::make_pair(3,"e+"));
        name_map.insert(std::make_pair(8,"pi+"));
        name_map.insert(std::make_pair(9,"pi-"));
        name_map.insert(std::make_pair(11,"k+"));
        name_map.insert(std::make_pair(12,"k-"));
        name_map.insert(std::make_pair(13,"n"));
        name_map.insert(std::make_pair(14,"p"));
    }
    /// number of particles in fit
    int nparts = input_particles.size();
    
    /// convert four_vector, vertexes, and covariance
    /// matrices to ROOT's format
    std::vector<TLorentzVector> input_momenta(nparts);
    std::vector<TVector3> input_vertexes(nparts);
    std::vector<std::string> particle_names(nparts);
    for (int i=0; i<nparts; i++)
    {
        input_momenta[i].SetXYZT(
            input_particles[i].p().x(),
            input_particles[i].p().y(),
            input_particles[i].p().z(),
            input_particles[i].p().t() );
        input_vertexes[i].SetXYZ(vertex.x(), vertex.y(), vertex.z());
        particle_names[i] = name_map[input_particles[i].pid()];
    }

    /// some kinfit options
    bool multi = true;
    bool mc = false;
    std::vector<bool> set(nparts, false);

    /// beam four momentum and target mass
    fourVec beam = tag;

    /// covariance matrices for each particle
    int covmat_dim = 3*nparts + 1;
    /// initial Covariance Matrix
    TMatrixD covmat_init(covmat_dim, covmat_dim);
    for (int i=0; i<nparts; i++)
    {
        matrix<double> cm = input_particles[i].getCovMatrix();
        covmat_init(3*i+1,3*i+1) =   cm.el(0,0) * pow(input_particles[i].p().lenSq(),2);
        covmat_init(3*i+2,3*i+2) =   cm.el(1,1);
        covmat_init(3*i+3,3*i+3) =   cm.el(2,2);
        covmat_init(3*i+1,3*i+2) = - cm.el(0,1) * double(input_particles[i].Q()) * input_particles[i].p().lenSq();
        covmat_init(3*i+2,3*i+1) = - cm.el(1,0) * double(input_particles[i].Q()) * input_particles[i].p().lenSq();
        covmat_init(3*i+1,3*i+3) = - cm.el(0,2) * double(input_particles[i].Q()) * input_particles[i].p().lenSq();
        covmat_init(3*i+3,3*i+1) = - cm.el(2,0) * double(input_particles[i].Q()) * input_particles[i].p().lenSq();
        covmat_init(3*i+2,3*i+3) =   cm.el(1,2);
        covmat_init(3*i+3,3*i+2) =   cm.el(2,1);
    }


    /// Covariance Matrix which will be used as input for fit procedure
    TMatrixD covmat(covmat_dim, covmat_dim);
    covmat = CorrectCLAS_V(
        covmat_init,
        particle_names,
        input_momenta,
        input_vertexes,
        multi,
        mc,
        *const_cast<std::string*>(&experiment_name),
        rscale,
        resscale);

    /// setup the fit
    Kstream fit;
    fit.StringNames(particle_names);
    fit.FitInput(tag.t(), input_momenta, covmat, target_mass);

    /// do the fit.
    fit.Fit(missing_mass);
    std::vector<TLorentzVector> output_momenta(nparts);
    for (int i=0; i<nparts; i++)
    {
        output_momenta[i] = fit.FitP4(i);
    }

    /// put the output into a struct and return
    kinfit_output_t output;

    output.prob = fit.Prob();
    output.chi2 = fit.Chi2();
    output.ndf = fit.Ndf();

    output.pull_beam = fit.GetPull(0);

    output.pulls.resize(nparts);
    for (int p=0; p<nparts; p++)
    {
        output.pulls[p].resize(3);
        for (int i=0; i<3; i++)
        {
            output.pulls[p][i] = fit.GetPull(3*p + 1 + i);
        }
    }

    output.missing_error.resize(3);
    for (int i=0; i<3; i++)
    {
        output.missing_error[i] = fit.GetMissingError(i);
    }
    threeVec newbeam_m(0., 0., fit.FitPhotonEnergy());
    fourVec newbeam(fit.FitPhotonEnergy(), newbeam_m);
    output.beam = newbeam;

    output.parts.resize(nparts);
    for (int i=0; i<nparts; i++)
    {
      threeVec temp_m(output_momenta[i].X(),
            output_momenta[i].Y(),
            output_momenta[i].Z() );
        output.parts[i] = fourVec(
            output_momenta[i].T(),
            temp_m);
    }

    return output;
}

#endif /** __KINFIT_HPP__ **/
