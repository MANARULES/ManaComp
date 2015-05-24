#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "gnuplot_i.hpp"
//#include "TCanvas.h"
//#include "TF1.h"

using namespace std;

class action{
	public:
		action(double,double,double,double);
		void lagrange1();
    void set_conditions(int,int,int,int);
    void graph_gnuplot(int , vector<double> &,vector<double> &, vector<double> &,int, int ,int, int );
    //void draw_root();
	private:
		//Initial Conditions:
		double xi;
		double xf;
		double ti;
		double tf;
		//Results
		vector<double> x;
		vector<double> vx;
		vector<double> t;
    vector<double> dx;
    vector<double> dvx;

};


//Constructor with initial conditions
action::action(double x_i,double x_f,double t_i,double t_f ){
	xi = x_i;
	xf = x_f;
	ti = t_i;
	tf = t_f;
}

//Set initial conditions
void action::set_conditions(int a,int b, int c , int d){
  xi = a;
	xf = b;
	ti = c;
	tf = d;
}

//Plot
/*void action::Draw(int n, double t[],double x[], double vx[]){

	TGraphsErrors gr(n,t,x,dx);
	gr.SetMarkerColor(2);
  gr.SetMarkerStyle(20);
  gr.SetMarkerSize(1.0);
  gr.GetXaxis().SetTitle("Whatever X");
  gr.GetYaxis().SetTitle("Whatever Y");
	gr.Draw("Plot");
}*/

void action::graph_gnuplot(int n, vector<double> &t2,vector<double> &x, vector<double> &dx,int begin_x, int end_x,int begin_y, int end_y){
  
  vector<pair<double, double> > xy_pts_A;
  vector<pair<double, double> > xy_pts_B;

  for(double i=0; i<n; i++) {
    xy_pts_A.push_back(make_pair(t2[i], x[i]));
    xy_pts_B.push_back(make_pair(t2[i], dx[i]));
  }
  
  cout << "t0 = "<<t2[0] << "t8 =" << t2[8] << endl;
  cout << "x2 = "<<x[2] << "x8 = "<< x[8] << endl;
  cout << "dx3 = "<<dx[3] << "dx8 =" << dx[8] << endl;
  cout << "Size t:" << t2.size() << endl;
  cout << "Size x:" << x.size() << endl;
  
  try
  {
    Gnuplot g1("lines");
    g1.set_grid();
    g1.set_style("points").plot_xy(t2,x,"x(t)");
  }
  catch (GnuplotException ge)
  {
    cout << ge.what() << endl;
  }
  
}


// Here begins the lagrange1 function
/*void action::lagrange1()
{
  //Variable Definition
  vector<double> x, xdot, S;
  double xi, xf, ti, tf; //initial conditions
  int n = 1000;
  double deltat=0,deltax=0, epsilon = 0.001,delta=0.001, action=0, aux1=xi; //needed parameters
  TF2 *lagrangian = new TF1("lagrangian", pow(y,2)+mgx); //?

  //Testing invariance of the Lagrangian in the interval
  //while(lagrangian->Evaluate)

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
    }
}
//Here ends the lagrange1 funcion
*/

//Here begins the main function
int main(){
	action a1 = action(0,0,1,1);
  vector<double> x(11,3.0);
  vector<double> y(11,5.0);
  int myints[] = {0,1,2,3,4,5,6,7,8,9,10};
  vector<double> test (myints, myints + sizeof(myints) / sizeof(int) );
  a1.graph_gnuplot(11,test,x,y,0,10,0,10);
	
}
