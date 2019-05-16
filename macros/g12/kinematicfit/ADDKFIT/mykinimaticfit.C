// using https://jlabsvn.jlab.org/svnroot/clas/users/goetz/clas_event_tree/include/clas6/kinfit.hpp






#ifndef __CLAS6_KINFIT_HPP__
#define __CLAS6_KINFIT_HPP__

#include <array>
#include <map>
#include <string>
#include <vector>

#include "particle.hpp"
#include "pdg.hpp"

#include "clas6/algorithm.hpp"
#include "clas6/detail/types.hpp"

#include "Kstream.h"

namespace clas6
{





kinfit_output_t kinematic_fit(
	const tag_hit& tag,
	const double& target_mass,
	const std::vector<charged_particle>& input_particles,
	const std::vector<neutral_particle>& input_neutral_particles,
	const double& missing_mass,
	const std::string& experiment_name /* = "g12" */,
	double rscale = -1,
	double resscale = -1 )
	{



	/// kinfit uses these names for particles
	    static std::map<int, std::string> name_map;
	    if (name_map.empty())
	    {
	        name_map.insert(std::make_pair(1,"g"));
	        name_map.insert(std::make_pair(2,"e-"));
	        name_map.insert(std::make_pair(3,"e+"));
	        name_map.insert(std::make_pair(8,"pi+"));
	        name_map.insert(std::make_pair(9,"pi-"));
	        name_map.insert(std::make_pair(11,"k+"));
	        name_map.insert(std::make_pair(12,"k-"));
	        name_map.insert(std::make_pair(13,"n"));
	        name_map.insert(std::make_pair(14,"p"));
	    }





	// number of particles in fit
    int nparts = input_particles.size();

    output.vertex = intersect(input_particles);

    /// convert four_vector, vertexes, and covariance
    /// matrices to ROOT's format
    std::vector<TLorentzVector> input_momenta(nparts);
    std::vector<TVector3> input_vertexes(nparts);
    std::vector<std::string> particle_names(nparts);
    for (int i=0; i<nparts; i++)
    {
        input_momenta[i].SetXYZT(
            input_particles[i].four_momentum().x(),
            input_particles[i].four_momentum().y(),
            input_particles[i].four_momentum().z(),
            input_particles[i].four_momentum().t() );
        input_vertexes[i].SetXYZ(output.vertex.x(), output.vertex.y(), output.vertex.z());
        particle_names[i] = name_map[input_particles[i].id()];
    }















Kstream fit;
fit.StringNames(particle_names);
fit.FitInput(tag.energy(), input_momenta, covmat, target_mass);

















} /* namespace clas6 */

#endif /* __CLAS6_KINFIT_HPP__ */