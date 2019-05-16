#!/usr/bin/perl


system("say -r 170 how many question should i tell?");
chomp ($nq = <>);
system("say -r 200 Ok, I will ask $nq questions. For each question to tell, i have four more to ask.");

system("say -r 200 to whom am i asking questions?");
chomp ($name = <>);
$total = 4*$nq;
system("say -r 230 Wonderful buddy, I will ask $name many questions. Either $nq or $total of them. I dont know how many yet. sorry buddy.");
sleep 1;
@line = ("what you are doing","what, you are doing","what you are doing","what you are doing man!");
@voice = ("Bruce","Fred","Junior","Ralph","Agnes","Kathy","Princess","Vicki","Victoria","Cellos","Deranged","Bahh");


for( $j = 0; $j <11; $j = $j + 1 )
{
	system("say -v @voice[$j]  -r 300   Hey $name?");
}

system("say Ok $name , time to start asking better questions, but first some questions, then more questions. ok buddy?");
 
	system("say -v Cellos -r 700  $name $name $name $name i am going to ask you $total questions and tell you even more. $name  $name $name $name i am going to tell you one hundred billion questions. ");

for( $j = 0; $j < $nq; $j = $j + 1 )
{

	my $rand = int(rand(10));
	if($j eq 0){
		$rand = 1;
	}	
	system("say -v @voice[$rand]  Hey $name ?");


    system("say -v @voice[$rand] -r 320  @line[0] @line[1] @line[2] @line[3]");


	


	if($j eq 1)
	{
		system("say -r 400 what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing man?");
	}
	
	if($j eq 3)
	{
		
		system("say There, that was one question. Now to ask the others buddy.");
	}
	
	
	if($j eq 4)
	{
		system("say Never mind!");
	}

	if($j eq 5)
	{
		system("say -v Princess -r 390 what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing what you are doing, man?");
	}

	
	sleep 1;
}

	
	system("say -v Pipe Organ -r 300 $name $name $name  $name i asked you many questions. $name $name $name would you like to go again?");

	system("say Never mind!");
	

