//____________________________________________________________________
//
// Example Slider 1
// 

//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas 
// Update: 2013-06-05 16:41:40-0500
// Copyright: 2013 (C) Andrés Vargas
//
#ifndef ___ExSlider1
#include "ExSlider1.h"
#endif

#ifndef ROOT_TMath
#include "TMath.h"
#endif

//____________________________________________________________________
ClassImp(ExSlider1);

//____________________________________________________________________
ExSlider1::ExSlider1()
{
  // Default constructor
  TGMainFrame *Ventana = new TGMainFrame(gClient->GetRoot());
  Ventana->SetWindowName("Ejemplo Slider");
  Ventana->SetWMSizeHints(300,300,300,300,0,0);

  TGLayoutHints *Centrar = new TGLayoutHints(kLHintsExpandX|
					     kLHintsExpandY|
					     kLHintsCenterX|
					     kLHintsCenterY,5,5,5,5);
  
  
  Lienzo = new TRootEmbeddedCanvas("Lienzo",Ventana,400,400);
  ApLienzo = Lienzo->GetCanvas();
  ApLienzo->Range(-10,-10,10,10);

  R = 5.0;

  Borde = new TEllipse(0.0,0.0,R,R,0,360);
  Borde->Draw();
  
  Circulo = new TEllipse(R,0.0,0.5,0.5,0,360);
  Circulo->SetFillColor(4);
  Circulo->Draw();

  MiSlider = new TGHSlider(Ventana);
  MiSlider->SetRange(-360.0,360.0);
  MiSlider->Connect("PositionChanged(Int_t)","ExSlider1",
		    this,"MoverPunto()");
  MiSlider->SetPosition(0.0);

  
  Ventana->AddFrame(Lienzo,Centrar);
  Ventana->AddFrame(MiSlider, new TGLayoutHints(kLHintsExpandX,5,5,5,5));
  
  Ventana->MapSubwindows();
  Ventana->Resize();
  Ventana->MapWindow();
}
//____________________________________________________________________ 
void ExSlider1::MoverPunto(){
  Circulo->SetX1(R*cos(MiSlider->GetPosition()*TMath::Pi()/180));
  Circulo->SetY1(R*sin(MiSlider->GetPosition()*TMath::Pi()/180));
  Circulo->Draw();
  ApLienzo->Update();
}


//____________________________________________________________________ 
//  
// EOF
//
