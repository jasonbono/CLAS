#!/apps/bin/perl -w
use File::Basename;

$path = "/jbono/ppippim/56799.A01.ppippim.bos";


($file,$dir) = fileparse($path);
$run = substr($file,0,5);
$subrun = substr($file,6,3);
$top = substr($file,10,7);
$ext = substr($file,18,3);
$newfile = $top . "." . $run  . "." . $subrun . "." . $ext;
$newpath = $dir . $newfile;

#print "dir:  $dir \n";
#print "file:  $file \n";
#print "run:  $run \n";
#print "subrun:  $subrun \n";
#print "top:  $top \n";
#print "ext:  $ext \n";


print "newfile:  $newfile \n \n";

print "path:  $path \n";
print "newpath:  $newpath \n";






