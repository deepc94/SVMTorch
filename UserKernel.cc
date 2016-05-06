//===////////////////////////////////////////////////////////////////////
//                                                                     //
//   SVMTorch II V1.77 [Ennastie]                                      //
//                                                                     //
//   Author: Ronan Collobert                                           //
//   Date: 20.11.2001                                                  //
//   Modified By: Deep Chakraborty                                     //
//   Modification date: 02.07.2015                                     //
//                                                                     //
//   Copyright (c) 2001  IDIAP & DIRO U. de Montreal                   //
//                       All rights reserved                           //
//                                                                     //
//   This software is available for non-commercial use only. It must   //
//   not be modified and distributed without prior permission of the   //
//   author. The author is not responsible for implications from the   //
//   use of this software.                                             //
//                                                                     //
////////////////////////////////////////////////////////////////////===//


#include "UserKernel.h"

UserKernel::UserKernel(SVM &svm_) : Kernel(svm_)
{
  id = 4;
  setParametres("10"); //dummy parameter to maintain structure
  //precalc_alloc = false;
}

void UserKernel::init() //dummy function
{
 /* precalc = new real[svm.n_train_examples];
  cout << "# Precalculating...";
  cout.flush();
  for(int i = 0; i < svm.n_train_examples; i++)
    precalc[i] = dot(i, i);
  cout << "OK\n";

  precalc_alloc = true;*/
}

void UserKernel::setParametres(string u)  //dummy function
{
  real std = atof(u.c_str());
  g = 1./(2*std*std);
}

void UserKernel::getParametres(string &u)  //dummy function
{
  char *truc;
  truc = new char[100];
  sprintf(truc, "%g", 1./(sqrt(2*g)));
  u = truc;
} 
real UserKernel::evalue(int i, int j)
{   
  real *ptr_i = svm.data[i]; 
  return(ptr_i[j]);
  //return(exp(g*( 2.*dot(i,j)-precalc[i]-precalc[j] )));
}

real UserKernel::evalue(real *x, int j)
{
  real *ptr_i = x; //pointer to a row of the test kernel gram matrix
  /*int i=0; 
  while(ptr_i[i] != NULL)
  {
    cout<<ptr_i[i]<<" ";
    i++;
  }*/
  //cout<<"\n ptr_i["<<j<<"] = "<<ptr_i[j]<<endl;
  return(ptr_i[j]); // j is the index of the support vector,
                    // thus it returns the jth element (column) of the ith row

  /*real precalc_x = 0;
  for(int t = 0; t < svm.n_input_dim; t++)
    precalc_x += x[t] * x[t];

  return(exp(g*( 2.*dotStandard(x,j)-precalc_x-precalc[j] )));*/
}

real UserKernel::evalue(sreal *x, int j)
{
  sreal *ptr_i = x; 
  real sum = 0;
  while( (ptr_i->indice != -1) && (j != -1) )
  {
    if(ptr_i->indice == j)
    {
      sum = ptr_i->valeur;
      ptr_i++;
    }
    else
    {
      if(ptr_i->indice > j)
        ptr_i--;
      else
        ptr_i++;
    }
  }
  return(sum);
 /* real precalc_x = 0;
  sreal *ptr_x = x;
  while( ptr_x->indice != -1 )
  {
    precalc_x += ptr_x->valeur * ptr_x->valeur;
    ptr_x++;
  }

  return(exp(g*( 2.*dotSparse(x,j)-precalc_x-precalc[j] )));*/
}

UserKernel::~UserKernel()
{
  /*if(precalc_alloc)
    delete[] precalc;*/
}
