/*
  Sección: Ilustración Simple de la Comunicación entre Objetos
  Aplicación de un sólo botón
*/
//_____________________________________________________________
#include <TGClient.h>
#include <RQ_OBJECT.h>

class VUnBoton {
  RQ_OBJECT("VUnBoton");
  
public:   
  VUnBoton(Int_t w = 200, Int_t h = 200);
  
};

VUnBoton::VUnBoton(Int_t w,Int_t h){

  fMain = new TGMainFrame(gClient->GetRoot(),w,h);
  fMain->SetWindowName("Ventana 1");

  fButton = new TGTextButton(fMain,"Bot\363n");
  fButton->Connect("Clicked()","TGMainFrame",fMain,"CloseWindow()");
  fButton->Resize(w-10,h-10); 
  fButton->Move(5,5);

  fMain->AddFrame(fButton);
  fMain->MapSubwindows();
  fMain->MapWindow();

}

int UnBoton(){

  App = new VUnBoton(300,150);
  return 0;

}
//_____________________________________________________________
