// using https://jlabsvn.jlab.org/svnroot/clas/users/goetz/clas_event_tree/kinfit/Kstream.C & Kstream.h









// construct the Kstream object kin1
Kstream kin1 = new Kstream();

// now set the setters:
// not sure if i need this kin1 -> StringNames(stringnames)  // string names must be a vector array of String type
//kin1 -> SetVMatrix(Vmatrix); //Vmatrix is the varence matrix and must be of TMatrixD type.
//kin1 -> SetP4(fvecs);   // array of TLorentzVectors representing the three measured particles.
//kin1 -> SetPhotonEnergy(ephoton);  //ephoton must be a double
//kin1 -> SetTargetMass(proton_mass);    //proton_mass must be a double 

//or can set the setters with one command

kin1-> StringNames(particle_names); // where particle_names is a vector of strings
kin1 -> FitInput(ephoton, fvecs, Vmatrix, proton_mass);   // witht the types defined the same as above.


// now call the function fit and have it return a double which is the confidence level
double confidence_level = k1 -> fit("lambda", constrain_meas, false, lambda_mass);  // with constrain_meas is a bool array and lambda_mass a double
// what is constrain_meas ??????????????


