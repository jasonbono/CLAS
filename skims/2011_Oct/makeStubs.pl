#!/usr/local/bin/perl -w


#makeStubs.pl

# from will. sep 21
#may have to remove the open submitted_jobs or die line
#made a directory on g12 work disk called farmjobs as required by this script
# /w/hallb/clasg12/jbono/farmjobs
# have to runt this in that directory
#edit the in_dir and out_dir in this file 
# type: perl makestubs.pl 

$in_dir = "";
$out_dir = "";

$date = `date +%F`;
chomp($date);

@nonprod = ("first");
open(USED, "submitted_jobs.txt") or die "Can't find submitted_jobs.txt!\n";

while(<USED>){
    chomp;
    push(@nonprod,$_);
}
close(USED);

$np_len = @nonprod;
system("ls -1 $in_dir > templist");
open(IN, "templist");
while(<IN>){
chomp;
    if(&prod("$_")){
    open(OUT,">farmjobs/job_$_\.jb");
    print OUT "PROJECT: g12\nTRACK: analysis\nJOBNAME: ppskim_$_\n";
    print OUT "COMMAND: ppskim $_ -ofile1\.bos ; pkskim $_ -ofile2\.bos\n";
    print OUT "INPUT_FILES: $in_dir/$_\n";
    print OUT "OUTPUT_DATA: file1\.bos\nOUTPUT_TEMPLATE: $out_dir/$_\n"; 
    print OUT "OUTPUT_DATA: file2\.bos\nOUTPUT_TEMPLATE: $out_dir/$_\n"; 
    print OUT "SINGLE_JOB: true\n";
    print OUT "DISK_SPACE: 5 GB\nTIME: 60\n";
    close(OUT);
    }
   
}
close(IN);
system("rm templist");

sub prod {
    local($process);
    $process = 1;
    for ($j = 0; $j < ($np_len); $j++){
        if ($_[0] eq $nonprod[$j]){
            $process = 0;
            }
    }
    $process;
}

