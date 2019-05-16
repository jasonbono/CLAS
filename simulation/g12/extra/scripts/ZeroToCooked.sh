

# from the try4 directory follow the commands

genr8 -M10000 -omyXi.gamp < myXi.input2

gamp2part -r56855 -omyXi.part -T -S-0.321,0.378,-0.254,0.407 -z-110,-70 myXi.gamp

gsim_bat -ffread ffread.g12 -kine 1 -mcin myXi.part -bosout myXi.gsim -trig 2000000

gpp -Y -s -R56855 -P0x7f -omyXi.gpp myXi.gsim

a1c -T4 -sa -ct1930 -cm0 -cp0 -X0 -d1 -F -P0x1bff -z0,0,-90 -Aprlink_tg-90pm30.bos -omyXi.a1c myXi.gpp

############# THE FFREAD #############################


=============FFREAD.G12======================

                            #(why five numbers in this group  ?)
CUTS   5.e-3 5.e-3 5.e-3 5.e-3 5.e-3	#  Kinetic energy cuts in GeV:      (why no particle specified ?)
DCCUTS 1.e-4 1.e-4 1.e-4 1.e-4 1.e-4	#  cuts for drift chamber  
ECCUTS 1.e-4 1.e-4 1.e-4 1.e-4 1.e-4	#  cuts for ec                                    (what is ec ?)
SCCUTS 1.e-4 1.e-4 1.e-4 1.e-4 1.e-4	#  cuts for start counter                        (scintelator or startcounter)          

MAGTYPE 2								#  B-field type: analytic torus field strength 
MAGSCALE 0.500 0.000					#  scale factor for torus and mini-torus
PTGIFIELD 0								# Polarized target field type                                 (?)
				  
STTYPE 1								#                                            (no documentation ?)
STZOFF -90.0							#
TGPOS 0. 0. 0.							# Target position x,y,z						 (no documentation ?)

TARGET 'g11a'							#  target type
TGMATE 'PROT'							#  target material  


POSBEAM 0.0 0.0					 		#  beam position

GEOM 'ALL' 'ST'   						#  user words to control geometry setup            (what is 'ALL' & 'ST'?)
NOGEOM 'MINI' 'PTG '					#  take out the mini torus and the ptg                    (what is ptg ?)

BEAM 0 0 5.744						 	#  electron beam energy
DCAY 1									#  let the particles decay

KINE 1     								#  Sets the flavor of kinematics generator:  Read BOS file from -mcin flag  (?) 
MULS 1									#  allow for multiple scattering

AUTO 1									#  automatic computation of the tracking medium parameters                (?)

RUNG 56855								#  run number

TIME 1000000 1000000 1000000			#  time left after initalization                                       (?)

TRIG 1000000							#  total number of events to process

STOP     								#
============================================

