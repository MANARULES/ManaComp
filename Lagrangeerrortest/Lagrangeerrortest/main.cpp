void action::lagrange1()
{
  //Variable Definition
  vector<double> xp,xdot, S, points, time ;
  double xi, xf, ti, tf; //initial conditions
  int n = 1000;
  double deltat=0,deltax=0, epsilon=0.02, delta=0.01, aux, x1, x2, xdot1, xdot2, xm1, xm2;
  TF2 *lagrangian = new TF2("lagrangian", "pow(y,2)+x");
  double action;
  
  //Testing invariance of the Lagrangian in the interval */queremos que o lagrangiano se mantenha aproximadamente constante no intervalo*/
  //while(lagrangian->Evaluate(
  
  //Defining vector of positions and vector of velocities while calculating action for the first time
  deltat=(tf-ti)/n;
  deltax=(xf-xi)/n;
  points.push_back(xi);
  time.push_back(ti);
  for(int i=1; i<=n; i++)
  {
    time.push_back(ti+deltat*i);
    points.push_back(xi+i*deltax); //extremal points of the interval
    xdot.push_back(deltax/deltat); //constant velocity in this case
    xp.push_back((points[i]+points[i-1])/2); //medium point of the interval
    S.push_back(deltat*(lagrangian->Eval(xp[i],xdot[i],0))); //action in each small interval
    action = action + S[i]; //sum of action in each interval
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
      
      if(S[i]+S[i+1]>aux,0)
      {
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
  xp = points;
  t = time;
  cout << "xp" <<xp.size()<<endl;
  
  
}
