/************************************************
 * Copyright: 2013 (C) Andrés Vargas            *
 * All rights reserved                          *
 * For the licensing terms see:                 * 
 * https://www.gnu.org/licenses/gpl-2.0.html    *
 ***********************************************/

#include "CaidaLibreGui.h"
#include "TGLabel.h"
#include "TApplication.h"
#include "TBenchmark.h"

void CaidaLibreGui::Exit() { gApplication->Terminate(0); }
CaidaLibreGui::CaidaLibreGui(){

  //Se crea y configura la ventana principal
  TGMainFrame *fMain = new TGMainFrame(gClient->GetRoot(),350,300,kHorizontalFrame);
  fMain->SetWMSizeHints(350,300,350,300,0,0);
  fMain->SetWindowName("Caso de Estudio: Ca\355da Libre");
  fMain->Connect("CloseWindow()","CaidaLibreGui",this,"Exit()");

  //Se crea y configura el Lienzo para la animaci\'on
  ECanvas = new TRootEmbeddedCanvas("ECanvas",fMain,155,280);
  //Definimos un "Acceso Directo" al canvas del canvas embebido
  fCanvas = ECanvas->GetCanvas();
  CuadrarRangoCanvas(10);

  E1 = new TEllipse(0,5,0.5,0.5);
  E1->SetFillColor(4);
  E1->Draw();

  //Se crea el espacio de los botones
  TGVerticalFrame *VF1 = new TGVerticalFrame(fMain);

  TGLayoutHints *CentrarEnX = new TGLayoutHints(kLHintsCenterX,2,2,2,2);
  TGHorizontalFrame *HFMasa = new TGHorizontalFrame(VF1);
  TGLabel *LMasa = new TGLabel(HFMasa,"Masa [kg] : ");  
  NEMasa = new TGNumberEntry(HFMasa);
  NEMasa->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEMasa->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEMasa->SetNumber(1.000);
  HFMasa->AddFrame(LMasa,CentrarEnX);
  HFMasa->AddFrame(NEMasa,CentrarEnX);

  TGHorizontalFrame *HFAltura = new TGHorizontalFrame(VF1);
  TGLabel *LAltura = new TGLabel(HFAltura,"Altura [m] : ");
  NEAltura = new TGNumberEntry(HFAltura);
  NEAltura->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEAltura->SetNumStyle(TGNumberFormat::kNESRealTwo);
  NEAltura->SetNumber(10.00);
  HFAltura->AddFrame(LAltura,CentrarEnX);
  HFAltura->AddFrame(NEAltura,CentrarEnX);

  TGHorizontalFrame *HFGravedad = new TGHorizontalFrame(VF1);
  TGLabel *LGravedad = new TGLabel(HFGravedad,"g [m/s^2] : ");
  NEGravedad = new TGNumberEntry(HFGravedad);
  NEGravedad->SetNumAttr(TGNumberFormat::kNEAPositive);
  NEGravedad->SetNumStyle(TGNumberFormat::kNESRealThree);
  NEGravedad->SetNumber(9.870);
  HFGravedad->AddFrame(LGravedad,CentrarEnX);
  HFGravedad->AddFrame(NEGravedad,CentrarEnX);
  
  TGPictureButton *PBPlay = new TGPictureButton(VF1,gClient->GetPicture("$ROOTSYS/icons/arrow_right.xpm"));
  PBPlay->Connect("Clicked()","CaidaLibreGui",this,"PBPlayClicked()");
  
  //TGLayoutHints *ExpandirEnXY = new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,10,10,10,10);
  TGLayoutHints *CentrarEnXY = new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,2,2,2,2);
  
  VF1->AddFrame(HFMasa,CentrarEnXY);
  VF1->AddFrame(HFAltura,CentrarEnXY);
  VF1->AddFrame(HFGravedad,CentrarEnXY);
  VF1->AddFrame(PBPlay,CentrarEnXY);

  fMain->AddFrame(ECanvas, new TGLayoutHints(kLHintsNoHints,10,10,10,10));
  fMain->AddFrame(VF1, new TGLayoutHints(kLHintsExpandX|kLHintsCenterY,10,10,10,10));

  Contador = new TTimer(100);
  Contador->Connect("Timeout()","CaidaLibreGui",this,"MNumerico()");

  fMain->MapSubwindows();
  fMain->Resize();
  fMain->MapWindow();

}
//____________________________________________________________________________
void CaidaLibreGui::CuadrarRangoCanvas(Double_t h){

  Double_t x0,x1,y0,y1,w;
  y0 = 0.0;
  y1 = h;
  w = (Double_t)fCanvas->GetXsizeReal();
  h = (Double_t)fCanvas->GetYsizeReal();
  x0 = -(w/h)*(y1-y0)/2.0;
  x1 = (w/h)*(y1-y0)/2.0;
  fCanvas->Range(x0,y0,x1,y1);  

}
//____________________________________________________________________________
void CaidaLibreGui::PBPlayClicked(){

  //Se cargan las variables
  g = -1*NEGravedad->GetNumber();
  m = NEMasa->GetNumber();
  h = NEAltura->GetNumber();
  dt = 0.1;
  YP = 0.0;
  Y = h;
  CuadrarRangoCanvas(h+(0.2*h));
  fCanvas->Clear();
  Contador->TurnOn();
  
}
//____________________________________________________________________________
void CaidaLibreGui::MNumerico(){
  
  YP += g*dt;
  Y += YP*dt;
  NEAltura->SetNumber(Y);
  //Establecemos el radio del c\'irculo
  //proporcionales a la altura
  E1->SetR1(0.05*h);
  E1->SetR2(0.05*h);
  E1->SetY1(Y);
  E1->Draw();
  E1 = new TEllipse(0,Y,0.05*h,0.05*h);
  E1->SetFillColor(4);
  fCanvas->Update();

  if(Y<=0) Contador->TurnOff();
}
