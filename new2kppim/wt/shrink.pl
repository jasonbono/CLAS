#!/usr/bin/perl
$file=$ARGV[0];
$massfile=$ARGV[1];
open(A, $file);
open(B, ">$massfile");
while(<A>){
        chop;
  	@line=split " ", $_;
	$goodst=0;
	$goodsc=0;
	$goodsc2=0;
	$goodeg=0;
	$goodpart=0;
	$goodcl=0;
	$goodv=0;
	$pnum=0;
	$pipnum=0;
	$kmnum=0;
	$scv=$line[2];
	$stv=$line[3];
	if(abs($scv-$stv)<1) {
	  $goodst=1;
	}
	$sctkp1=$line[25];
	$sclkp1=$line[28];
	$betakp1=$line[22];
	if($betakp1>0){
	  if(abs($sctkp1-$sclkp1/(29.99*$betakp1)-$scv)<1){
	    $goodsc=1;
	  }
	}
	$sctkp2=$line[26];
	$sclkp2=$line[29];
	$betakp2=$line[23];
	if($betakp2>0){
	  if(abs($sctkp2-$sclkp2/(29.99*$betakp2)-$scv)<1){
	    $goodsc2=1;
	  }
	}
	$beam=$line[40];
	if($beam>3){
	  $goodeg=1;
	}
	$mmkkpi=0;
	if($line[53]>0) {$mmkkpi=sqrt($line[53]);}
	if(abs($mmkkpi-1.3172)<0.02){
	  $goodx=1;
	}
	$cl=$line[13];
	if($cl>0.1){
	  $goodcl=1;
	}
	$pnum=$line[11];
	$pipnum=$line[12];
	$kmnum=$line[10];
	if($pnum<2&&$pipnum<1&&$kmnum<1){
	  $goodpart=1;
	}
	$vz=$line[7];
	$vx=$line[5];
	$vy=$line[6];
	if(abs($vz+10)<21&&($vx*$vx+$vy*$vy)<8){
	  $goodv=1;
	}
	$fitm=$line[17];
	$cos=$line[102];
	
	if($goodst&&$goodsc&&$goodsc2&&$goodeg&&$goodcl&&$goodpart&&$goodv&&$goodx){
	  print B "$fitm $cos\n";
	  #print B "$_\n";
	}
      }
close(A);
close(B);
