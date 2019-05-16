	Program Min_gains_main 
c
c	Main program to drive Minuit
c	External subroutine to compute chi square is min_gains.
c	This routine must be provided.
c
	implicit none
	double precision min_gains
	external min_gains
	integer linput, loutput, lsave, ldata, flag, lparm, ihst,lkumac
	integer npts
	double precision parm, error, bound1, bound2
	double precision p1, p2, err1, err2, chi2df, chimin, p1min
	double precision p3, p4, p5, p6, p7
	double precision err3,err4, err5, err6, err7
	real xmin,xmax,xave
	common /xlimits/ xmin,xmax,xave
	character*10 name
	character*1 answer, select
	character*20 control
	character*20 min_input, min_output, min_parm, min_kumac
	Parameter (min_input='min_input', min_output='min_output',
     1             min_parm='min_parm', min_kumac='min_kumac')
c
	double precision chi2, fedm, errdef
	integer npari, nparx, istat, ndf
c
	Parameter (linput=9, loutput=8, lsave=7, ldata=1, lparm=14,
     1             lkumac=15)
	data chimin, p1min /200.,100./
c
c       Write out files in use
c
	write (6,*) 'Min_main - Symbolic Input  File=',min_input
	write (6,*) 'Min_main - Symbolic Output File=',min_output
	write (6,*) 'Min_main - Symbolic Parm   File=',min_parm
	write (6,*) 'Min_main - Symbolic Kumac  File=',min_kumac
c
c       open files
c       
	open (unit=linput,file=min_input,status='old')
	open (unit=loutput,file=min_output,status='unknown',
     1		form='formatted')
	open (unit=lparm,file=min_parm,status='unknown',
     1		form='formatted')
	open (unit=lkumac,file=min_kumac,status='unknown',
     1		form='formatted')
c
	call mintio (linput,loutput,lsave)
c
c       inquire about cuts on kumac file
c
      	write (6,'(a,$)') ' Min_main - Kumac File: Check All/Selected (A/S)? '
c	read (5,'(a)') answer
	answer = 'a'
	if (answer.eq.'s' .or. answer.eq.'S') then
	   write (6,*) 'Min_main - Kumac: Check selected histograms only'
	   answer = 's'
	else
	   write (6,*) 'Min_main - Kumac: Check all histograms'
	endif
c
c       output headers
c
	write (lkumac,*) 'vector/create p(8) R 8*0.'	
c
c       loop over data / one per plot until EOF
c
100	continue
	read (linput,*,end=900) control, ihst, npts
c	write (6,*) control, ihst, npts
	call minuit (min_gains,0)
c
c       output fitted parameters
c
	call mnpout (1,name,parm,error,bound1,bound2,flag)
	p1 = parm
	err1 = error
	call mnpout (2,name,parm,error,bound1,bound2,flag)
	p2 = parm
	err2 = error
	call mnpout (3,name,parm,error,bound1,bound2,flag)
	p3 = parm
	err3 = error
	call mnpout (4,name,parm,error,bound1,bound2,flag)
	p4 = parm
	err4 = error
	call mnpout (5,name,parm,error,bound1,bound2,flag)
	p5 = parm
	err5 = error
	call mnpout (6,name,parm,error,bound1,bound2,flag)
	p6 = parm
	err6 = error
                call mnpout (7,name,parm,error,bound1,bound2,flag)
	p7 = parm
	err7 = error
c
c       Fit quality
c
	call mnstat (chi2,fedm,errdef,npari,nparx,istat)
	ndf = npts - npari + 1
	if (ndf.gt.0 .and. istat.gt.0) then
c
c            note: normalization is given by chi2 / use status as normalizer 4/2/01
c
	     chi2df = (chi2/ndf)/istat
	else
	     chi2df = 100.
c	     write (6,*) '*** Min_main - chi2df=0., ihst=',ihst
	endif

	select = 'n'


	if (chi2df.gt.chimin .or. istat.eq.0 .or. p1.lt.p1min) then
	   write (6,*) 'Min_main - ihst=',ihst,' istat=',istat,
     1                 ' chi2df=',chi2df
	   select = 'y'
c
c          if peak is poorly determined, set to 600+/-600
c
               p1 = 600.
               err1 = 600.
	endif
c
c
c       if (p1.gt. 1500 .or. p1.lt. 0) then
c       p1 = 600.00
c      endif
c
c
       if (err1.gt. 1500 .or. p1.lt. 0) then
       err1 = 600.0
       endif

c
c       output to parameter file
c
	write (lparm,110) ihst,p1,err1,chi2df,istat
c	write (6,110) ihst,p1,err1,chi2df,istat
 110	format (i6,2f10.3,f8.2,i4)
c
c       output selected files to kumac file
c
	if (select.eq.'y' .or. answer.ne.'s') then
	   write (lkumac,*) 'hi/plot',ihst
	   write (lkumac,112) 'vector/input p ', p1,p2,p3,p4,p5,p6,p7,chi2df
 112	   format (a,8f17.3)
	   write (lkumac,*) 'func/plot gains_func_plot.f 0. 1000. s'
	   write (lkumac,*) 'exe window#push'
	   write (lkumac,*) 'text 0.4 0.5 ''Peak=''//$eval(p(1)) 0.2'
	   write (lkumac,*) 'text 0.4 0.3 ''Chi2=''//$eval(p(8)) 0.2'
	   write (lkumac,*) 'exe window#pop'
	   write (lkumac,*) 'wait' 
	endif
c
c       get next plot
c
	go to 100
900	end


