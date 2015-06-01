#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "gnuplot_i.hpp"
#include <functional>
#include "TF1.h"
#include "TF2.h"

using namespace std;

class action{
public:
  action(double,double,double,double,const function<double(double,double)> &);
  action(double ,double ,double ,double , TF2*);
  void lagrange1();
  void set_conditions(int,int,int,int);
  void graph_gnuplot(int ,int,string c);
  void set_results(vector<double> , vector<double> ,vector<double> );
  //void draw_root();
  vector<double> getresults(int a){ if (a == 1)return x; else return t;};
private:
  //Lagrangeano
  function<double(double,double)> lag;
  TF2 *lag2;
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

action::action(double x_i,double x_f,double t_i,double t_f, TF2* langr){
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


void action::graph_gnuplot(int a, int b, string c){
  
  cout << t.size() << endl;
  cout << "x" << x.size() << endl;
  try
  {
    if ( a != 0)
    {
      Gnuplot g1("lines");
      g1.set_grid();
      g1.set_style("lines").plot_xy(t,x,"x(t)");
    }
    if( b != 0){
      Gnuplot g2("lines");
      g2.set_grid();
      g2.set_style("lines").plot_xy(t,vx,"vx(t)");
    }
    if ( c != NULL){
      Gnuplot g3("lines");
      g3.set_grid();
      g3.plot_equation(c,c);
    }
  }
  catch (GnuplotException ge)
  {
    cout << ge.what() << endl;
  }
  
}


// Here begins the lagrange1 function
void action::lagrange1()
{
  //Variable Definition
  vector<double> xp, xdot, S, points, time ;
  int n = 1000;
  double deltat=0,deltax=0, epsilon=5, delta=0.01, aux, x1, x2, xdot1, xdot2, xm1, xm2;
  TF2 *lagrangian = lag2;
  double action = 0;
  
  //Testing invariance of the Lagrangian in the interval */queremos que o lagrangiano se mantenha aproximadamente constante no intervalo*/
  //while(lagrangian->Evaluate(
  
  //Defining vector of positions and vector of velocities while calculating action for the first time
  deltat=(tf-ti)/n;
  deltax=(xf-xi)/n;
  points.push_back(xi);
  time.push_back(ti);
  cout << "deltat" << deltat<< endl;
  points[0] = xi;
  for(int i=1; i<=n; i++)
  {
    //cout << "action: " << action << endl;
    time.push_back(ti+deltat*i);
    points.push_back(xi+i*deltax); //extremal points of the interval
    xdot.push_back(deltax/deltat); //constant velocity in this case
    xp.push_back((points[i]+points[i-1])/2); //medium point of the interval
    S.push_back(deltat*(lagrangian->Eval(xp[i-1],xdot[i-1],0))); //action in each small interval
    action = action + S[i-1]; //sum of action in each interval
    
  }
  
  cout << "action: " << action << endl; //total action when using straight line to connect the points
  
  //Minimizing action for each small interval
  for(int i=0; i<n; i++)
  {
    double k = points[i+1]; //keeps the value of the point to enter the iteration
    
    for(int j=1;j<100;j++) //increases values of position change
    {
      //Test interval for positive epsilon
      
      /*Como variar a posição de um ponto varia a acção no intervalo anterior e posterior a este ponto
       é necessário considerar uma minimização conjugada da acção nos dois intervalos daí a utilização
       de variáveis 1 e 2. Para além disso, em cada iteração testa-se aumentar a posição e diminui-la. O valor extremo de j no for é relativo...*/
      
      x1 = k+j*epsilon;
      xdot1 = (x1-points[i])/deltat;
      xm1 = (points[i]+x1)/2;
      
      x2 = k+j*epsilon;
      xdot2 = (points[i+2]-x2)/deltat;
      xm2 = (points[i+2]+x2)/2;
      
      aux = deltat*(lagrangian->Eval(xm1,xdot1,0)+lagrangian->Eval(xm2,xdot2,0));
      
      if(S[i]+S[i+1]>aux)
      {
      	cout << "Ele passou por aqui." <<endl;
        points[i+1] = x1;
        xp[i] = xm1;
        xdot[i] = xdot1;
        
        xp[i+1]=xm2;
        xdot[i+1] = xdot2;
        
        double a = S[i];
        double b = S[i+1];
        
        S[i]=deltat*(lagrangian->Eval(xp[i],xdot[i],0));
        S[i+1] = deltat*(lagrangian->Eval(xp[i+1],xdot[i+1],0));
        
        if((a+b)-(S[i]+S[i+1])<delta)
          break;
      }
      
      //Test interval for negative epsilon
      
      x1 = k-j*epsilon;
      xdot1 = (x1-points[i])/deltat;
      xm1 = (points[i]+x1)/2;
      
      x2 = k-j*epsilon;
      xdot2 = (points[i+2]-x2)/deltat;
      xm2 = (points[i+2]+x2)/2;
      
      aux = deltat*(lagrangian->Eval(xm1,xdot1,0)+lagrangian->Eval(xm2,xdot2,0));
      
      if(S[i]+S[i+1]>aux)
      {
      	cout << "Ele passou por aqui."<<endl;
        points[i+1] = x1;
        xp[i] = xm1;
        xdot[i] = xdot1;
        
        xp[i+1]=xm2;
        xdot[i+1] = xdot2;
        
        double a = S[i];
        double b = S[i+1];
        
        S[i]=deltat*(lagrangian->Eval(xp[i],xdot[i],0));
        S[i+1] = deltat*(lagrangian->Eval(xp[i+1],xdot[i+1],0));
        
        if((a+b)-(S[i]+S[i+1])<delta)
          break;
      }
      
    }

  }
  cout << points.size()<<endl;
  cout << time.size()<<endl;

  cout << "x" <<x.size()<<endl;
  x = points;
  t = time;
  
}

//Here ends the lagrange1 funcion


//Create the langrangian //If you don't want to use ROOT for the TF2!

double grave(double a, double b){
  double cenas;
  cenas = 20*b*b+50*a*a;
  cout << "cenas" << cenas << endl;
  return cenas;
}



//Here begins the main function
int main(int argc, char *argv[]){
  TF2 *lag;
  if( argc > 0)
    lag = new TF2("lagrangeano",argv[1]);
  else
    lag = new TF2("lagrangeano","y*y+x"); //Langragean por defeito
  
  double x_i,x_f,t_i,t_f;
  //Initail conditions
  if ( argc  > 5){
    x_i = atof(argv[2]);
    x_f = atof(argv[3]);
    t_i = atof(argv[4]);
    t_f = atof(argv[5]);
  }
  else{
    x_i = 10;
    x_f = 0;
    t_i = 0;
    t_f = 100;
  }
  action a1 = action(x_i,x_f,t_i,t_f,lag);
  a1.lagrange1();
  a1.graph_gnuplot(1,0,"0.25*x*x"); // The first argument is if you wanna plot x(t) i so just put 1 if not put 0. The second is the same but this time for xponto(t). O terceiro é um plot de uma função que ponhas lá, to compare  with the x(t) or xponto(t) real...
}
