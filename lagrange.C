#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void lagrange()
{
  //Variable Definition
  vector<double> x, xdot, S;
  double xi, xf, ti, tf; //initial conditions
  int n = 1000;
  double deltat=0,deltax=0, epsilon = 0.001,delta=0.001, action=0, aux1=xi; //needed parameters
  TF2 *lagrangian = new TF1("lagrangian", pow(y,2)+mgx);

  //Testing invariance of the Lagrangian in the interval
  //while(lagrangian->Evaluate(

  //Defining vector of positions and vector of velocities while calculating action for the first time 
  deltat=(tf-ti)/n;
  deltax=(xf-xi)/n;
  for(int i=0; i<1000; i++)
    {
      aux2=aux1+i*deltax;
      x.push_back((aux1+aux2)/2);
      aux1=aux1+i*deltax;
      xdot.push_back(deltax/deltat); //constant velocity in this case
      S=S+deltat*(lagrangian->Eval(x[i],xdot[i],0));
      action = action +S[i];
    }

  //Minimizing action for each small interval 
    for(int i=0; i<1000; i++)
    {
      for(double epsilon=-0.01; Sf-Si<delta; epsilon=epsilon+0.001)
	{
	  x[0]=x[0]+epsilon;
	  aux1=aux1+i*deltax;
	  xdot.push_back(deltax/deltat); //constant velocity in this case
	  S=S+deltat*(lagrangian->Eval(x[i],xdot[i],0));
    }
