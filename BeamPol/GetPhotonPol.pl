#!/apps/bin/perl -w
use diagnostics;
use warnings;

# Author: Jason Bono
# Date: Feb 8 2014
# Purpose: To calculate the g12 photon polarization within a specified energy range.

# Notes:
# This scirpt uses the electron polarization as recorded by the moller runs along with a user-specified energy range
# and Johann's g12-flux calculator (found at /u/home/clasg12/local/scripts/g12-gflux)
# g12-gflux was compiled under the enviroment /group/clas/builds/environment.csh/sh. 
# The flux is calculated in bins of 100 MeV

# Usage:   > perl GetPhotonPol.pl
# enter the low and high photon energy in GeV as prompted
# The result assumes a flat energy distribution within the specified range so smaller intervals have smaller error. 
# Other sources of error come from the moller measurments and the flux calculations.


print "low energy? example: 2.1 (this is the lowest value you should use) \n";
chomp ($low = <>);
print "high energy? example: 5.5 (this is the highest value you should use) \n";
chomp ($high = <>);
$scriptdir="/u/home/clasg12/local/scripts";



#the energy step for calculation of the flux
my $estep = 0.1;
my $emin = 2.1;
my $emax = 5.5;


#"lower" run number 
@rl = ();
push(@rl,56355);#1
push(@rl,56476);#2
push(@rl,56644);#3
push(@rl,56733);#4
push(@rl,56744);#5
push(@rl,56850);#6
push(@rl,56930);#7
push(@rl,57029);#8
push(@rl,57178);#9
push(@rl,57250);#10 pol droped to zero after this measurment because the pocket-cell was turned off
push(@rl,57283);#11
push(@rl,57317); #12 this is the last run
$dim = scalar @rl;

# "upper" run number
@ru = ();
for  ($i = 0; $i < $dim - 1; $i++  ){
	push(@ru,$rl[$i + 1] - 1);
}

#moler measured polarization
@p = ();
push(@p,81.221);#1
push(@p,67.166);#2
push(@p,59.294);#3
push(@p,62.071);#4
push(@p,62.78);#5
push(@p,46.49);#6
push(@p,45.45);#7
push(@p,68.741);#8
push(@p,70.504);#9
push(@p,2);#10  polarization dropped after the moller run was preformed
push(@p,68.535);#11
push(@p,67.7); #12

#dimension of p and r should be the same
for  ($i = 0; $i < $dim; $i++  ){
	print "lower run = $rl[$i],  moller = $p[$i] \n";
}

#create the files of the run lists for runs in between moller measurments.
if ( !(-d "./txt")) {
    system ("mkdir txt");
}
for  ($i = 0; $i < $dim - 1; $i++  ){
	system ("$scriptdir/g12runs -r $rl[$i]:$ru[$i] > ./txt/g12runs$i.txt");
}

@totalf = (); #the total flux in each energy bin
@totalfp = (); #the sumed product of flux and electron polarization in each energy bin
@overallp = (); #the overall polarization in each energy bin
#create files with the flux in bins of energy, and with the relevant moller measurment.
for  ($i = 0; $i < $dim - 1; $i++  ){
	system ("$scriptdir/g12-gflux $emin $emax $estep ./txt/g12runs$i.txt good > ./txt/flux$i.txt");
 	my $file = "./txt/flux$i.txt";
 	open my $info, $file or die "Could not open $file: $!";	
	@el = ();
	@eh = ();
	@f = ();
	while( my $line = <$info>){   
		#spilt the lower energy, higher energy, and the flux
		@EandF = split (/ +/,$line);
		push(@el,$EandF[0]);
		push(@eh,$EandF[1]);
		push(@f,$EandF[2]);
 	}
	$nebins = scalar @f;
	for  ($j = 0; $j < $nebins; $j++  ){
		$totalf[$j] += $f[$j];
		$totalfp[$j] += $f[$j]*$p[$i];
		print "total flux = $totalf[$j], total flux times polarization = $totalfp[$j]  \n";
	}		
 	close $info;
}
for  ($j = 0; $j < $nebins; $j++  ){
	$overallp[$j] = $totalfp[$j]/$totalf[$j];
	print "Overall Polarization = $overallp[$j] \n";
}
$electronenergy = 5.715;
$count = 0;
#now calculate the weighted sum to get photon polairzation using the maximon-olsen relation
for  ($k = $low; $k < $high; $k += $estep  ){
	$emean = $low + ($count + 1/2)*$estep;
	$y = $emean/$electronenergy;
	$photonp_sum += $overallp[$k]*$y*(4-$y)/(4 - 4*$y + 3*$y*$y);
	$count += 1;
	print "k = $k, count = $count ,photon energy = $emean, y = $y, photonp_sum $photonp_sum \n"	
}

$photonp = $photonp_sum/$count;
print "Photon Polarization = $photonp \n";