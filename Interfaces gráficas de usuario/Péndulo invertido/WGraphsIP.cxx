/************************************************
 * Copyright: 2013 (C) Andrés Vargas            *
 * All rights reserved                          *
 * For the licensing terms see:                 * 
 * https://www.gnu.org/licenses/gpl-2.0.html    *
 ***********************************************/

#include "WGraphsIP.h"
#include "TGTab.h"
#include <iostream>

ClassImp(WGraphsIP);
//_________________________________________________________________________
WGraphsIP::~WGraphsIP(){};
//_________________________________________________________________________
WGraphsIP::WGraphsIP(const TGWindow *p, const TGWindow *main){

  TGLayoutHints *LHExpand = new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,5,5,5,5);
 
  TFGraphs = new TGTransientFrame(p,main,500,500);
  TFGraphs->SetWMSizeHints(500,500,1024,768,10,10);
  TFGraphs->SetWindowName("Gr\341ficas");
  TFGraphs->Connect("CloseWindow()","TGTransientFrame",TFGraphs,"DontCallClose()");
  TFGraphs->Connect("CloseWindow()","WGraphsIP",this,"Hidden()");

  CreateGraphs();

  TGTab *Tabs = new TGTab(TFGraphs);
  TGCompositeFrame *TabEnergy = Tabs->AddTab("Energ\355a");
  TGCompositeFrame *TabPhaseBase = Tabs->AddTab("Phase");
  TGCompositeFrame *TabPhi = Tabs->AddTab("Phi");
  TGCompositeFrame *TabPhiP = Tabs->AddTab("Phi'");

  CEnergy = new TRootEmbeddedCanvas("CEnergy",TabEnergy,400,400);
  CPhaseBase = new TRootEmbeddedCanvas("CPhaseBase",TabPhaseBase,400,400);
  CPhi = new TRootEmbeddedCanvas("CPhi",TabPhi,400,400);
  CPhiP = new TRootEmbeddedCanvas("CPhiP",TabPhiP,400,400);

  TabEnergy->AddFrame(CEnergy,LHExpand);
  TabPhaseBase->AddFrame(CPhaseBase,LHExpand);
  TabPhi->AddFrame(CPhi,LHExpand);
  TabPhiP->AddFrame(CPhiP,LHExpand);
  
  TFGraphs->AddFrame(Tabs,LHExpand);
  TFGraphs->MapSubwindows();
  TFGraphs->Resize();
  TFGraphs->MapWindow();
  
}
//_________________________________________________________________________
void WGraphsIP::CreateGraphs(){

  //gROOT->SetStyle("Classic");
  //gROOT->SetStyle("Pub");
  //gROOT->SetStyle("Modern");

  GEnergyU = new TGraph();
  GEnergyU->SetTitle("Energ\355a");
  GEnergyU->SetMarkerColor(8);
  GEnergyU->SetLineColor(8);
  GEnergyU->SetFillStyle(0);

  GEnergyK2 = new TGraph();
  GEnergyK2->SetMarkerColor(9);
  GEnergyK2->SetLineColor(9);
  GEnergyK2->SetTitle("Energ\355a");
  GEnergyK2->SetFillStyle(0);
  GEnergyK1 = new TGraph();
  GEnergyK1->SetMarkerColor(6);
  GEnergyK1->SetLineColor(6);
  GEnergyK1->SetFillStyle(0);

  GEnergyE = new TGraph();
  GEnergyE->SetMarkerColor(7);
  GEnergyE->SetLineColor(7);
  GEnergyE->SetFillStyle(0);

  GPhaseBase = new TGraph();
  GPhaseBase->SetTitle("Diagrama de Fase Cuerpo Base");
  GPhaseBase->SetMarkerColor(2);
  GPhaseBase->SetLineColor(2);

  GPhi = new TGraph();
  GPhi->SetTitle("#Phi Vs t");
  GPhi->SetMarkerColor(4);
  GPhi->SetLineColor(4);

  GPhiP = new TGraph();
  GPhiP->SetTitle("#Phi' Vs t");
  GPhiP->SetMarkerColor(41);
  GPhiP->SetLineColor(41);

}
//_________________________________________________________________________
void WGraphsIP::SetHidden(Bool_t Opt){

  if(Opt){ TFGraphs->UnmapWindow(); }
  else { TFGraphs->MapWindow(); }

}
//_________________________________________________________________________
void WGraphsIP::CleanGraphs(){

  delete GEnergyK2;
  delete GEnergyK1;
  delete GEnergyU;
  delete GEnergyE;
  delete GPhaseBase;
  delete GPhi;
  delete GPhiP;

  CreateGraphs();

  // CEnergy->GetCanvas()->Update();
  // CPhaseBase->GetCanvas()->Update();
  // CPhi->GetCanvas()->Update();
  // CPhiP->GetCanvas()->Update();

}
