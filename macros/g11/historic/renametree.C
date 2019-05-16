
void renametree(){

  
  TFile f("~/clas/rootfiles/nxyzREAL.root","update");
  TTree *T = (TTree*)f.Get("new");
   T->Write("mytree");

  // TFile f("~/clas/rootfiles/helicitySIM.root","update");
 // TTree *T = (TTree*)f.Get("g112kppim");
 // T->Write("mytree");







/*
TFile f("std.root","update");
 TTree *T = (TTree*)f.Get("g112kppim");
T->Write("mytree");

TFile f("dbg.root","update");
 TTree *T = (TTree*)f.Get("g112kppim");
T->Write("mytree");
  

TFile f("beam.root","update");
TTree *T = (TTree*)f.Get("new");
T->Write("mytree");


TFile f("beamfix.root","update");
TTree *T = (TTree*)f.Get("new");
T->Write("mytree");
  */

  //TFile f("my.root","update");
  //TTree *T = (TTree*)f.Get("g112kppim");
  //T->Write("mytree");

  //TFile f("helicity.root","update");
  //TTree *T = (TTree*)f.Get("new");
  //T->Write("mytree");

  //TFile f("helicitySIM.root","update");
  //TTree *T = (TTree*)f.Get("g112kppim");
  //T->Write("mytree");
}
