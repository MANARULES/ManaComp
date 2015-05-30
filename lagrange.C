#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "gnuplot_i.hpp"
#include <functional>
#include "TF1.h"

using namespace std;

class action{
	public:
		action(double,double,double,double,const function<double(double,double)> &);
    action(double ,double ,double ,double , TF1*);
		void lagrange1();
    void set_conditions(int,int,int,int);
    void graph_gnuplot(int ,int);
    void set_results(vector<double> , vector<double> ,vector<double> );
    //void draw_root();
	private:
    //Lagrangeano
    function<double(double,double)> lag;
    TF1 *lag2;
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
action::action(double x_i,double x_f,double t_i,double t_f, const function<double(double,double)> &langr){
	xi = x_i;
	xf = x_f;
	ti = t_i;
	tf = t_f;
  lag =langr;
}

action::action(double x_i,double x_f,double t_i,double t_f, TF1* langr){
  xi = x_i;
  xf = x_f;
  ti = t_i;
  tf = t_f;
  lag2 =langr;
};
//Set initial conditions
void action::set_conditions(int a,int b, int c , int d){
  xi = a;
	xf = b;
	ti = c;
	tf = d;
}

void action::set_results(vector<double> t1, vector<double> x1,vector<double> vx1){
  t = t1;
  x = x1;
  vx = vx1;
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


void action::graph_gnuplot(int a, int b){
  
  lag(5,9);
  try
  {
    Gnuplot g1("lines");
    g1.set_grid();
    g1.set_style("lines").plot_xy(t,x,"x(t)");
    
    Gnuplot g2("lines");
    g2.set_grid();
    g2.set_style("lines").plot_xy(t,vx,"x(t)");
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

//Create the langrangian

double grave(double a, double b){
  double cenas;
  cenas = 20*b*b+50*a*a;
  cout << "cenas" << cenas << endl;
  return cenas;
}



//Here begins the main function
int main(int argc, char *argv[]){
  TF1 *lag = new TF1("lagrangeano",argv[1]);
	action a1 = action(0,0,1,1,&grave);
  double tempoarray[] = {0,1,2,3,4,5,6,7,8,9,10};
  double qarray[] = {3,4,5,6,7,3,4,5,2,1,3};
  double qpontoarray[] = {5,4,3,2,1,0,5,6,4,3,3};
  vector<double> tempo(begin(tempoarray),end(tempoarray));
  vector<double> q(begin(qarray),end(qarray));
  vector<double> qponto(begin(qpontoarray),end(qpontoarray));
  
  a1.set_results(tempo,q,qponto);
  a1.graph_gnuplot(0,0);
  
}
