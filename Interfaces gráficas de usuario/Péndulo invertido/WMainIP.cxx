/************************************************
 * Copyright: 2013 (C) Andrés Vargas            *
 * All rights reserved                          *
 * For the licensing terms see:                 * 
 * https://www.gnu.org/licenses/gpl-2.0.html    *
 ***********************************************/

#include "WMainIP.h"
#include "TMath.h"
#include "TAxis.h"
#include "TTimer.h"
#include "TApplication.h"

ClassImp(WMainIP);
//_________________________________________________________________________
WMainIP::~WMainIP(){}
//_________________________________________________________________________
WMainIP::WMainIP(){

  //gBenchmark->Start("Load");
  
  //gROOT->SetStyle("Classic");
  TGMainFrame *fMain = new TGMainFrame(gClient->GetRoot(),600,500);
  fMain->SetWMSizeHints(600,450,600,450,0,0);
  fMain->SetWindowName("P\351ndulo Invertido");
  fMain->SetCleanup(kDeepCleanup);
  fMain->Connect("CloseWindow()","WMainIP",this,"TBExitClicked()");
  SBar = new TGStatusBar(fMain); //BARRA DE ESTADO
  SBar->SetParts(3);

  TGHorizontalFrame *HFrame = new TGHorizontalFrame(fMain);
  TGVerticalFrame *VFInit = new TGVerticalFrame(HFrame);
  
  TGLayoutHints *LCenterX = new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,2,2,2,2);
  TGLayoutHints *LExpandX = new TGLayoutHints(kLHintsExpandX,2,2,5,5);

  TGGroupFrame *GFCPend = new TGGroupFrame(VFInit,"P\351ndulo ");

  TGHorizontalFrame * HF3 = new TGHorizontalFrame(GFCPend);
  TGLabel *LLenght = new TGLabel(HF3,"L [m]: ");
  NELenght = new TGNumberEntry(HF3);
  NELenght->SetNumStyle(TGNumberFormat::kNESRealThree);
  NELenght->SetNumAttr(TGNumberFormat::kNEAPositive);
  NELenght->SetNumber(1.000);
  NELenght->Connect("ValueSet(Long_t)","WMainIP",this,"ReDraw()");
  HF3->AddFrame(LLenght,LCenterX);
  HF3->AddFrame(NELenght,LCenterX);
  GFCPend->AddFrame(HF3,LExpandX);

 TGHorizontalFrame *HF5 = new TGHorizontalFrame(GFCPend);
  TGLabel *LMassPend = new TGLabel(HF5,"m [kg]: ");
  NEMassPend = new TGNumberEntry(HF5);
  NEMassPend->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEMassPend->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEMassPend->SetNumber(0.250);
  HF5->AddFrame(LMassPend,LCenterX);
  HF5->AddFrame(NEMassPend,LCenterX);
  GFCPend->AddFrame(HF5,LExpandX);

  TGHorizontalFrame *HF1 = new TGHorizontalFrame(GFCPend);
  TGLabel *LPhi0 = new TGLabel(HF1,"Phi(t=0) [\260]: ");
  NEPhi0 = new TGNumberEntry(HF1);
  NEPhi0->SetNumStyle(TGNumberFormat::kNESRealTwo);
  NEPhi0->SetNumber(-15.0);
  NEPhi0->Connect("ValueSet(Long_t)","WMainIP",this,"ReDraw()");
  HF1->AddFrame(LPhi0,LCenterX);
  HF1->AddFrame(NEPhi0,LCenterX);
  GFCPend->AddFrame(HF1,LExpandX);

  TGHorizontalFrame *HF2 = new TGHorizontalFrame(GFCPend);
  TGLabel *LPhiP0 = new TGLabel(HF2,"Phi'(t=0) [\260/s]: ");
  NEPhiP0 = new TGNumberEntry(HF2);
  NEPhiP0->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEPhiP0->SetNumber(0.0);
  HF2->AddFrame(LPhiP0,LCenterX);
  HF2->AddFrame(NEPhiP0,LCenterX);
  GFCPend->AddFrame(HF2,LExpandX);

  VFInit->AddFrame(GFCPend,LExpandX);

  TGGroupFrame *GFCBase = new TGGroupFrame(VFInit,"Base ");
  
  TGHorizontalFrame *HF4 = new TGHorizontalFrame(GFCBase);
  TGLabel *LMassBase = new TGLabel(HF4,"M [kg]: ");
  NEMassBase = new TGNumberEntry(HF4);
  NEMassBase->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEMassBase->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEMassBase->SetNumber(1.25);
  HF4->AddFrame(LMassBase,LCenterX);
  HF4->AddFrame(NEMassBase,LCenterX);
  GFCBase->AddFrame(HF4,LExpandX);
  
  TGHorizontalFrame *HF6 = new TGHorizontalFrame(GFCBase);
  TGLabel *LX0 = new TGLabel(HF6,"X(t=0) [m]: ");
  NEX0 = new TGNumberEntry(HF6);
  NEX0->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEX0->SetNumber(0.0);
  NEX0->Connect("ValueSet(Long_t)","WMainIP",this,"NEX0ValueSet(Long_t)");
  HF6->AddFrame(LX0,LCenterX);
  HF6->AddFrame(NEX0,LCenterX);
  GFCBase->AddFrame(HF6,LExpandX);
 
  TGHorizontalFrame *HF7 = new TGHorizontalFrame(GFCBase);
  TGLabel *LXP0 = new TGLabel(HF7,"X'(t=0) [m/s]: ");
  NEXP0 = new TGNumberEntry(HF7);
  NEXP0->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEXP0->SetNumber(0.0);
  HF7->AddFrame(LXP0,LCenterX);
  HF7->AddFrame(NEXP0,LCenterX);
  GFCBase->AddFrame(HF7,LExpandX);

  VFInit->AddFrame(GFCBase,LExpandX);

  /*
    Physical constants of Equatorial Gravity's planet on
    the solar system has been extracted from:
    "Global Earth Physics: A Handbook of Physical Constants"
    written by "Thomas J. Ahrens"
    LOCATE AT: file:///media/InfoHD/Books/Physics%20Complete/Geophysics/AGU%20Ref%20Shelf%201%20-%20Global%20Earth%20Physics%20A%20Handbook%20of%20Physical%20Constants%20%20-%20T.%20Ahrens.pdf
  */

  TGHorizontalFrame *HF8 = new TGHorizontalFrame(VFInit);
  TGLabel *LGr = new TGLabel(HF8,"g [m/s^2]: ");
  NEGr = new TGNumberEntry(HF8);
  NEGr->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEGr->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEGr->SetNumber(TMath::Gn());
  NEGr->SetState(kFALSE);
  //NEGr->SetWidth(100);
  CBGr = new TGComboBox(HF8);
  CBGr->AddEntry("Sol (274.0)",0);
  CBGr->AddEntry("Mercurio (3.701)",1);
  CBGr->AddEntry("Venus (8.870)",2);
  CBGr->AddEntry("Tierra (9.780)",3);
  CBGr->AddEntry("Luna (1.62)",4);
  CBGr->AddEntry("Marte (3.690)",5);
  CBGr->AddEntry("Jupiter (23.12)",6);
  CBGr->AddEntry("Saturno (8.96)",7);
  CBGr->AddEntry("Urano (8.69)",8);
  CBGr->AddEntry("Neptuno (11.00)",9);
  CBGr->AddEntry("Otro... ",10);
  CBGr->Connect("Selected(Int_t)","WMainIP",this,"CBGrSelected(Int_t)");
  CBGr->Select(3);
  CBGr->Resize(120,20);
  HF8->AddFrame(LGr,LCenterX);
  HF8->AddFrame(CBGr,LCenterX);
  HF8->AddFrame(NEGr,LCenterX);
  VFInit->AddFrame(HF8,LExpandX);

  // GFGraphs = new TGGroupFrame(VFInit,"Graphics");
  // VF1 = new TGVerticalFrame(GFGraphs);
  // CBGEnergy = new TGCheckButton(VF1,"Energy");
  // CBGEnergy->Connect("Clicked()","WMainIP",this,"CBGEnergyClicked()");
  // CBGPosition = new TGCheckButton(VF1,"Position");
  // CBGForce = new TGCheckButton(VF1,"Force Applied");
  // CBGPhi = new TGCheckButton(VF1,"Phi(t)");
  // VF1->AddFrame(CBGEnergy);
  // VF1->AddFrame(CBGPosition);
  // VF1->AddFrame(CBGForce);
  // VF1->AddFrame(CBGPhi);
  // GFGraphs->AddFrame(VF1);
  // VFInit->AddFrame(GFGraphs,LExpandX);

  TGHorizontalFrame *HF11 = new TGHorizontalFrame(VFInit);
  TGLabel *Ldt = new TGLabel(HF11,"dt [s]: ");
  NEdt = new TGNumberEntry(HF11);
  NEdt->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEdt->SetNumStyle(TGNumberFormat::kNESRealFour);
  NEdt->SetNumber(1e-3);
  NEdt->Resize(70,20);
  HF11->AddFrame(Ldt);
  HF11->AddFrame(NEdt);
  VFInit->AddFrame(HF11,LCenterX);

  CBGraphs = new TGCheckButton(VFInit,"Mostrar Gr\341ficas");
  CBGraphs->Connect("Clicked()","WMainIP",this,"CBGraphsClicked()");
  VFInit->AddFrame(CBGraphs,LCenterX);

  TGHorizontalFrame *HF9 = new TGHorizontalFrame(VFInit);
  TBPlay = new TGTextButton(HF9," &Simular ");
  TBPlay->Connect("Clicked()","WMainIP",this,"TBPlayClicked()");
  HF9->AddFrame(TBPlay,LCenterX);
  TBClear = new TGTextButton(HF9," &Limpiar ");
  TBClear->Connect("Clicked()","WMainIP",this,"TBClearClicked()");
  TBClear->SetEnabled(kFALSE);
  HF9->AddFrame(TBClear,LCenterX);
  TGTextButton *TBExit = new TGTextButton(HF9," S&alir ");
  TBExit->Connect("Clicked()","WMainIP",this,"TBExitClicked()");
  HF9->AddFrame(TBExit,LCenterX);
  VFInit->AddFrame(HF9,LExpandX);

  TGVerticalFrame *VF1 = new TGVerticalFrame(HFrame);
  fECanvas = new TRootEmbeddedCanvas("ECanvas",VF1,300,300);
  fCanvas = fECanvas->GetCanvas();
  fCanvas->SetFixedAspectRatio(kTRUE);
  fCanvas->Range(-2,-2,2,2);
  HSX0 = new TGHSlider(HFrame);
  HSX0->SetRange(-1000,1000);
  HSX0->SetScale(10);
  HSX0->Resize(150,20);
  HSX0->Connect("PositionChanged(Int_t)","WMainIP",this,"HSX0PositionChanged(Int_t)");
  VF1->AddFrame(fECanvas,LCenterX);
  VF1->AddFrame(HSX0,LCenterX);
  HFrame->AddFrame(VF1,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,1,1,1,1));

  //-- Animación --//

  l = NELenght->GetNumber();
  m = NEMassPend->GetNumber();
  M = NEMassBase->GetNumber();
  g = NEGr->GetNumber(); //Standard Acceleration of Gravity
  Phi0 = NEPhi0->GetNumber()*(TMath::Pi()/180.0);
  PhiP0 = NEPhiP0->GetNumber()*(TMath::Pi()/180.0);
  X0 = NEX0->GetNumber();
  XP0 = NEXP0->GetNumber();

  DMassPend = new TEllipse(X0 + l*sin(Phi0),l*cos(Phi0),.05,.05,0,360);
  DMassPend->SetFillColor(2);
  DMassPend->Draw();

  DMassBase = new TBox(X0-0.2,-0.1,X0+0.2,0.1);
  DMassBase->SetFillColor(9);
  DMassBase->Draw("l");

  TLine *DLine = new TLine(fCanvas->GetX1(),0,fCanvas->GetX2(),0);
  DLine->SetLineStyle(6);
  DLine->Draw();

  DLenght = new TLine(X0,0,X0 + l*sin(Phi0),l*cos(Phi0));
  DLenght->SetLineWidth(1);
  DLenght->Draw();

  //gPad->SetEditable(kFALSE);

  //-- Fin Animación --//

  //HFrame->AddFrame(fECanvas,LCenterX);
  HFrame->AddFrame(VFInit,LCenterX);

  fMain->AddFrame(HFrame,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,1,1,1,1));
  fMain->AddFrame(SBar,new TGLayoutHints(kLHintsExpandX,0,0,0,0));
  fMain->MapSubwindows();
  fMain->Resize();
  fMain->MapWindow();

  WGraphs = new WGraphsIP(gClient->GetRoot(),fMain);
  WGraphs->Connect("Hidden()","WMainIP",this,"HideGraphs()");
  GetObjectsGraphs();
  CBGraphs->SetState(kButtonDown);

  Cont = new TTimer(100);
  Cont->Connect("Timeout()","WMainIP",this,"DoDraw()");

  IsActive = -1;

  //gBenchmark->Show("Load");
  //gBenchmark->Reset();

}
//_________________________________________________________________________
void WMainIP::GetObjectsGraphs(){
  GEnergyU = WGraphs->GetGraphEnergyU();
  GEnergyK2 = WGraphs->GetGraphEnergyK2();
  GEnergyK1 = WGraphs->GetGraphEnergyK1();
  GEnergyE = WGraphs->GetGraphEnergyE();
  GPhaseBase = WGraphs->GetGraphPhaseBase();
  GPhi = WGraphs->GetGraphPhi();
  GPhiP = WGraphs->GetGraphPhiP();
  CGraphEnergy = WGraphs->GetCanvasEnergy();
  CGraphPhaseBase = WGraphs->GetCanvasPhaseBase();
  CGraphPhi = WGraphs->GetCanvasPhi();
  CGraphPhiP = WGraphs->GetCanvasPhiP();
}
//_________________________________________________________________________
void WMainIP::TBExitClicked(){

  Cont->TurnOff();
  gApplication->Terminate(0);

}
//_________________________________________________________________________
void WMainIP::TBClearClicked(){

  NELenght->SetState(kTRUE);
  NEMassPend->SetState(kTRUE);
  NEMassBase->SetState(kTRUE);
  NEPhi0->SetState(kTRUE);
  NEPhiP0->SetState(kTRUE);
  NEX0->SetState(kTRUE);
  NEXP0->SetState(kTRUE);
  NEdt->SetState(kTRUE);
  HSX0->SetState(kTRUE);
  CBGr->SetEnabled(kTRUE);
  TBPlay->SetText(" &Simular ");
  IsActive = -1;
  TBClear->SetEnabled(kFALSE);

  SBar->SetText("",0);
  SBar->SetText("",1);
  SBar->SetText("",2);

  WGraphs->CleanGraphs();
  GetObjectsGraphs();

  ReDraw(); 
  
}
//_________________________________________________________________________
void WMainIP::CBGrSelected(Int_t Opt){

  NEGr->SetState(kFALSE);

  switch(Opt){
  case 0:{
    //Sun Selected
    NEGr->SetNumber(274.0);
  }
  break;
  case 1:{
    //Mercury Selected
    NEGr->SetNumber(3.701);
  }
  break;
  case 2:{
    //Venus Selected
    NEGr->SetNumber(8.870);
  }
  break;
  case 3:{
    //Earth Selected
    NEGr->SetNumber(9.780);
  }
  break;
  case 4:{
    //Moon Selected
    NEGr->SetNumber(1.62);
  }
  break;
  case 5:{
    //Mars Selected
    NEGr->SetNumber(3.690);
  }
  break;
  case 6:{
    //Jupiter Selected
    NEGr->SetNumber(23.12);
  }
  break;
  case 7:{
    //Saturn Selected
    NEGr->SetNumber(8.96);
  }
  break;
  case 8:{
    //Uranus Selected
    NEGr->SetNumber(8.69);
  }
  break;
  case 9:{
    //Neptune Selected
    NEGr->SetNumber(11.00);
  }
  break;
  case 10:{
    NEGr->SetState(kTRUE);
  }
  break;
  }

}
//_________________________________________________________________________
void WMainIP::NEX0ValueSet(Long_t number){
  
  HSX0->SetPosition(NEX0->GetNumber()*1e3);
  ReDraw();

}
//_________________________________________________________________________
void WMainIP::HSX0PositionChanged(Int_t pos){

  NEX0->SetNumber(pos*1e-3);
  ReDraw();

}
//_________________________________________________________________________
void WMainIP::ReDraw(){
  
  l = NELenght->GetNumber();
  Phi0 = NEPhi0->GetNumber()*(TMath::Pi()/180.0);
  X0 = NEX0->GetNumber();

  fCanvas->cd();
  
  DMassPend->SetX1(X0 + l*sin(Phi0)); 
  DMassPend->SetY1(l*cos(Phi0));      
  DMassPend->Draw();
  
  DMassBase->SetX1(X0-0.2);
  DMassBase->SetX2(X0+0.2);
  DMassBase->Draw();
  
  DLenght->SetX1(X0);
  DLenght->SetY1(0);
  DLenght->SetX2(DMassPend->GetX1());
  DLenght->SetY2(DMassPend->GetY1());
  DLenght->Draw();

  fCanvas->Update();

}
//_________________________________________________________________________
void WMainIP::DoDraw(){

  //gBenchmark->Start("DoDraw");
  
  Double_t kPhi1,kPhi2,kPhi3,kPhi4;
  Double_t kPhiP1,kPhiP2,kPhiP3,kPhiP4;
  Double_t kX1,kX2,kX3,kX4;
  Double_t kXP1,kXP2,kXP3,kXP4;
  
  Double_t kPhi5,kPhi6,kPhi7;
  Double_t kPhiP5,kPhiP6,kPhiP7;
  Double_t kX5,kX6,kX7;
  Double_t kXP5,kXP6,kXP7;
  
  Double_t K2,K1,U;
  
  Int_t n = 100;
  
  for (Int_t i = 0; i < n; i++){
    //-- RK4 --//

    kPhi1 = PhiP * dt;
    kX1 = XP * dt;
    kPhiP1 = GetPhiPP(Phi,PhiP) * dt;
    kXP1 = GetXPP(Phi,PhiP) * dt;
    
    kPhi2 = (PhiP + 0.5*kPhiP1) * dt;
    kX2 = (XP + 0.5*kXP1) * dt;
    kPhiP2 = GetPhiPP(Phi+0.5*kPhi1, PhiP+0.5*kPhiP1) * dt;
    kXP2 = GetXPP(Phi+0.5*kPhi1, PhiP+0.5*kPhiP1) * dt;

    kPhi3 = (PhiP+0.5*kPhiP2) * dt;
    kX3 = (XP + 0.5*kXP2) * dt;
    kPhiP3 = GetPhiPP(Phi+0.5*kPhi2,PhiP+0.5*kPhiP2) * dt;
    kXP3 = GetXPP(Phi+0.5*kPhi1,PhiP+0.5*kPhiP2) * dt;

    kPhi4 = (PhiP + kPhiP3) * dt;
    kX4 = (XP + kXP3) * dt ;
    kPhiP4 = GetPhiPP(Phi+1*kPhi3,PhiP+1*kPhiP3) * dt;
    kXP4 = GetXPP(Phi+1*kPhi3,PhiP+1*kPhiP3) * dt;
    
    // 1/6 = 0.166666667
    Phi = Phi + (0.166666667)*(kPhi1+2*kPhi2+2*kPhi3+kPhi4);
    PhiP = PhiP + (0.166666667)*(kPhiP1+2*kPhiP2+2*kPhiP3+kPhiP4);
    X = X + (0.166666667)*(kX1+2*kX2+2*kX3+kX4);
    XP = XP + (0.166666667)*(kXP1+2*kXP2+2*kXP3+kXP4);
 
  }

  U = m*g*cos(Phi);
  K1 = 0.5*M*pow(XP,2);
  K2 = 0.5*(m)*pow(XP,2) - m*XP*l*PhiP*cos(Phi) + 0.5*m*pow(l*PhiP,2);
  t += dt;

  Int_t np = GEnergyU->GetN();

  GEnergyU->SetPoint(np,t,U);
  GEnergyK2->SetPoint(np,t,K2);
  GEnergyK1->SetPoint(np,t,K1);
  GEnergyE->SetPoint(np,t,U+K2+K1);
  GPhaseBase->SetPoint(np,X,M*XP);
  GPhi->SetPoint(np,t,Phi*180/TMath::Pi());
  GPhiP->SetPoint(np,t,PhiP*180/TMath::Pi());
  
  sprintf(STAll,"t = %.2f s",t);
  SBar->SetText(STAll,0);
  sprintf(STAll,"Phi = %.2f",TMath::Abs(Phi*180.0/(TMath::Pi())));
  SBar->SetText(STAll,1);
  sprintf(STAll,"X = %.2f m", X);
  SBar->SetText(STAll,2);
               
  DMassPend->SetX1(X + l*sin(Phi)); 
  DMassPend->SetY1(l*cos(Phi));      

  DMassBase->SetX1(X-0.2);
  DMassBase->SetX2(X+0.2);

  DLenght->SetX1(X);
  DLenght->SetY1(0);
  DLenght->SetX2(DMassPend->GetX1());
  DLenght->SetY2(DMassPend->GetY1());

  fCanvas->cd();
  //fCanvas->Range(X-2,-2,X+2,2); //Observador en la base

  DMassPend->Draw();
  DMassBase->Draw();
  DLenght->Draw();

  fCanvas->Update();
  
  CGraphEnergy->cd();
  GEnergyK2->SetTitle("Cin\351tica P\351ndulo");
  GEnergyK2->GetYaxis()->SetTitle("Energ\355a [Jul]\n\n\n");
  GEnergyK2->GetXaxis()->SetTitle("Tiempo [s]");
  GEnergyK2->Draw("ACP");
  GEnergyU->Draw("CP");
  GEnergyU->SetTitle("Potencial");
  GEnergyK1->Draw("CP");
  GEnergyK1->SetTitle("Cin\351tica Base");
  GEnergyE->Draw("CP");
  GEnergyE->SetTitle("Mec\341nica");
  CGraphEnergy->BuildLegend();
  CGraphEnergy->Update();
  
  CGraphPhaseBase->cd();
  GPhaseBase->GetXaxis()->SetTitle("X [m]");
  GPhaseBase->GetYaxis()->SetTitle("P [kg*m/s]\n\n\n");
  GPhaseBase->Draw("ACP");
  CGraphPhaseBase->Update();
  CGraphPhi->cd();
  GPhi->GetYaxis()->SetTitle("Phi [\260]\n\n\n");
  GPhi->GetXaxis()->SetTitle("t [s]");
  GPhi->Draw("ACP");
  CGraphPhi->Update();
  
  CGraphPhiP->cd();
  GPhiP->Draw("ACP");
  GPhiP->GetYaxis()->SetTitle("Phi' [\260/s]\n\n\n\n\n\n\n");
  GPhiP->GetXaxis()->SetTitle("t [s]");
  CGraphPhiP->Update();
  
  //gBenchmark->Show("DoDraw");
  //gBenchmark->Reset();
  
}
//_________________________________________________________________________
Double_t WMainIP::GetPhiPP(Double_t Phi,Double_t PhiP){

  Double_t f1, f2, f3, f4;

  f1 = 1/(l*(m+M)-l*m*pow(cos(Phi),2));
  f2 = (m+M)*g*sin(Phi);
  f3 = F*cos(Phi);
  f4 = -m*l*pow(PhiP,2)*sin(Phi)*cos(Phi);

  return f1*(f2+f3+f4);

}
//_________________________________________________________________________
Double_t WMainIP::GetXPP(Double_t Phi, Double_t PhiP){
  
  Double_t f1, f5, f6, f7;

  f1 = 1/(l*(m+M)-l*m*pow(cos(Phi),2));
  f5 = m*l*g*sin(Phi)*cos(Phi);
  f6 = l*F;
  f7 = -m*pow(l,2)*pow(PhiP,2)*sin(Phi);

  return f1*(f5+f6+f7);

}
//_________________________________________________________________________
void WMainIP::TBPlayClicked(){

  /*
    -1: No iniciada
    0: Pausada
    1: Continuada
  */

  if(IsActive == -1){

    NELenght->SetState(kFALSE);
    NEMassPend->SetState(kFALSE);
    NEMassBase->SetState(kFALSE);
    NEPhi0->SetState(kFALSE);
    NEPhiP0->SetState(kFALSE);
    NEX0->SetState(kFALSE);
    NEXP0->SetState(kFALSE);
    NEdt->SetState(kFALSE);
    CBGr->SetEnabled(kFALSE);
    HSX0->SetState(kFALSE);

    l = NELenght->GetNumber();
    m = NEMassPend->GetNumber();
    M = NEMassBase->GetNumber();
    g = NEGr->GetNumber(); //Standard Acceleration of Gravity
    Phi0 = NEPhi0->GetNumber()*(TMath::Pi()/180.0);
    PhiP0 = NEPhiP0->GetNumber()*(TMath::Pi()/180.0);
    X0 = NEX0->GetNumber();
    XP0 = NEXP0->GetNumber();
    t = 0;

    
    //GEnergyK2->SetMaximum(m*g*cos(Phi0));
    //GEnergyK2->SetMinimum(m*g*cos(Phi0));

    
    F = 0.0;
    //dt = 1e-4;
    dt = NEdt->GetNumber();
    
    Phi = Phi0;
    PhiP = PhiP0;
    
    X = X0;
    XP = XP0;

    Cont->TurnOn();
    IsActive = 0;

    TBPlay->SetText("&Pausar");
  }
  else if (IsActive == 0){
    Cont->TurnOff();
    TBPlay->SetText("&Continuar");
    TBClear->SetEnabled(kTRUE);
    IsActive = 1;
  }
  else if (IsActive == 1){
    Cont->TurnOn();
    TBPlay->SetText("&Pausar");
    TBClear->SetEnabled(kFALSE);
    IsActive = 0;
  }

}
//_________________________________________________________________________
void WMainIP::CBGraphsClicked(){

  WGraphs->SetHidden(!CBGraphs->IsDown());

}
