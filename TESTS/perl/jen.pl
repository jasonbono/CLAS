#!/usr/bin/perl


system("say Hi jennifer how are you?");
chomp ($choice = <>);
if ($choice eq "good"){
	system("say im glad you are good hem hen");	
} elsif ($choice eq "bad"){
	system("say im sorry to hear that hem hen");
} else {system("say $choice  you say... i see");}


sleep 1;

system("say so what do you want to do this morning" );
chomp ($choice = <>);
system("say $choice ?????");
sleep 1;
system("say hmmmmmmm.... let me think...");
sleep 3;
system("say dont get hasty im still thinking... \n");
sleep 2;
system("say OK! we will $choice. sounds amazing. we can do whatever you want.");