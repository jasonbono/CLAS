#!/apps/bin/perl -w
use File::Basename;


$indir = "/mss/clas/g12/production/pass1/user_skims/jbono/ppippim";



@files = <$indir/*.bos>;
foreach $path (@files) {
	
	($file,$dir) = fileparse($path);
	$run = substr($file,0,5);
	$subrun = substr($file,6,3);
	$top = substr($file,10,7);
	$ext = substr($file,18,3);
	$newfile = $top . "." . $run  . "." . $subrun . "." . $ext;
	$newpath = $dir . $newfile;
		
		
	print "path:  $path \n";
	print "newpath:  $newpath \n";	
	print "will execute: \n";
	print "system(jrename $path $newpath) \n";
	system("jrename $path $newpath");
	print "\n"
}