// nov 8 made this to develop 


tagr_t *my_get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *TBID){
  /* This routine only works for time-based tracks! */  
  float best_diff=ST_TAG_COINCIDENCE_WINDOW;
  float tprop=0.0;
  tagr_t *tagr = NULL;
  clasTBTR_t *TBTR=(clasTBTR_t *)getBank(&bcs_,"TBTR");
  float g11targz=-10;
  int i, j;      
    
  /* Exit from function if missing the requisite banks... */
  if(!TAGR || !TBTR || !TBID) return(NULL);
    
  for (i=0;i<TBID->bank.nrow;i++){
    int trk_ind=TBID->bid[i].track;
    if(trk_ind){     
      tprop=(TBTR->tbtr[trk_ind-1].vert.z - g11targz)/SPEED_OF_LIGHT*1e9;
    	if (TBID->bid[i].st.stat){       
    	  for(j=0;j<TAGR->bank.nrow;j++){
    	    float diff=fabs(TBID->bid[i].st.vtime-(TAGR->tagr[j].tpho+tprop));
    	    if (diff<ST_TAG_COINCIDENCE_WINDOW&&diff<best_diff
    		&& (TAGR->tagr[j].stat==7 || TAGR->tagr[j].stat==15)){
    	      best_diff=diff;
    	      tagr=&(TAGR->tagr[j]);
    	    }
    	  }       
    	} 
    }
