//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas
// Update: 2013-06-05 18:31:10-0500
// Copyright: 2013 (C) Andrés Vargas
//
//
#ifndef __CINT__
#ifndef ROOT_TApplication
#include "TApplication.h"
#endif
#endif

#ifdef __CINT__
#include "ExSlider1.cxx"
#else
#include "ExSlider1.h"
#endif

int RunExSlider1()
{
  ExSlider1 *appsl = new ExSlider1();
  return 0;
}

#ifndef __CINT__
int main(int argc, char** argv)
{
  TApplication RunExSlider1App("RunExSlider1App", &argc, argv);
  int retVal = RunExSlider1();
  RunExSlider1App.Run();
  return retVal;
}
#endif

//____________________________________________________________________ 
//  
// EOF
//
