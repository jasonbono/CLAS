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
	$goodx=0;
	$goodlam=0;
	$scv=$line[2];
	$stv=$line[3];
	if(abs($scv-$stv)<1) {
	  $goodst=1;
	}
	$sctkp1=$line[20];
	$sclkp1=$line[23];
	$betakp1=$line[17];
	if($betakp1>0){
	  if(abs($sctkp1-$sclkp1/(29.99*$betakp1)-$scv)<1){
	    $goodsc=1;
	  }
	}
	$sctkp2=$line[21];
	$sclkp2=$line[24];
	$betakp2=$line[18];
	if($betakp2>0){
	  if(abs($sctkp2-$sclkp2/(29.99*$betakp2)-$scv)<1){
	    $goodsc2=1;
	  }
	}
	$beam=$line[35];
	if($beam>3){
	  $goodeg=1;
	}
	$mmkkpi=0;
	if($line[48]>0) {$mmkkpi=sqrt($line[48]);}
	if(abs($mmkkpi-1.1162)<0.0264){
	  $goodlam=1;
	}
	$mmkk=0;
	if($line[55]>0) {$mmkkpi=$line[55];}
	if(abs($mmkkpi-1.3218)<0.0225){
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
	$mmkp1=$line[75];
	$mmkp2=$line[74];
	$cos1=$line[101];
	$cos2=$line[103];
	
	if($goodst&&$goodsc&&$goodsc2&&$goodeg&&$goodlam&&$goodx&&$goodpart&&$goodx){
	  print B "$mmkp1 $mmkp2 $cos1 $cos2\n";
	  #print B "$_\n";
	}
      }
close(A);
close(B);
