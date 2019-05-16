#include <csignal>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

#include "clas6/event.hpp"
#include "clas6/iarchive.hpp"
#include "clas6/run_periods.hpp"

#include "histogram.hpp"
#include "histogram/collection.hpp"

#include "clas6/kinfit.hpp"

#include "args.hpp"

using namespace std;
using namespace clas6;

namespace experiment = g12;
namespace cut = experiment::cut;
typedef histogram<1>::dim_desc_t desc_t;

int main(int argc, char** argv)
{
    // Begin command line option handler
    bool quiet = false;
    bool verbose = false;
    int max = 0;
    string outfile = "xi.hist.gz";
    vector<string> infiles;

    po::options_description arg_specific("Program specific options");
    arg_specific.add_options()
        ("max,m",
            po::value<int>(&max)->default_value(max),
            "maximum number of events to process.")
        ;

    po::variables_map vm = process_program_options(
        argc, argv,
        quiet,
        verbose,
        outfile,
        infiles,
        arg_specific );

    if (!quiet)
    {
        clog << "Max: " << max << endl;
    }
    // End command line option handler

    if (!quiet)
    {
        clog << "progress output:\n";
        clog << "total events / events in file / total files processed.\n";
    }

    histogram_collection hcol;

    string gp_kpkpx_str = "$\\gammaup \\mathrm{p} \\rightarrow \\mathrm{K}^+ \\mathrm{K}^+ X$";
    string gp_kpkpkm_mlambda_str = "$\\gammaup \\mathrm{p} \\rightarrow [\\Lambda] \\mathrm{K}^+ \\mathrm{K}^+ \\mathrm{K}^-$";
//    string gp_kpkpkm_msigma0_str = "$\\gammaup \\mathrm{p} \\rightarrow [\\Sigma^0] \\mathrm{K}^+ \\mathrm{K}^+ \\mathrm{K}^-$";

    desc_t mkpkp_m_dim {300, 0.6, 2.6, "MM($\\mathrm{K}^+\\mathrm{K}^+$) (GeV)"};
//    desc_t mkpkpkm_m_dim {300, 0., 1.7, "MM($\\mathrm{K}^+\\mathrm{K}^+\\mathrm{K}^-$) (GeV)"};
	desc_t mkpkppim_m_dim {300, 0., 1.7, "MM($\\mathrm{K}^+\\mathrm{K}^+\\mathrm{K}^-$) (GeV)"};  ///////////////////jb jan24
    histogram<1> hmkpkp_m ({mkpkp_m_dim}, gp_kpkpx_str);
    histogram<1> hmkpkpkm_m ({mkpkpkm_m_dim}, gp_kpkpx_str);
	histogram<1> hmkpkppim_m ({mkpkpkmpim_m_dim}, gp_kpkpx_str);   ///////////////////jb jan24
    hcol.append("hmkpkp_m", hmkpkp_m);
//   hcol.append("hmkpkpkm_m", hmkpkpkm_m);
	hcol.append("hmkpkppim_m", hmkpkppim_m);					  //////////////////jb jan24


    /// g p --> [Lambda] K+ K+ K-
    histogram<1> hkflambda_mkpkp_m ({mkpkp_m_dim}, gp_kpkpkm_mlambda_str);
    hcol.append("hkflambda_mkpkp_m", hkflambda_mkpkp_m);

    histogram<1> hkflambda_prob ({100}, {{-0.1,1.1}}, {"Kinfit Probability"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_chi2 ({100}, {{-0.1,1.6}}, {"Kinfit $\\chi^2 / \\mathrm{ND}f$"}, gp_kpkpkm_mlambda_str);
    hcol.append("hkflambda_prob",hkflambda_prob);
    hcol.append("hkflambda_chi2",hkflambda_chi2);

    histogram<1> hkflambda_pull_beam ({100}, {{-5,5}}, {"Pull ($E_\\mathrm{beam}$)"}, gp_kpkpkm_mlambda_str);
    hcol.append("hkflambda_pull_beam",hkflambda_pull_beam);

    histogram<1> hkflambda_pull0_kp0 ({100}, {{-5,5}}, {"Pull ($p$) (K$^+_\\mathrm{fast}$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_pull1_kp0 ({100}, {{-5,5}}, {"Pull ($\\lambda$) (K$^+_\\mathrm{fast}$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_pull2_kp0 ({100}, {{-5,5}}, {"Pull ($\\phi$) (K$^+_\\mathrm{fast}$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_pull0_kp1 ({100}, {{-5,5}}, {"Pull ($p$) (K$^+_\\mathrm{slow}$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_pull1_kp1 ({100}, {{-5,5}}, {"Pull ($\\lambda$) (K$^+_\\mathrm{slow}$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_pull2_kp1 ({100}, {{-5,5}}, {"Pull ($\\phi$) (K$^+_\\mathrm{slow}$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_pull0_km0 ({100}, {{-5,5}}, {"Pull ($p$) (K$^-$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_pull1_km0 ({100}, {{-5,5}}, {"Pull ($\\lambda$) (K$^-$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_pull2_km0 ({100}, {{-5,5}}, {"Pull ($\\phi$) (K$^-$)"}, gp_kpkpkm_mlambda_str);
    hcol.append("hkflambda_pull0_kp0",hkflambda_pull0_kp0);
    hcol.append("hkflambda_pull1_kp0",hkflambda_pull1_kp0);
    hcol.append("hkflambda_pull2_kp0",hkflambda_pull2_kp0);
    hcol.append("hkflambda_pull0_kp1",hkflambda_pull0_kp1);
    hcol.append("hkflambda_pull1_kp1",hkflambda_pull1_kp1);
    hcol.append("hkflambda_pull2_kp1",hkflambda_pull2_kp1);
    hcol.append("hkflambda_pull0_km0",hkflambda_pull0_km0);
    hcol.append("hkflambda_pull1_km0",hkflambda_pull1_km0);
    hcol.append("hkflambda_pull2_km0",hkflambda_pull2_km0);

    histogram<1> hkflambda_err0_lambda ({100}, {{-0.05,0.15}}, {"Error ($p$) ($\\Lambda$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_err1_lambda ({100}, {{-0.05,0.15}}, {"Error ($\\lambda$) ($\\Lambda$)"}, gp_kpkpkm_mlambda_str);
    histogram<1> hkflambda_err2_lambda ({100}, {{-0.05,0.15}}, {"Error ($\\phi$) ($\\Lambda$)"}, gp_kpkpkm_mlambda_str);
    hcol.append("hkflambda_err0_lambda",hkflambda_err0_lambda);
    hcol.append("hkflambda_err1_lambda",hkflambda_err1_lambda);
    hcol.append("hkflambda_err2_lambda",hkflambda_err2_lambda);

    /// g p --> [Sigma0] K+ K+ K-
    histogram<1> hkfsigma0_mkpkp_m ({mkpkp_m_dim}, gp_kpkpkm_msigma0_str);
    hcol.append("hkfsigma0_mkpkp_m", hkfsigma0_mkpkp_m);

    histogram<1> hkfsigma0_prob ({100}, {{-0.1,1.1}}, {"Kinfit Probability"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_chi2 ({100}, {{-0.1,1.6}}, {"Kinfit $\\chi^2 / \\mathrm{ND}f$"}, gp_kpkpkm_msigma0_str);
    hcol.append("hkfsigma0_prob",hkfsigma0_prob);
    hcol.append("hkfsigma0_chi2",hkfsigma0_chi2);

    histogram<1> hkfsigma0_pull_beam ({100}, {{-5,5}}, {"Pull ($E_\\mathrm{beam}$)"}, gp_kpkpkm_msigma0_str);
    hcol.append("hkfsigma0_pull_beam",hkfsigma0_pull_beam);

    histogram<1> hkfsigma0_pull0_kp0 ({100}, {{-5,5}}, {"Pull ($p$) (K$^+_\\mathrm{fast}$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_pull1_kp0 ({100}, {{-5,5}}, {"Pull ($\\lambda$) (K$^+_\\mathrm{fast}$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_pull2_kp0 ({100}, {{-5,5}}, {"Pull ($\\phi$) (K$^+_\\mathrm{fast}$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_pull0_kp1 ({100}, {{-5,5}}, {"Pull ($p$) (K$^+_\\mathrm{slow}$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_pull1_kp1 ({100}, {{-5,5}}, {"Pull ($\\lambda$) (K$^+_\\mathrm{slow}$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_pull2_kp1 ({100}, {{-5,5}}, {"Pull ($\\phi$) (K$^+_\\mathrm{slow}$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_pull0_km0 ({100}, {{-5,5}}, {"Pull ($p$) (K$^-$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_pull1_km0 ({100}, {{-5,5}}, {"Pull ($\\lambda$) (K$^-$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_pull2_km0 ({100}, {{-5,5}}, {"Pull ($\\phi$) (K$^-$)"}, gp_kpkpkm_msigma0_str);
    hcol.append("hkfsigma0_pull0_kp0",hkfsigma0_pull0_kp0);
    hcol.append("hkfsigma0_pull1_kp0",hkfsigma0_pull1_kp0);
    hcol.append("hkfsigma0_pull2_kp0",hkfsigma0_pull2_kp0);
    hcol.append("hkfsigma0_pull0_kp1",hkfsigma0_pull0_kp1);
    hcol.append("hkfsigma0_pull1_kp1",hkfsigma0_pull1_kp1);
    hcol.append("hkfsigma0_pull2_kp1",hkfsigma0_pull2_kp1);
    hcol.append("hkfsigma0_pull0_km0",hkfsigma0_pull0_km0);
    hcol.append("hkfsigma0_pull1_km0",hkfsigma0_pull1_km0);
    hcol.append("hkfsigma0_pull2_km0",hkfsigma0_pull2_km0);

    histogram<1> hkfsigma0_err0_sigma0 ({100}, {{-0.05,0.15}}, {"Error ($p$) ($\\Sigma^0$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_err1_sigma0 ({100}, {{-0.05,0.15}}, {"Error ($\\lambda$) ($\\Sigma^0$)"}, gp_kpkpkm_msigma0_str);
    histogram<1> hkfsigma0_err2_sigma0 ({100}, {{-0.05,0.15}}, {"Error ($\\phi$) ($\\Sigma^0$)"}, gp_kpkpkm_msigma0_str);
    hcol.append("hkfsigma0_err0_sigma0",hkfsigma0_err0_sigma0);
    hcol.append("hkfsigma0_err1_sigma0",hkfsigma0_err1_sigma0);
    hcol.append("hkfsigma0_err2_sigma0",hkfsigma0_err2_sigma0);


    double c = cons::light_speed;

    float target_z = experiment::target.z();
    lorentz_vector target(pdg::mass::proton,0.,0.,0.);

    tag_hit tag;
    lorentz_vector beam;

    charged_particle cp_kp0, cp_kp1, cp_km0, cp_pim;    //jb jan24 added cp_pim
    lorentz_vector kp0, kp1, km0, pim;  //jb jan24 added pim
    lorentz_vector mkpkp, mkpkpkm, mkpkppim;  //jb jan24 added mkpkppim
    lorentz_vector kfkp0, kfkp1, kfkm0, kfpim;  //jb jan24 added kfpim
    lorentz_vector kflambda_mkpkp, kfsigma0_mkpkp, kfcascadem_mkpkp, kflambda_mkpkppim; // jb jan24 added kfcascadem_mkpkp & kflambda_mkmkpim

    size_t infile_count = 0;
    size_t event_count = 0;
    size_t eventsinfile_count;

    for (int i=0; i<infiles.size(); i++)
    {
        if (max && event_count >= max)
        {
            break;
        }
        eventsinfile_count = 0;
        event evt;

        iarchive ia(infiles[i]);
        infile_count++;

        while (ia >> evt && (!max || event_count < max))
        {
            try
            {
// Begin Process Event

/// assume PID has already run on these files
/// get the tagger hit and set the beam energy
/// they are usually the product of the filter-kaon program
tag = evt.tag()[0];
beam = lorentz_vector(tag.energy(), 0., 0., tag.energy());

if (evt.n(pid::kplus) > 1)  //////////////////////////////jb  probably dont need this if statment
{
    /// g p --> K+ K+ X
    cp_kp0 = evt.charged_particle(pid::kplus, 0);
    cp_kp1 = evt.charged_particle(pid::kplus, 1);
//	cp_pim = evt.charged_particle(pid::piminus, 0); 	/////////////////jb jan24

    kp0 = cp_kp0.four_momentum();
    kp1 = cp_kp1.four_momentum();
//	pim = cp_pim.four_momentum(); 					 //////////////////jb jan24

    mkpkp = beam + target - kp0 - kp1;
//	mkpkppim = beam + target - kp0 - kp1 - pim;      //////////////////jb jan24

    hmkpkp_m.fill(mkpkp.invariant());
//	hmkpkppim_m.fill(mkpkppim.invariant());			//////////////////jb jan24
	



//-----------------------------------JB JAN24 NOW WILL BE MODIFYING FROM KM TO PIM--------------------------
    //if (evt.n(pid::kminus) > 0)
	if (evt.n(pid::piminus) > 0)            //jb jan24 replaced the kminus with piminus
    {		

		/// g p --> K+ K+ Pi- X  //jb
 

       	cp_pim = evt.charged_particle(pid::pimminus, 0);
        pim = cp_pim.four_momentum();

        mkpkppim = beam + target - kp0 - kp1 - pim;
        hmkpkppim_m.fill(mkpkppim.invariant());

        // add phi cut

        double dm = 0.4999 * (pdg::mass::lambda + pdg::mass::sigma0);   /////////figgure out what value to make this
        vector<charged_particle> cp_kpkppim { cp_kp0, cp_kp1, cp_pim };

        if (abs(mkpkppim.invariant() - pdg::mass::lambda) < dm)   //use lambda ???? 
        {
            /// g p --> [Lambda] K+ K+ K- -------------->>>>>>>> changed to  g p --> [Lambda] K+ K+ Pi- 
            kinfit_output_t kfit_lambda = kinematic_fit(tag, pdg::mass::proton, cp_kpkppim, pdg::mass::lambda, "g12");  //jb jan24

            kfkp0 = kfit_lambda.parts[0];
            kfkp1 = kfit_lambda.parts[1];
            kfpim = kfit_lambda.parts[2];  ///////////////jb jan24

            hkflambda_prob.fill(kfit_lambda.prob);
            hkflambda_chi2.fill(kfit_lambda.chi2 / kfit_lambda.ndf);

            hkflambda_pull_beam.fill(kfit_lambda.pull_beam);

            hkflambda_pull0_kp0.fill(kfit_lambda.pulls[0][0]);
            hkflambda_pull1_kp0.fill(kfit_lambda.pulls[0][1]);
            hkflambda_pull2_kp0.fill(kfit_lambda.pulls[0][2]);
            hkflambda_pull0_kp1.fill(kfit_lambda.pulls[1][0]);
            hkflambda_pull1_kp1.fill(kfit_lambda.pulls[1][1]);
            hkflambda_pull2_kp1.fill(kfit_lambda.pulls[1][2]);
            hkflambda_pull0_pim.fill(kfit_lambda.pulls[2][0]);  /////jb jan24
            hkflambda_pull1_pim.fill(kfit_lambda.pulls[2][1]);  /////jb jan24
            hkflambda_pull2_pim.fill(kfit_lambda.pulls[2][2]);  /////jb jan24

            hkflambda_err0_lambda.fill(kfit_lambda.missing_error[0]);
            hkflambda_err1_lambda.fill(kfit_lambda.missing_error[1]);
            hkflambda_err2_lambda.fill(kfit_lambda.missing_error[2]);  

            if (kfit_lambda.prob > 0.1)
            {
                kflambda_mkpkp = kfit_lambda.beam + target - kfkp0 - kfkp1;
                hkflambda_mkpkp_m.fill(kflambda_mkpkp.invariant());
            }
        }



// will take out the below if statment for now
/* 
       if (abs(mkpkpkm.invariant() - pdg::mass::sigma0) < dm)
        {
            /// g p --> [Sigma0] K+ K+ K-
            kinfit_output_t kfit_sigma0 = kinematic_fit(tag, pdg::mass::proton, cp_kpkpkm, pdg::mass::sigma0, "g12");

            kfkp0 = kfit_sigma0.parts[0];
            kfkp1 = kfit_sigma0.parts[1];
            kfkm0 = kfit_sigma0.parts[2];

            hkfsigma0_prob.fill(kfit_sigma0.prob);
            hkfsigma0_chi2.fill(kfit_sigma0.chi2 / kfit_sigma0.ndf);

            hkfsigma0_pull_beam.fill(kfit_sigma0.pull_beam);

            hkfsigma0_pull0_kp0.fill(kfit_sigma0.pulls[0][0]);
            hkfsigma0_pull1_kp0.fill(kfit_sigma0.pulls[0][1]);
            hkfsigma0_pull2_kp0.fill(kfit_sigma0.pulls[0][2]);
            hkfsigma0_pull0_kp1.fill(kfit_sigma0.pulls[1][0]);
            hkfsigma0_pull1_kp1.fill(kfit_sigma0.pulls[1][1]);
            hkfsigma0_pull2_kp1.fill(kfit_sigma0.pulls[1][2]);
            hkfsigma0_pull0_km0.fill(kfit_sigma0.pulls[2][0]);
            hkfsigma0_pull1_km0.fill(kfit_sigma0.pulls[2][1]);
            hkfsigma0_pull2_km0.fill(kfit_sigma0.pulls[2][2]);

            hkfsigma0_err0_sigma0.fill(kfit_sigma0.missing_error[0]);
            hkfsigma0_err1_sigma0.fill(kfit_sigma0.missing_error[1]);
            hkfsigma0_err2_sigma0.fill(kfit_sigma0.missing_error[2]);

            if (kfit_sigma0.prob > 0.1)
            {
                kfsigma0_mkpkp = kfit_sigma0.beam + target - kfkp0 - kfkp1;
                hkfsigma0_mkpkp_m.fill(kfsigma0_mkpkp.invariant());
            }
        }
*/


    }
}


// End Process Event
            }
            catch (logic_error& e)
            {
                if (!quiet)
                {
                    clog << "Exception caught: " << e.what() << endl;
                }
            }
            eventsinfile_count++;

            if (!(++event_count%1000))
            {
                if (!quiet)
                {
                    clog << event_count
                        << "    " << eventsinfile_count
                        << "    " << infile_count
                        << "    \r";
                }
            }

        } /* end event loop */
    }
    if (!quiet)
    {
        clog << event_count
            << "    " << eventsinfile_count
            << "    " << infile_count
            << "    " << endl;
    }


    {
        clog << "writing histograms to file: " << outfile << endl;
        hcol.save_to_file(outfile);
    }

    return 0;
}
