#!/usr/local/bin/perl -w

$indir = "/mss/clas/g12/production/pass1/bos/1-1ckaon1ctrk";
$outdir1 = "/mss/clas/g12/production/pass1/user_skims/jbono/kpppim";
$workdir = "/w/hallb/clasg12/jbono/skim/badui/kpppim";

$i = 1;
@sublist = ("first"); 
@array = ("first");

system("date +%F > date.tmp");
open(DATE,"date.tmp");
while(<DATE>){
  chomp;
  $date = $_;
}
system("rm date.tmp");

#$date = chomp(`date +%F`);

while(<USED>){
  chomp;
  push(@sublist,$_);
}
close(USED);
$sublength = @sublist;

#Creates an array of files on the farm
system("ls -1 $indir/ > templist");
open(IN, "templist");
while(<IN>){
  chomp;
  push(@array,$_);
}
close(IN);
system("rm templist");
$arrayLength = @array;

while($i < $arrayLength){
  $num_files = 50;
  if(($arrayLength - $i)<$num_files){
        $num_files = $arrayLength - $i;
  }
  $filename = $array[$i];
    open(OUT,">farmjobs/job_$date\.$filename\.jb") or die("Cannot open file job_$date\.$filename\.jb for writing\n");
    print OUT "PROJECT: g12\nTRACK: analysis\nJOBNAME: badui-kpppim-bos-view-skim-$filename\nOS: centos62\n";
    print OUT "COMMAND: source environment.csh ; perl anakpppim_perl";
    print OUT "\n";
    print OUT "INPUT_FILES:\n";
    print OUT "/group/clas/builds/environment.csh\n";
    print OUT "$workdir\/farm/ana_kpppim\n";
    print OUT "$workdir\/farm/anakpppim_perl\n";

    for($j=$i;$j<($num_files+$i); $j++){
        print OUT "$indir\/$array[$j] \n";
    }
    print OUT "SINGLE_JOB: true\nMEMORY: 1 GB\nDISK_SPACE: 100 GB\n";
    print OUT "TIME: 120\n";
    for($j=$i;$j<$num_files+$i; $j++){
        print OUT "OUTPUT_DATA: $array[$j]\.bos1\nOUTPUT_TEMPLATE: $outdir1/bos/$array[$j]\n";
    }
    for($j=$i;$j<$num_files+$i; $j++){
        print OUT "OUTPUT_DATA: $array[$j]\.view1\nOUTPUT_TEMPLATE: $outdir1/view/$array[$j] \n";
    }
    print OUT "OUTPUT_DATA: status1\.txt\nOUTPUT_TEMPLATE: $outdir1/logs/$array[1] \n";

    close(OUT);
    $percent = (($i / $arrayLength) * 100);
    printf "\r Percent completed: %4.2f%%", $percent;
  $i+=$num_files;
}
