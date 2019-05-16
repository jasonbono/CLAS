# Author: Jason Bono
# Date: July 24 2013
 


#!/apps/bin/perl -w
use diagnostics;
use warnings;
use File::Basename;

$indir = "/w/hallb/clasg12/samples/ppippim";
$outdir = "/mss/clas/g12/production/pass1/user_skims/jbono/ppippim";


@files = <$indir/*.bos>;
foreach $fpath (@files) {  
	print "Original  : " . $fpath . "\n";
 	my($filename, $directories) = fileparse($fpath);
	print "Filename  : " . $filename    . "\n";
	print "Directory : " . $directories . "\n";
  	print "Output :   $outdir/$filename  \n";
	print "\n";
 	system ("jput $fpath $outdir/$filename");
}  