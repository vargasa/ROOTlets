{

  fMain = new TGMainFrame(gClient->GetRoot(),400,300,kVerticalFrame);
  fMain->SetWindowName("T\315tulo de la ventana");
  fMain->SetIconPixmap("$ROOTSYS/icons/info.gif");
  
  fMain->MapWindow();

}
//_________________________________________________________

{
  //Se crea y configura la ventana principal
  fMain = new TGMainFrame(gClient->GetRoot(),120,100,kVerticalFrame);
  fMain->SetWMSizeHints(120,110,120,100,0,0);
  fMain->SetWindowName("Ejemplo SetLayoutBroken");
  //Se ejecuta el m\'etodo SetLayoutBroken
  fMain->SetLayoutBroken(kTRUE);

  //Se crea un bot\'on de texto
  fButton = new TGTextButton(fMain,"SetLayoutBroken");
  //Se modifica su tama\~no y se mueve
  fButton->Resize(100,20);
  fButton->Move(10,70);
  
  //Se muestran los resultados
  fMain->AddFrame(fButton);
  fMain->MapSubwindows();
  fMain->MapWindow();
  
}

//_________________________________________________________
{

  //Se crea y configura una ventana principal
  fMain = new TGMainFrame();
  fMain->SetWMSizeHints(200,50,400,100,10,10);

  fButton = new TGTextButton(fMain,"Objeto Expandido");
  
  Expandir = new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,5,5,5,5);

  fMain->AddFrame(fButton,Expandir);

  //Se mapea los objetos de la ventana
  fMain->MapSubwindows();
  //Se activa el mecanismo de las capas
  fMain->Resize();
  //Se muestra la ventana
  fMain->MapWindow();

}
//_________________________________________________________
{

  //Se crea y configura una ventana principal
  fMain = new TGMainFrame();
  fMain->SetWMSizeHints(200,50,400,100,10,10);

  //Se cre un bot\'on
  fButton1 = new TGTextButton(fMain,"Bot\363n 1");
  fButton2 = new TGTextButton(fMain,"Bot\363n 2");

  //Se crea una capa que se expande a lo largo
  //de los ejes horizontal (x) y vertical (y)
  Centrar = new TGLayoutHints(kLHintsCenterX,5,5,5,5);

  //Se agrega el bot\'on y se establece
  //la capa que usa.
  fMain->AddFrame(fButton1,Centrar);
  fMain->AddFrame(fButton2,Centrar);

  //Se mapea los objetos de la ventana
  fMain->MapSubwindows();
  //Se activa el mecanismo de las capas
  fMain->Resize();
  //Se muestra la ventana
  fMain->MapWindow();

}
//_________________________________________________________
