9000 1 4 0.000000 0.000000 4.000000 4.000000

1 11 0.493680    kaon
   1 -0.072461 -0.177362 1.470692 1.563126

2 9 0.139570    pim
   -1 0.007089 0.046208 0.336820 0.367577

3 0 1.116000   lambda
   0 -0.499491 -0.157020 1.107901 1.657422

4 11 0.493680   kaon
   1 0.564863 0.288173 1.084587 1.349875





1   0  0.000000     0.000000  4.000000  4.000000   beam 
9  -1  0.061035     0.129477  0.279903  0.343970   pion
0   0 -0.191932    -0.060142  1.664580  2.014135   ?
11  1  0.095907     0.033500  0.044118  0.505951   kaon
11  1  0.034990    -0.102835  2.011398  2.073943   kaon











===================================
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    genr8 input file usage:
%
%            genr8 -M100 -Aoutput.ascii -n < reaction.input
%
% Example: gamma p -> n X(1600)          (All decays are isotropic)
%                      X -> pi+ pi+ pi-
%
%  hint: use "-n" flag to actually print the particle names in the
%        the output for viewing/debuging, but remember not to use "-n"
%        for data that is used as input to HDFast.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
% Any number of blank spaces ( NO TABS!!!)
% can be used between input values in an input line.
%
%%%%%%%%%%%%%%%%% Start Input Values %%%%%%%%%%%%%%%%%%%%
% beamp.x beamp.y beamp.z beamMass
0 0 8 0
% targetp.x targetp.y targetp.z targetMass
0 0 0 0.938
% t-channelSlope
      5.0
% number of particles needed to describe the isobar decay of X
6
%
% particle# 0&1 are always the X&Y
%part#  chld1#  chld2#  parent# Id     nchild   mass    width   charge  flag
% meson (X) decay
 1       *      *       *       11       0     0.49368    0.0    +1      11
% baryon (Y) decay
 0       2      3       *       0       2       2.0      0.5      0      00
 2       4      5       0       23      2       1.321    0.01    -1      00
 3       *      *       0       11      0      0.49368    0.0    +1      11
 4       *      *       2       9       0      0.13957    0.0    -1      11
 5       *      *       2       l8      0      1.116      0.0     0      11
!EOI
%%%%%%%%%%%%%%%%%%%%% End Input Values %%%%%%%%%%%%%%%%%%%%%%%
% for narrow widths particles(stable to strong interactions)
%  set width to zero (i.e. eta, pi's).'
%
%flag 00 =isobar or resonace
%flag  01 = production particle that decays i.e. eta, pizero ..
%flag  11 = production particle that does not decay i.e. piplus,...
%flag  10 = final state particle not in production i.e. gamma
%
%
%  Particle Id information defined in particleType.h
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% These constants are defined to be same as GEANT.
% See http://wwwcn.cern.ch/asdoc/geant/H2GEANTCONS300.html
% for more details.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Unknown        =  0,
%  Gamma          =  1,
%  Positron       =  2,
%  Electron       =  3,
%  Neutrino       =  4,
%  MuonPlus       =  5,
%  MuonMinus      =  6,
%  Pi0            =  7,
%  PiPlus         =  8,
%  PiMinus        =  9,
%  KLong          = 10,
%  KPlus          = 11,
%  KMinus         = 12,
%  Neutron        = 13,
%  Proton         = 14,
%  AntiProton     = 15,
%  KShort         = 16,
%  Eta            = 17,
%  Lambda         = 18,
%  SigmaPlus      = 19,
%  Sigma0         = 20,
%  SigmaMinus     = 21,
%  Xi0            = 22,
%  XiMinus        = 23,
%  OmegaMinus     = 24,
%  AntiNeutron    = 25,
%  AntiLambda     = 26,
%  AntiSigmaMinus = 27,
%  AntiSigma0     = 28,
%  AntiSigmaPlus  = 29,
%  AntiXi0        = 30,
%  AntiXiPlus     = 31,
%  AntiOmegaPlus  = 32,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% extra constants not defined by GEANT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Rho0           = 57,
%  RhoPlus        = 58,
%  RhoMinus       = 59,
%  omega          = 60,
%  EtaPrime       = 61,
%  phiMeson       = 62 
%  
%  







============================================================================
try4 gamp
6
1 0 0.000000 0.000000 4.000000 4.000000

pi-
9 -1 -0.061768 0.156862 0.156033 0.268788

proton
14 1 -0.449567 0.084920 1.109845 1.523623
9 -1 0.018416 0.055898 0.157595 0.218585
11 1 0.140475 -0.110968 0.272428 0.591594
11 1 0.220052 -0.124768 2.264252 2.331212



try4 ascii
9000 1 5 0.000000 0.000000 4.000000 4.000000

1 11 0.493680  k+
   1 -0.172479 -0.057083 1.883705 1.955779

2 9 0.139570   pi-
   -1 0.051877 0.031564 0.282184 0.320616

3 14 0.938270  proton
   1 0.109959 0.218964 0.621751 1.151938

4 9 0.139570  pi-
   -1 0.080727 -0.040467 0.091643 0.189823

5 11 0.493680 k+
   1 -0.156963 -0.029757 1.285454 1.386231
















