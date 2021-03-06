      Subroutine trk_book_tbt()
*_begin_doc
*  RCS ID string
*  $Id: trk_book_tbt.F,v 1.5 1998/04/03 22:57:06 jyun Exp $
*
*  Documentation for subroutine TRK_BOOK_tbt
*
*  Purpose:  This routine book the Hit Based Tracking Histograms.
*  --------  
*
*  Input Parameters: NONE
*  ----------------
*
*  Output Parameters: NONE
*  -----------------
*
*  Other routines:
*  ---------------
*
*  Notes:
*  ------
*
*  Author:         Francois H. Roudot
*  -------         
*
*  Creation Date:  29 May, 1997
*  --------------
*
*  Major revisions: 
*  ---------------	
*
*_end_doc
*
      Implicit None
      Save
*
*
*_begin_inc
*  include files :
*  ---------------------
*

#include "bcs.inc"
c#include "sdakeys.inc"
#include "sdadigi.inc"
#include "trktcl_var.inc"

*
*_end_inc
*
*_begin_var
*  input/output variables:
*  -----------------------
*
*  Local pre-defined variables:
*  ---------------------------
*  RCS information: 
      CHARACTER*132  CFILE, CREVIS, CSTATE, CDATE, CAUTHO, CRCSID
      PARAMETER ( CFILE = '$RCSfile: trk_book_tbt.F,v $')
      PARAMETER ( CREVIS = '$Revision: 1.5 $')
      PARAMETER ( CSTATE = '$State: Exp $')
      PARAMETER ( CDATE = '$Date: 1998/04/03 22:57:06 $')
      PARAMETER ( CAUTHO = '$Author: jyun $')
      DATA CRCSID/
     1'$Id: trk_book_tbt.F,v 1.5 1998/04/03 22:57:06 jyun Exp $
     3'/
*     Module information:
      CHARACTER*132  CRNAME, CRAUTH
      CHARACTER*132  CRMESS
      PARAMETER (CRNAME='TRK_BOOK_tbt')
      PARAMETER (CRAUTH='Francois H. Roudot')
*     
*     Local User defined variables:
*     ----------------------------
      character*6 h1_label(7)
      data h1_label/'event ','sector','layer ','wire  ','fdoca ','tdc   ','lclang'/
      character*6 h2_label(19)
      data h2_label/'Sector', 'NHtR1S', 'NHtR1A', 'NHtR2S', 'NHtR2A', 'NHtR3S',
     1     'NHtR3A', 'XVert ', 'YVert ', 'ZVert ', 'XDirCS', 'YDirCS',
     2     'ZDirCS', 'WrLyR1', 'WrLyR2', 'WrLyR3', 'Chi2  ', 'Mmtm  ',
     3     'Q    '/
*     
      
      character*80 his_title
      character*1 Fsec
      integer Reg, Sec, HistID
      integer NWRITE    
     
c     ------------------------------------------------------------------------
	if (ipar_trk_histo.ge.1.or.ipar_trk_ntuple.ge.1) then

         
         call hcdir('//PAWC/TRK',' ')
         call hmdir('tbt','S')
         call hcdir('//LUN1/TRK',' ')
         call hmdir('tbt','S')
         
c     --------------------
c     book ntuples
c     --------------------
         if (ipar_trk_ntuple.ge.1) then                                     
            call hbookn(111,'tbt per layer',7,'//LUN1/TRK/tbt',500,h1_label) ! quantities indexed on layer
            call hbookn(112,'tbt per track',19,'//LUN1/TRK/tbt',500,h2_label) ! quantities indexed on track
         endif

c     -----------------------
c     book the tbt histograms
c     -----------------------
         if (ipar_trk_histo.ge.1) then
c     book stuff from the tbtR bank
            call hbook1(7735, 'tbt Chi2 pdf', 100, 0., 10., 0.)
            call hbook1(7736, 'tbt track momentum (GeV/cc)', 200, 0., 5., 0.)
            call hbook1(7737, 'tbt X at vertex (cm)', 200, -100., 100., 0.)
            call hbook1(7738, 'tbt Y at vertex (cm)', 200, -100., 100., 0.) 
            call hbook1(7739, 'tbt Z at vertex (cm)', 200, -100., 100., 0.) 
            call hbook1(7740, 'tbt X direction mtm', 200, 0., 5., 0.)
            call hbook1(7741, 'tbt Y direction mtm', 200, 0., 5., 0.)
            call hbook1(7742, 'HBf Z direction mtm', 200, 0., 5., 0.)
            call hbook1(7743, 'tbt charge', 5, -2., 2., 0.)
            
c     book counting stuff
            call hbook1(7730, 'tbt tracks per event', 37, 1.0, 10.0, 0.0)
cyun(18/9/97) change the limit
            call hbook1(7731, 'tbt hits per track', 34, 1.0, 35.0, 0.0)
            
c     book things indexed on sector (and region)
cyun 11/9/97 change his_title


            do Sec = 1,6
            
               write(Fsec,'(i1)') Sec	
               HistID = 30 + Sec*100 + 7000
	       his_title = 'tbt tracks per event  Sec'//Fsec	
               call hbook1(HistID, his_title, 37, 1.0, 10.0, 0.0)
               HistID = 31 + Sec*100 + 7000
	       his_title = 'tbt hits per track  Sec'//Fsec
               call hbook1(HistID, his_title, 37, 1.0, 37.0, 0.0)
               HistID = 32 + Sec*100 + 7000 
               his_title = 'tbt real layer vs wire  Sec'//Fsec
               call hbook2(HistID,his_title,195, 0.0, 195.0, 37, 0.0, 37.0, 0.0)
               HistID = 33 + Sec*100 + 7000   
               his_title = 'tbt synth layer vs wire  Sec'//Fsec
               call hbook2(HistID,his_title,195, 0., 195., 37, 0., 37., 0.)
               HistID = 45 + Sec*100 + 7000
               his_title='tbt layer vs local track angle Sec '//Fsec
               call hbook2(HistID,'tbt layer vs local track angle (degs)',120, -60., 60., 37, 0., 37., 0.)
               
               Reg=1
               HistID = 34 + Sec*100 + Reg*1000
               his_title = 'tbt TDC  R1S'//Fsec
               call hbook1(HistID, his_title, 200, -500.0, 3000.0, 0.0)  
               HistID = 44 + Sec*100 + Reg*1000
               his_title = 'tbt Fitted DOCA  R1S'//Fsec
               call hbook1(HistID, his_title, 200, -3., 3., 0.)
               HistID = 46 + Sec*100 + 1000*Reg
               his_title = 'tbt FDOCA vs TDC  R1S'//Fsec
               call hbook2(HistID, his_title, 200,  0., 3000.,  200, -2., 2., 0.)
               
               Reg=2
               HistID = 34 + Sec*100 + Reg*1000
               his_title = 'tbt TDC  R2S'//Fsec
               call hbook1(HistID,his_title, 200, -500.0, 3000.0, 0.0)  
               HistID = 44 + Sec*100 + Reg*1000
               his_title = 'tbt Fitted DOCA  R2S'//Fsec
               call hbook1(HistID, his_title, 200, -4., 4., 0.)
               HistID = 46 + Sec*100 + 1000*Reg
               his_title = 'tbt FDOCA vs TDC  R2S'//Fsec
               call hbook2(HistID, his_title, 200, 0., 3000., 200, -3., 3., 0.)
               
               Reg=3
               HistID = 34 + Sec*100 + Reg*1000
               his_title = 'tbt TDC  R3S'//Fsec
               call hbook1(HistID, his_title, 200, -500.0, 3000.0, 0.0)  
               HistID = 44 + Sec*100 + Reg*1000
               his_title = 'tbt Fitted DOCA  R3S'//Fsec     
               call hbook1(HistID, his_title, 200, -5., 5., 0.)
               HistID = 46 + Sec*100 + 1000*Reg
               his_title = 'tbt FDOCA vs TDC  R3S'//Fsec
               call hbook2(HistID, his_title, 200, 0., 3000., 200, -4., 4., 0.)
            enddo
         endif
         call hcdir('//PAWC/TRK',' ')
      endif
      
      Return
      End









































