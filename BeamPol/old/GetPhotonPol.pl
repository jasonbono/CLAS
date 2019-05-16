#!/apps/bin/perl -w
use diagnostics;
use warnings;

# Author: Jason Bono
# Date: Feb 8 2014
#Notes: To run this,/group/clas/builds/environment.csh must be sourced. 



print "low energy? example: 2.8 \n";
chomp ($low = <>);
print "high energy? example: 5.5 \n";
chomp ($high = <>);

$scriptdir="/u/home/clasg12/local/scripts";

#run number 
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

@ru = ();
for  ($i = 0; $i < $dim - 1; $i++  )
{
	push(@ru,$rl[$i + 1] - 1);
}

#measured moler polarization
@p = ();
push(@p,-81.221);#1
push(@p,-67.166);#2
push(@p,-59.294);#3
push(@p,-62.071);#4
push(@p,-62.78);#5
push(@p,-46.49);#6
push(@p,-45.45);#7
push(@p,-68.741);#8
push(@p,-70.504);#9
push(@p,2);#10 
push(@p,-68.535);#11
push(@p,-67.7); #12 this is the last run

#dimension of p and r should be the same
for  ($i = 0; $i < $dim; $i++  )
{
	print "lower run = $rl[$i],  moller = $p[$i] \n";
}

#create the files of the run lists for runs inbetween moller measurments.
for  ($i = 0; $i < $dim - 1; $i++  )
{
	system ("$scriptdir/g12runs -r $rl[$i]:$ru[$i] > ./txt/g12runs$i.txt");
}

#the energy step for the flux
my $estep = 0.2;
my $emin = 2.8;
my $emax = 5.5;
@totalf = (); #the total flux in each energy bin
@totalfp = (); #the sumed product of flux and electron polarization in each energy bin
@overallp = (); #the overall polarization in each energy bin
#create files with the flux in bins of energy, and with the relevant moller measurment.
for  ($i = 0; $i < $dim - 1; $i++  )
{
	system ("$scriptdir/g12-gflux $emin $emax $estep ./txt/g12runs$i.txt good > ./txt/flux$i.txt  ");
 	my $file = "./txt/flux$i.txt";
 	open my $info, $file or die "Could not open $file: $!";	
	@el = ();
	@eh = ();
	@f = ();
	while( my $line = <$info>)  
 	{   
		#spilt the lower energy, higher energy and the flux
		@EandF = split (/ +/,$line);
		push(@el,$EandF[0]);
		push(@eh,$EandF[1]);
		push(@f,$EandF[2]);
 	}
	$nebins = scalar @f;
	for  ($j = 0; $j < $nebins; $j++  )
	{
		$totalf[$j] += $f[$j];
		$totalfp[$j] += $f[$j]*$p[$i];
		print "total flux = $totalf[$j], total flux times polarization = $totalfp[$j]  \n";
	}	
	
 	close $info;
}

for  ($j = 0; $j < $nebins; $j++  )
{
	$overallp[$j] = $totalfp[$j]/$totalf[$j];
	print "Overall Polarization = $overallp[$j] \n";
}


$electronenergy = 5.715;
$count = 0;
#now calculate the "integral" to get photon polairzation
for  ($k = $low; $k < $high; $k += $estep  )
{
	$emean = $low + ($count + 1/2)*$estep;
	$y = $emean/$electronenergy;
	$photonp_sum += $overallp[$k]*$y*(4-$y)/(4 - 4*$y + 3*$y*$y);
	$count += 1;
	print "k = $k, count = $count ,photon energy = $emean, y = $y, photonp_sum $photonp_sum \n"	
}

$photonp = $photonp_sum/$count;
print "Photon Polarization = $photonp \n";
