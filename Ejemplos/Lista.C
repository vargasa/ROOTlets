#include <TGClient.h>
#include <RQ_OBJECT.h>

class TituloDeLista {

private:
  void CambiarTitulo(Int_t id);
  TGMainFrame *fMain;
 
public:
  TituloDeLista();

};

TituloDeLista::TituloDeLista(){

  //Se crea y configura la ventana principal
  fMain = new TGMainFrame(gClient->GetRoot(),200,80);
  fMain->SetLayoutBroken(kTRUE);

  //Se crea una lista de selecci\'on
  Lista = new TGComboBox(fMain);
  //Se modifica el tama\~no de la Lista
  //y luego se ubica en la ventana
  Lista->Resize(160,40);
  Lista->Move(20,20);

  //Se a\~naden items a la lista
  Lista->AddEntry("Opci\363n 1",1);
  Lista->AddEntry("Opci\363n 2",2);
  Lista->AddEntry("Opci\363n 3",3);
  
  //Se conecta la se\~nal
  Lista->Connect("Selected(Int_t)","TituloDeLista",
                 this,"CambiarTitulo(Int_t)");

  //Se selecciona la opci\'on que
  //tendr\'a al iniciar
  Lista->Select(3);

  //Se ejecutan los m\'etodos
  //para hacer visible los objetos
  fMain->AddFrame(Lista);
  fMain->MapSubwindows();
  fMain->MapWindow();

}

void TituloDeLista::CambiarTitulo(Int_t id){

  switch(id){
  case 1:{
    fMain->SetWindowName("Opci\363n 1");
  }
    break;
  case 2:{
    fMain->SetWindowName("Opci\363n 2");
  }
    break;
  case 3:{
    fMain->SetWindowName("Opci\363n 3");
  }
  }
  return kTRUE;
}


int Lista(){
  App = new TituloDeLista();
  return 0;
}
