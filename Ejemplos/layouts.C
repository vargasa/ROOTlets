{

  //Se crea y configura una ventana principal
  fMain = new TGMainFrame(gClient->GetRoot(),500,150,kHorizontalFrame);
  //fMain = new TGMainFrame();
  fMain->SetWMSizeHints(500,150,800,150,10,10);

  //Se cre un bot\'on
  fButton1 = new TGTextButton(fMain,"Ejemplo 1");
  fButton2 = new TGTextButton(fMain,"Ejemplo 2");

  //Se crea una capa que se expande a lo largo
  //de los ejes horizontal (x) y vertical (y)
  Centrar = new TGLayoutHints(kLHintsCenterX|kLHintsCenterY,5,5,5,5);

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
