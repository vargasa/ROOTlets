// -*- mode: c++ -*- 
//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas 
// Update: 2013-04-26 11:48:00-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef _IP__WMainIP
#define _IP__WMainIP

#include "TGClient.h"
#include "RQ_OBJECT.h"
#include "TGSlider.h"
#include "TGNumberEntry.h"
#include "TGStatusBar.h"
#include "TGComboBox.h"
#include "TGButton.h"
#include "TEllipse.h"
#include "TBox.h"
#include "TLine.h"
#include "WGraphsIP.h"
#include "TGLabel.h"
#include "TTimer.h"


class WMainIP {
  
  RQ_OBJECT("WMainIP");
  Int_t IsActive;
  TTimer *Cont;
  TGHSlider *HSX0;
  TGNumberEntry *NELenght,*NEMassPend,*NEMassBase,*NEPhi0,*NEPhiP0,*NEX0,*NEXP0,*NEGr,*NEdt;
  TGraph *GEnergyU,*GEnergyK2,*GEnergyK1,*GEnergyE,*GPhaseBase,*GPhi,*GPhiP;
  TGCheckButton *CBGraphs;
  TCanvas *CGraphEnergy,*CGraphPhaseBase,*CGraphPhi,*CGraphPhiP;
  TGStatusBar *SBar;
  TGComboBox *CBGr;
  TGTextButton *TBPlay,*TBClear;
  TGTransientFrame *TFGraphs;
  TRootEmbeddedCanvas *fECanvas;
  TCanvas *fCanvas;
  TCanvas *CGraphs;
  TBox *DMassBase;
  TEllipse *DMassPend;
  TLine *DLenght;
  Double_t l,m,M,g,Phi0,PhiP0,X0,XP0;
  Double_t F,Phi,PhiP,PhiPP,t,dt,X,XP,XPP;
  char STAll[50];
  void GetObjectsGraphs();

public:
  WMainIP();
  ~WMainIP();
  void TBExitClicked();
  void TBPlayClicked();
  void TBClearClicked();
  void ReDraw();
  void DoDraw();
  Double_t GetPhiPP(Double_t Phi,Double_t PhiP);
  Double_t GetXPP(Double_t Phi,Double_t PhiP);
  void CBGrSelected(Int_t Opt);
  void NEX0ValueSet(Long_t number);
  void HSX0PositionChanged(Int_t pos);
  void CBGraphsClicked();
  WGraphsIP *WGraphs;
  void HideGraphs();

  ClassDef(WMainIP,0);

};

inline void WMainIP::HideGraphs(){
  CBGraphs->SetState(kButtonUp);
}


#endif 

#ifdef __CINT__
#include "WMainIP.cxx"
#endif
//____________________________________________________________________ 
//  
// EOF
//
