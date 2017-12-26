/************************************************
 * Copyright: 2013 (C) Andrés Vargas            *
 * All rights reserved                          *
 * For the licensing terms see:                 * 
 * https://www.gnu.org/licenses/gpl-2.0.html    *
 ***********************************************/

//NPM: Non Parabolic Movement
#include "WMainNPM.h"
#include "TApplication.h"

ClassImp(WMainNPM);
//_________________________________________________________________________
WMainNPM::WMainNPM(){
  
  //gBenchmark->Start("Load");

  //Creaci\'on y configuraci\'on de la ventana principal
  fMain = new TGMainFrame(gClient->GetRoot(),980,380);
  fMain->Connect("CloseWindow()","WMainNPM",this,"TBExitClicked()");
  fMain->SetWMSizeHints(980,380,980,380,0,0);
  fMain->SetCleanup(kDeepCleanup);
  fMain->SetWindowName("Movimiento No Tan Parab\363lico");

  TGVerticalFrame *VFMain = new TGVerticalFrame(fMain);
  //Marco que contendrá las 3 columnas
  TGHorizontalFrame *VF0 = new TGHorizontalFrame(VFMain);

  //Unas capas generales
  TGLayoutHints *LayoutA = new TGLayoutHints(kLHintsCenterX|
					     kLHintsCenterY,2,2,2,2);
  TGLayoutHints *LayoutB = new TGLayoutHints(kLHintsExpandX,0,0,0,0);

  //Columna1
  TGVerticalFrame *VFCol1 = new TGVerticalFrame(VF0);
  ECGPos = new TRootEmbeddedCanvas("ECGPos",VFCol1,300,300);
  CGPos = ECGPos->GetCanvas();
  CGPos->Range(0,0,10,10);
  EBody = new TEllipse();
  EBody->SetFillColor(2);
  //http://root.cern.ch/root/html/TAttLine.html#TAttLine:SetLineStyle
  AV = new TArrow();
  AV->SetLineColor(2);
  AV->SetLineWidth(2);
  AV->SetArrowSize(0.04);
  AV->SetOption(">");
  AXP = new TArrow();
  AXP->SetLineColor(2);
  AXP->SetLineStyle(3);
  AYP = new TArrow();
  AYP->SetLineColor(2);
  AYP->SetLineStyle(3);
  AW = new TArrow();
  AW->SetLineWidth(2);
  AW->SetArrowSize(0.04);
  AW->SetOption(">");
  AFe = new TArrow();
  AFe->SetArrowSize(0.04);
  AFe->SetOption(">");
  AFe->SetLineWidth(2);
  AFe->SetLineColor(3);
  AFrx = new TArrow();
  AFrx->SetLineColor(4);
  AFrx->SetLineStyle(3);
  AFry = new TArrow();
  AFry->SetLineStyle(3);
  AFry->SetLineColor(4);
  AFr = new TArrow();
  AFr->SetArrowSize(0.04);
  AFr->SetOption(">");
  AFr->SetLineColor(4);
  AFr->SetLineWidth(2);
  VFCol1->AddFrame(ECGPos,LayoutA);
  VF0->AddFrame(VFCol1);

  //Columna 2
  TGVerticalFrame *VFCol2 = new TGVerticalFrame(VF0);
  //Variables del cuerpo
  TGGroupFrame *GFBody = new TGGroupFrame(VFCol2, "Propiedades Esfera");
  TGHorizontalFrame *HF2 = new TGHorizontalFrame(GFBody);
  TGLabel *LMass = new TGLabel(HF2,"Masa [kg]:");
  NEMass = new TGNumberEntry(HF2);
  NEMass->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEMass->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEMass->SetNumber(0.100);
  NEMass->Resize(70,20);
  HF2->AddFrame(LMass,LayoutA);
  HF2->AddFrame(NEMass,LayoutA);
  TGHorizontalFrame *HF3 = new TGHorizontalFrame(GFBody);
  TGLabel *LRadio = new TGLabel(HF3,"Radio [m]:");
  NERadio = new TGNumberEntry(HF3);
  NERadio->Resize(70,20);
  NERadio->SetNumStyle(TGNumberFormat::kNESRealThree);
  NERadio->SetNumAttr(TGNumberFormat::kNEAPositive);
  NERadio->SetNumber(0.1);
  NERadio->Connect("ValueSet(Long_t)","WMainNPM",this,"NERadioValueSet()");
  HF3->AddFrame(LRadio,LayoutA);
  HF3->AddFrame(NERadio,LayoutA);
  GFBody->AddFrame(HF2,LayoutA);
  GFBody->AddFrame(HF3,LayoutA);
  VFCol2->AddFrame(GFBody,LayoutB);
  //Variables del medio
  TGGroupFrame *GFMed = new TGGroupFrame(VFCol2,"Propiedades del Medio");
  TGHorizontalFrame *HF4 = new TGHorizontalFrame(GFMed);
  TGLabel *LRho = new TGLabel(HF4,"Rho [kg/m^3]:");
  NERho = new TGNumberEntry(HF4);
  NERho->SetNumStyle(TGNumberFormat::kNESRealThree);
  NERho->SetNumAttr(TGNumberFormat::kNEAPositive);
  NERho->SetNumber(0.010);
  NERho->Resize(70,20);
  CBRho = new TGComboBox(HF4);
  //http://www.roymech.co.uk/Useful_Tables/Matter/Prop_Gas.htm
  //http://www.engineeringtoolbox.com/air-properties-d_156.html
  CBRho->AddEntry("Aire 0\260C 1atm",0);//1.293
  CBRho->AddEntry("Aire 20\260C 1atm",1);//1.2045
  CBRho->AddEntry("Oxigeno 20\260C 1atm",2);//1.331
  CBRho->AddEntry("Helio 20\260C 1atm",3);//0.1664
  CBRho->AddEntry("Vapor de Agua",4);//0.804
  CBRho->AddEntry("Otro...",5);
  CBRho->Connect("Selected(Int_t)","WMainNPM",this,"CBRhoSelected(Int_t)");
  CBRho->Select(1);
  CBRho->Resize(120,20);
  HF4->AddFrame(LRho,LayoutA);
  HF4->AddFrame(CBRho,LayoutA);
  HF4->AddFrame(NERho,LayoutA);
  TGHorizontalFrame *HF5 = new TGHorizontalFrame(GFMed);
  TGLabel *LCPull = new TGLabel(HF5,"c : ");
  NECPull = new TGNumberEntry(HF5);
  NECPull->SetNumStyle(TGNumberFormat::kNESRealThree);
  NECPull->SetNumber(0.5);
  HF5->AddFrame(LCPull,LayoutA);
  HF5->AddFrame(NECPull,LayoutA);
  GFMed->AddFrame(HF4,LayoutB);
  GFMed->AddFrame(HF5,LayoutB);
  VFCol2->AddFrame(GFMed,LayoutB);
  //Parámetros simulación
  TGGroupFrame *GFPar = new TGGroupFrame(VFCol2,"Par\341metros Simulaci\363n");
  TGHorizontalFrame *HF6 = new TGHorizontalFrame(GFPar);
  TGLabel *LGr = new TGLabel(HF6,"g [m/s^2]: ");
  NEGr = new TGNumberEntry(HF6);
  NEGr->Resize(70,20);
  NEGr->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEGr->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEGr->SetNumber(TMath::Gn());
  NEGr->SetState(kFALSE);
  CBGr = new TGComboBox(HF6);
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
  CBGr->Connect("Selected(Int_t)","WMainNPM",this,"CBGrSelected(Int_t)");
  CBGr->Select(3);
  CBGr->Resize(120,20);
  HF6->AddFrame(LGr,LayoutA);
  HF6->AddFrame(CBGr,LayoutA);
  HF6->AddFrame(NEGr,LayoutA);
  GFPar->AddFrame(HF6,LayoutB);
  TGHorizontalFrame *HF7 = new TGHorizontalFrame(GFPar);
  TGLabel *LDt = new TGLabel(HF7,"dt [s]:");
  NEDt = new TGNumberEntry(HF7);
  NEDt->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEDt->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEDt->SetNumber(0.005);
  HF7->AddFrame(LDt,LayoutB);
  HF7->AddFrame(NEDt,LayoutB);
  GFPar->AddFrame(HF7,LayoutB);
  CHBRastro = new TGCheckButton(HF7,"Mostrar Rastro");
  CHBRastro->SetState(kButtonDown);
  HF7->AddFrame(CHBRastro,LayoutA);
  TGHorizontalFrame *HF10 = new TGHorizontalFrame(GFPar);
  CHBVVel = new TGCheckButton(HF10,"Mostrar Vector Velocidad");
  CHBVVel->SetState(kButtonDown);
  CHBVForce = new TGCheckButton(HF10,"Mostrar Vectores de Fuerza");
  CHBVForce->SetState(kButtonDown);
  HF10->AddFrame(CHBVVel,LayoutA);
  HF10->AddFrame(CHBVForce,LayoutA);
  GFPar->AddFrame(HF10,LayoutB);
  VFCol2->AddFrame(GFPar,LayoutB);
  //Condiciones Iniciales
  TGGroupFrame *GFInitCond = new TGGroupFrame(VFCol2,"Condiciones Iniciales");
  TGHorizontalFrame *HF0 = new TGHorizontalFrame(GFInitCond);
  TGLabel *LX0 = new TGLabel(HF0,"x(t=0) [m]:");
  NEX0 = new TGNumberEntry(HF0);
  NEX0->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEX0->SetNumber(2.0);
  NEX0->Resize(70,20);
  NEX0->Connect("ValueSet(Long_t)","WMainNPM",this,"NEX0ValueSet()");
  TGLabel *LY0 = new TGLabel(HF0,"y(t=0) [m]:");
  NEY0 = new TGNumberEntry(HF0);
  NEY0->Resize(70,20);
  NEY0->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEY0->SetNumber(1.0);
  NEY0->Connect("ValueSet(Long_t)","WMainNPM",this,"NEY0ValueSet()");
  HF0->AddFrame(LX0,LayoutA);
  HF0->AddFrame(NEX0,LayoutA);
  HF0->AddFrame(LY0,LayoutA);
  HF0->AddFrame(NEY0,LayoutA);
  GFInitCond->AddFrame(HF0,LayoutB);
  TGHorizontalFrame *HF1 = new TGHorizontalFrame(GFInitCond);
  TGLabel *LV0 = new TGLabel(HF1,"v(t=0) [m/s]:");
  NEV0 = new TGNumberEntry(HF1);
  NEV0->Resize(70,20);
  NEV0->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEV0->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEV0->SetNumber(20.0);
  TGLabel *LAlpha = new TGLabel(HF1,"Alpha [\260]:");
  NEAlpha = new TGNumberEntry(HF1);
  NEAlpha->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEAlpha->SetNumber(80.0);
  NEAlpha->Resize(70,20);
  HF1->AddFrame(LV0,LayoutA);
  HF1->AddFrame(NEV0,LayoutA);
  HF1->AddFrame(LAlpha,LayoutA);
  HF1->AddFrame(NEAlpha,LayoutA);
  GFInitCond->AddFrame(HF1,LayoutB);
  VFCol2->AddFrame(GFInitCond,LayoutB);
  VF0->AddFrame(VFCol2);


  //Columna 3
  TGVerticalFrame *VFCol3 = new TGVerticalFrame(VF0);
  TGHorizontalFrame *HF8 = new TGHorizontalFrame(VFCol3);
  TGLabel *LGraph = new TGLabel(HF8,"Graficar ");
  TGComboBox *CBYGraph = new TGComboBox(HF8);
  CBYGraph->Connect("Selected(Int_t)","WMainNPM",this,"CBYGraphSelected(Int_t)");
  CBYGraph->AddEntry("x [m]",0);
  CBYGraph->AddEntry("y [m]",1);
  CBYGraph->AddEntry("t [s]",2);
  CBYGraph->AddEntry("U [jul]",3);
  CBYGraph->AddEntry("K [jul]",4);
  CBYGraph->AddEntry("E [jul]",5);
  CBYGraph->AddEntry("V [m/s]",6);
  CBYGraph->AddEntry("Vx [m/s]",7);
  CBYGraph->AddEntry("Vy [m/s]",8);
  CBYGraph->AddEntry("Frx [N]",9);
  CBYGraph->AddEntry("Fry [N]",10);
  CBYGraph->AddEntry("Fr [N]",11);
  //CBYGraph->AddEntry("P [Kg*m/s]",7);
  CBYGraph->Select(1);
  CBYGraph->Resize(80,20);
  TGLabel *LVs = new TGLabel(HF8," Vs ");
  TGComboBox *CBXGraph = new TGComboBox(HF8);
  CBXGraph->Connect("Selected(Int_t)","WMainNPM",this,"CBXGraphSelected(Int_t)");
  CBXGraph->AddEntry("x [m]",0);
  CBXGraph->AddEntry("y [m]",1);
  CBXGraph->AddEntry("t [s]",2);
  CBXGraph->AddEntry("U [jul]",3);
  CBXGraph->AddEntry("K [jul]",4);
  CBXGraph->AddEntry("E [jul]",5);
  CBXGraph->AddEntry("V [m/s]",6);
  CBXGraph->AddEntry("Vx [m/s]",7);
  CBXGraph->AddEntry("Vy [m/s]",8);
  CBXGraph->AddEntry("Frx [N]",9);
  CBXGraph->AddEntry("Fry [N]",10);
  CBXGraph->AddEntry("Fr [N]",11);
  //CBXGraph->AddEntry("P [Kg*m/s]",7);
  CBXGraph->Select(0);
  CBXGraph->Resize(80,20);
  HF8->AddFrame(LGraph,LayoutA);
  HF8->AddFrame(CBYGraph,LayoutA);
  HF8->AddFrame(LVs,LayoutA);
  HF8->AddFrame(CBXGraph,LayoutA);
  ECGraph = new TRootEmbeddedCanvas("ECGPos",VFCol3,300,300);
  CGraph = ECGraph->GetCanvas();
  VFCol3->AddFrame(HF8,LayoutA);
  VFCol3->AddFrame(ECGraph,LayoutA);
  VF0->AddFrame(VFCol3);

  TGHorizontalFrame *HF9 = new TGHorizontalFrame(VFMain);
  TBPlay = new TGTextButton(HF9,"&Simular");
  TBPlay->Connect("Clicked()","WMainNPM",this,"TBPlayClicked()");
  TBClear = new TGTextButton(HF9,"&Limpiar");
  TBClear->Connect("Clicked()","WMainNPM",this,"TBClearClicked()");
  TGTextButton *TBExit = new TGTextButton(HF9,"S&alir");
  TBExit->Connect("Clicked()","WMainNPM",this,"TBExitClicked()");
  HF9->AddFrame(TBPlay,LayoutA);
  HF9->AddFrame(TBClear,LayoutA);
  HF9->AddFrame(TBExit,LayoutA);

  VFMain->AddFrame(VF0,new TGLayoutHints(kLHintsExpandX,1,1,1,1));
  VFMain->AddFrame(HF9,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,1,1,1,1));

  fMain->AddFrame(VFMain,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,1,1,1,1));
  fMain->MapSubwindows();
  fMain->Resize();
  fMain->MapWindow();

  Cont = new TTimer(100);
  Cont->Connect("Timeout()","WMainNPM",this,"DoDraw()");
  GGraph = new TGraph();

  IsActive = -1;

  //gBenchmark->Show("Load");
  //gBenchmark->Reset();

}
//_________________________________________________________________________
void WMainNPM::NERadioValueSet(){

  EBody->SetR1(NERadio->GetNumber());
  EBody->SetR2(NERadio->GetNumber());
  CGPos->cd();
  EBody->Draw();
  CGPos->Update();

}
//_________________________________________________________________________
void WMainNPM::NEY0ValueSet(){

  EBody->SetY1(NEY0->GetNumber());
  CGPos->cd();
  EBody->Draw();
  CGPos->Update();

}
//_________________________________________________________________________
void WMainNPM::NEX0ValueSet(){

  EBody->SetX1(NEX0->GetNumber());
  CGPos->cd();
  EBody->Draw();
  CGPos->Update();

}
//_________________________________________________________________________
void WMainNPM::CBXGraphSelected(Int_t Opt){

  delete GGraph;
  GGraph = new TGraph();

  switch(Opt){
  case 0: GX = &X;
    break;
  case 1: GX = &Y;
    break;
  case 2: GX = &t;
    break;
  case 3: GX = &U;
    break;
  case 4: GX = &K;
    break;
  case 5: GX = &E;
    break;
  case 6: GX = &V;
    break;
  case 7: GX = &XP;
    break;
  case 8: GX = &YP;
    break;
  case 9: GX = &FFrx;
    break;
  case 10: GX = &FFry;
    break;
  case 11: GX = &FFr;
    break;
  }

}
//_________________________________________________________________________
void WMainNPM::CBYGraphSelected(Int_t Opt){

  delete GGraph;
  GGraph = new TGraph();

  switch(Opt){
  case 0: GY = &X;
    break;
  case 1: GY = &Y;
    break;
  case 2: GY = &t;
    break;
  case 3: GY = &U;
    break;
  case 4: GY = &K;
    break;
  case 5: GY = &E;
    break;
  case 6: GY = &V;
    break;
  case 7: GY = &XP;
    break;
  case 8: GY = &YP;
    break;
  case 9: GY = &FFrx;
    break;
  case 10: GY = &FFry;
    break;
  case 11: GY = &FFr;
    break;
  }

}
//_________________________________________________________________________
void WMainNPM::CBRhoSelected(Int_t Opt){

  NERho->SetState(kFALSE);

  switch(Opt){
  case 0: NERho->SetNumber(1.293); //Aire 0°C 1atm
    break;
  case 1: NERho->SetNumber(1.205); //Aire 20°C 1atm
    break;
  case 2: NERho->SetNumber(1.331); //Oxigeno 20°C 1atm
    break;
  case 3: NERho->SetNumber(0.1664); //Helio 20°C 1atm
    break;
  case 4: NERho->SetNumber(0.804); //Vapor de Agua
    break;
  case 5: NERho->SetState(kTRUE);
    break;
  }
  
}
//_________________________________________________________________________
void WMainNPM::CBGrSelected(Int_t Opt){

  switch(Opt){
  case 0: NEGr->SetNumber(274.0); //Sol
    break;
  case 1: NEGr->SetNumber(3.701); //Mercurio
    break;
  case 2: NEGr->SetNumber(8.870); //Venus
    break;
  case 3: NEGr->SetNumber(9.780); //Tierra
    break;
  case 4: NEGr->SetNumber(1.62); //Luna Terrestre
    break;
  case 5: NEGr->SetNumber(3.690); //Marte
    break;
  case 6: NEGr->SetNumber(23.12); //Jupiter
    break;
  case 7: NEGr->SetNumber(8.96); //Saturno
    break;
  case 8: NEGr->SetNumber(8.69); //Urano
    break;
  case 9: NEGr->SetNumber(11.00); //Neptuno
    break;
  case 10: NEGr->SetState(kTRUE); //Otro
  break;
  }

}
//_________________________________________________________________________
Double_t WMainNPM::Mod(Double_t CX,Double_t CY){

  return sqrt(pow(CX,2)+pow(CY,2));

}
//_________________________________________________________________________
Double_t WMainNPM::YPP(Double_t XP, Double_t YP){

  return (g*(Rho*(4.0*TMath::Pi()*pow(R,3)/3.0)-m) - 0.5*c*Rho*TMath::Pi()*pow(R,2)*Mod(XP,YP)*YP)/m;

}
//_________________________________________________________________________
Double_t WMainNPM::XPP(Double_t XP, Double_t YP){

  return (-0.5*c*Rho*TMath::Pi()*pow(R,2)*Mod(XP,YP)*XP)/m;

}
//_________________________________________________________________________
void WMainNPM::Disable(){
    TBClear->SetEnabled(kFALSE);
    NEMass->SetState(kFALSE);
    NERadio->SetState(kFALSE);
    NECPull->SetState(kFALSE);
    CBRho->SetEnabled(kFALSE);
    NERho->SetState(kFALSE);
    CBGr->SetEnabled(kFALSE);
    NEGr->SetState(kFALSE);
    NEDt->SetState(kFALSE);
    //CHBRastro->SetEnabled(kFALSE);
    NEDt->SetState(kFALSE);
    NEX0->SetState(kFALSE);
    NEY0->SetState(kFALSE);
    NEV0->SetState(kFALSE);
    NEAlpha->SetState(kFALSE);
}
//_________________________________________________________________________
void WMainNPM::Enable(){
    TBClear->SetEnabled(kTRUE);
    NEMass->SetState(kTRUE);
    NERadio->SetState(kTRUE);
    NECPull->SetState(kTRUE);
    CBRho->SetEnabled(kTRUE);
    //NERho->SetState(kTRUE);
    CBGr->SetEnabled(kTRUE);
    //NEGr->SetState(kTRUE);
    NEDt->SetState(kTRUE);
    CHBRastro->SetEnabled(kTRUE);
    CHBRastro->SetState(kButtonDown);
    NEDt->SetState(kTRUE);
    NEX0->SetState(kTRUE);
    NEY0->SetState(kTRUE);
    NEV0->SetState(kTRUE);
    NEAlpha->SetState(kTRUE);
}
//_________________________________________________________________________
void WMainNPM::TBClearClicked(){
  
  Enable();
  // GGraph->Print();
  delete GGraph;
  GGraph = new TGraph();
  TBPlay->SetText("&Simular");
  CGraph->Update();
  CGPos->Clear();
  CGPos->Update();
  IsActive=-1;

}
//_________________________________________________________________________
void WMainNPM::TBExitClicked(){

  Cont->TurnOff();
  gApplication->Terminate(0);

}
//_________________________________________________________________________
void WMainNPM::TBPlayClicked(){

  /*
    Existen tres estados:
    -1 = Simulación no iniciada: Se requiere inicializar variables
    0 = Simulación pausada
    1 = Simulación despausada: No se requiere inicializar variables
  */

  if (IsActive == -1){

    m = NEMass->GetNumber();
    R = NERadio->GetNumber();
    EBody->SetR1(R);
    EBody->SetR2(R);
    Rho = NERho->GetNumber();
    c = NECPull->GetNumber();
    g = NEGr->GetNumber();
    t = 0;
    dt = NEDt->GetNumber();
    X = NEX0->GetNumber();
    Y = NEY0->GetNumber();
    Alpha = NEAlpha->GetNumber()*TMath::Pi()/180;
    XP = NEV0->GetNumber()*cos(Alpha);
    YP = NEV0->GetNumber()*sin(Alpha);
    TBPlay->SetText("&Pausar");
    FW = -m*g;
    FFe = Rho*(4.0/3.0)*TMath::Pi()*pow(R,3)*g;
    Cont->TurnOn();
    Disable();
    IsActive = 0;

  }
  else if (IsActive == 0){
    Cont->TurnOff();
    TBPlay->SetText("&Continuar");
    TBClear->SetEnabled(kTRUE);
    IsActive = 1;
  }
  else if (IsActive == 1){
    TBPlay->SetText("&Pausar");
    TBClear->SetEnabled(kFALSE);
    IsActive = 0;
    Cont->TurnOn();
  }

 
}
//_________________________________________________________________________
void WMainNPM::DoDraw(){

  //gBenchmark->Start("DoDraw");

  Double_t kX1,kX2,kX3,kX4;
  Double_t kY1,kY2,kY3,kY4;
  Double_t kXP1,kXP2,kXP3,kXP4;
  Double_t kYP1,kYP2,kYP3,kYP4;

  //printf("*** %d \t %.16f \t %.16f \t%.4f\n",GGraph->GetN(),X,Y,t);
  
  for(Int_t i = 0; i < 14 ;i++){

    V = Mod(XP,YP);
    p = m*V;
    K = 0.5*m*pow(Mod(XP,YP),2);
    U = m*g*Y;
    E = K+U;
    FFrx = -0.5*c*Rho*TMath::Pi()*pow(R,2)*V*XP;
    FFry = -0.5*c*Rho*TMath::Pi()*pow(R,2)*V*YP;
    FFr = Mod(FFrx,FFry);

    kX1 = XP*dt;
    kXP1 = XPP(XP,YP)*dt;
    kY1 = YP*dt;
    kYP1 = YPP(XP,YP)*dt;
    
    kX2 = (XP+0.5*kXP1)*dt;
    kXP2 = XPP(XP+0.5*kXP1,YP+0.5*kYP1)*dt;
    kY2 = (YP+0.5*kYP1)*dt;
    kYP2 = YPP(XP+0.5*kXP1,YP+0.5*kYP1)*dt;
    
    kX3 = (XP+0.5*kXP2)*dt;
    kXP3 = XPP(XP+0.5*kXP2,YP+0.5*kYP2)*dt;
    kY3 = (YP+0.5*kYP1)*dt;
    kYP3 = YPP(XP+0.5*kXP2,YP+0.5*kYP2)*dt;
    
    kX4 = (XP+kXP3)*dt;
    kXP4 = XPP(XP+kXP3,YP+kYP3)*dt;
    kY4 = (YP+kYP3)*dt;
    kYP4 = YPP(XP+kXP3,YP+kYP3)*dt;

    X += (1.0/6.0)*kX1 + (1.0/3.0)*kX2 + (1.0/3.0)*kX3 + (1.0/6.0)*kX4;
    XP += (1.0/6.0)*kXP1 + (1.0/3.0)*kXP2 + (1.0/3.0)*kXP3 + (1.0/6.0)*kXP4; 
    Y += (1.0/6.0)*kY1 + (1.0/3.0)*kY2 + (1.0/3.0)*kY3 + (1.0/6.0)*kY4;
    YP += (1.0/6.0)*kYP1 + (1.0/3.0)*kYP2 + (1.0/3.0)*kYP3 + (1.0/6.0)*kYP4; 
    
    t += dt;
  }

  GGraph->SetPoint(GGraph->GetN(),*GX,*GY);

  CGPos->cd();
  //CGPos->Range(X-10,Y-10,X+10,Y+10);//Viajar sobre el cuerpo
  EBody->SetX1(X);
  EBody->SetY1(Y);

  Float_t ks1 = 0.5;//Factor de Escala Velocidad
  Float_t ks2 = 3.0;//Factor de Escala Fuerza

  if (CHBVVel->IsDown()){
    
    AXP->SetX1(X);
    AXP->SetY1(Y);
    AXP->SetX2(X+ks1*XP);
    AXP->SetY2(Y);
    
    AYP->SetX1(X);
    AYP->SetY1(Y);
    AYP->SetX2(X);
    AYP->SetY2(Y+ks1*YP);
    
    AV->SetX1(X);
    AV->SetY1(Y);
    AV->SetX2(X+ks1*XP);
    AV->SetY2(Y+ks1*YP);
    
    AXP->Draw();
    AYP->Draw();
    AV->Draw();
    
  }
      
  if (CHBVForce->IsDown()){
    
    AW->SetX1(X);
    AW->SetY1(Y);
    AW->SetX2(X);
    AW->SetY2(Y+ks2*FW);
    
    AFe->SetX1(X);
    AFe->SetY1(Y);
    AFe->SetX2(X);
    AFe->SetY2(Y+ks2*FFe);
    
    AFrx->SetX1(X);
    AFrx->SetY1(Y);
    AFrx->SetX2(X+ks2*FFrx);
    AFrx->SetY2(Y);
    
    AFry->SetX1(X);
    AFry->SetY1(Y);
    AFry->SetX2(X);
    AFry->SetY2(Y+ks2*FFry);
    
    AFr->SetX1(X);
    AFr->SetY1(Y);
    AFr->SetX2(X+ks2*FFrx);
    AFr->SetY2(Y+ks2*FFry);

    AW->Draw();
    AFr->Draw();
    AFe->Draw();
    AFrx->Draw();
    AFry->Draw();
  }

  EBody->Draw();
  if (CHBRastro->IsDown()){
    EBody = new TEllipse(X,Y,R,R);
    EBody->SetFillColor(2);
  }
  CGPos->Update();


  CGraph->cd();
  GGraph->Draw("AC*");
  CGraph->Update();
  //gBenchmark->Show("DoDraw");
  //gBenchmark->Reset();

}
//_________________________________________________________________________
