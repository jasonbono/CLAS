#!/usr/bin/perl

#jason bono
#july 3rd 2012

#purpose: to display what percent of the files h
#everything in g12runs by doing 1-10 files at a time.



$total = 0;

# open g12runs file which give howmany files there are for each run
open(FILE, "g12runs.txt") or die("Unable to open file");

# read file into an array
@g12runs = <FILE>;

# close file 
close(FILE);



#now split the array and determine how many total files there are
	for my $elem (@g12runs) 
	{
	    my ($run, $howmany) = split (' ',$elem);		
		my @values = split(' ',$data);
		my $decimal = $howmany/10;
		my $decplushalf = $decimal + 0.499;
		my $rounded = sprintf "%.0f",$decplushalf;

		$total = $total + $rounded;
		#print "howmany=$howmany decimal=$decimal decplushalf=$decplushalf rounded=$rounded \n";
	}

print "out of $total files in total \n";


