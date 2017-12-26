/*
  Animaci\'on simple
  Secci\'on: Creando visualizaci\'on en la interfaz
*/

#include <TCanvas.h>
#include <TEllipse.h>
#include <TTimer.h>

TCanvas *Lienzo;
TEllipse *Circulo;
TTimer *Cronometro;
Int_t i;
//_______________________________________________________
void Desplazar(){

  Double_t RadioAnterior = Circulo->GetR1();
  //en cada ejecuci\'on se incrementa el radio
  //en 0.1 unidades
  Double_t NuevoRadio = RadioAnterior + 0.1;

  //i es un contador de cu\'antas veces
  //se ha ejecutado \'esta funci\'on
  i++;
  
  //Se cambia el color de relleno
  //del c\'irculo aprovechando el
  //contador i
  Circulo->SetFillColor(i);
  //Se establece el nuevo radio
  //al ser un c\'irculo r1=r2
  Circulo->SetR1(NuevoRadio);
  Circulo->SetR2(NuevoRadio);
  //Se dibuja en el lienzo
  Circulo->Draw();
  //Se actualiza el lienzo
  Lienzo->Update();

  //Detiene el cron\'ometro si se alcanza
  //un radio de 8 unidades
  if(Circulo->GetR1() >= 8) Cronometro->TurnOff(); 

}
//_______________________________________________________
void ttimer(){

  //Se crea y configura el lienzo
  Lienzo = new TCanvas();
  Lienzo->SetWindowSize(500,500);
  Lienzo->Range(-10,-10,10,10);
  
  //Se crea la elipse
  Circulo = new TEllipse(0,0,1,1,0,360);
  Circulo->Draw();
  //Se crea un cron\'ometro que ejecutar\'a
  //una funci\'on cada 200ms
  Cronometro = new TTimer(200);
  i = 0;
  //Se establece la funci\'on a ejecutar
  //en cada intervalo
  Cronometro->SetCommand("Desplazar()"); 
  Cronometro->TurnOn(); //Activar TTimer 

}
