//____________________________________________________________________ 
//  
// $Id$ 
// Author: Andrés Vargas 
// Update: 2013-06-05 18:36:11-0500
// Copyright: 2013 (C) Andrés Vargas
//
//
#ifndef __CINT__
#ifndef ROOT_TApplication
#include "TApplication.h"
#endif
#endif

#ifdef __CINT__
#include "ExSlider2.cxx"
#else
#include "ExSlider2.h"
#endif

int RunExSlider2()
{
  ExSlider2 *appsl = new ExSlider2();
  return 0;
}

#ifndef __CINT__
int main(int argc, char** argv)
{
  TApplication RunExSlider2App("RunExSlider2App", &argc, argv);
  int retVal = RunExSlider2();
  RunExSlider2App.Run();
  return retVal;
}
#endif

//____________________________________________________________________ 
//  
// EOF
//
