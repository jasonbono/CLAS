c      include file INTEGR
c
c_begin_doc
c  RCS ID string
c  $Id$
c
c  Documentation for include file INTEGR
c
c  Purpose:
c  --------
c
c  Used in routines:
c  ----------------
c
c  Notes:
c  ------
c
c  Author:         Created:  Mon Dec 16 16:48:06 EST 1996
c  -------
c
c  Major revisions:
c  ----------------
c
c_end_doc
c
c
c  Remember NO NESTED INCLUDES
c
c  COMMON BLOCK NAME should be the same as include file name!
c
c_begin_var
c  variables for include file INTEGR:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CIINTEGR
      DATA CIINTEGR/
     1'$Id$'
     2/
c----6----------------------------------------------------------------72
c  
c  Variables contained in INTEGR common block
c  --------------------------------------------
c
c_end_var
c
      REAL br(6,3)
       COMMON/INTEGR/br
c----6----------------------------------------------------------------72




