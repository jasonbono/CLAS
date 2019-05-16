




genr8 -M100 -omyXi.gamp < myXi.input
gamp2part -r56855 -omyXi.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 myXi.gamp










# gamp2part
# Options:

#   -M[#]		Use only [#] number of events
#   -p[#]		Use this number part bank for output file
#   -r[#]		Use [#] for runno (default runno = 1)
#   -o<filename>	Use <filename> for output BOS file
#   -t[#]		Use [#] for trigger bit identification (default = 1)
#   -T			Put Beam particle in TAGR bank (photon use only!)
#   -z[#,#]		Distribute vertex-z is given range
#   -S[#,#,#,#]	Distribute vertex-xy according to MU_X,MU_Y,SIGMA_X,SIGMA_Y
#   -V			Use debugging mode
#   -h			Print this message
