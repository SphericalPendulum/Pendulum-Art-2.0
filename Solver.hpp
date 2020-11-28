#ifndef __Solver_
#define __Solver_

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<string>

using namespace std;


//base class 
class Solver
{
  protected:                   //private, protected, public
    int    dim;               //dimensionality
    vector<double> yinitial;  //intial condition
    double timestep;          
    double timetotal;
    string filename;
    vector<double> (*f)(vector<double>, double);  //function
  public:
    //Constructor
    Solver(void) { }
    Solver(vector<double> (*fun)(vector<double>, double), vector<double> y0)
    {
      dim = y0.size();
      yinitial.resize(dim);
      f = fun;
      yinitial = y0;
      filename = "RungeKuttaSolution.dat";
    }
    Solver(vector<double> (*fun)(vector<double>, double), vector<double> y0, string name)
    {
      dim = y0.size();
      yinitial.resize(dim);
      f = fun;
      yinitial = y0;
      filename = name;
    }
    void SetDimension(int d)
    {
      dim = d;
      yinitial.resize(dim);
    }
    void SetInitial(vector<double> y0)
    {
      dim = y0.size();
      yinitial.resize(dim);
      yinitial = y0;
    }
    void SetDt(double dt)
    {
      timestep = dt;
    }
    void SetTmax(double tmax)
    {
      timetotal = tmax;
    }   
    virtual void Solve(void) = 0 ; // the =0 makes the method a pure virtual method (it is not defined)
                                   // any class containing one or more pure virtual methods is called abstract
};

class RungeKutta : public Solver
{  
  public:
    //Constructor
    RungeKutta(void) { }
    RungeKutta(vector<double> (*fun)(vector<double>, double), vector<double> y0) : Solver(fun,y0) {}
    RungeKutta(vector<double> (*fun)(vector<double>, double), vector<double> y0, string name) : Solver(fun,y0,name) {}
    void Solve(void);
};



void RungeKutta::Solve(void)
{
  ofstream myfile;
  myfile.open(filename);

  double t = 0, dt;
  vector<double> y(dim);
  vector<double> dy(dim);
  vector<double> k1(dim);
  vector<double> k2(dim);
  vector<double> k3(dim);
  vector<double> k4(dim);
  vector<double> ytemp1(dim);
  vector<double> ytemp2(dim);
  vector<double> ytemp3(dim); 

 
  dt = timestep;

  y = yinitial;
  while(t<=timetotal)
  {
    //print on file
    myfile << t;
    for(int i=0; i<dim; ++i)
    { myfile << setw(20) << y[i]; }
    myfile << endl;

    for(int i=0; i<dim; i++)
    { 
       k1[i] = dt*f(y,t)[i];
       ytemp1[i] = y[i] + 0.5*k1[i];
    }
    for(int i=0; i<dim; i++)
    {
      k2[i] = dt*f(ytemp1,t+dt/2.0)[i];
      ytemp2[i] = y[i] + 0.5*k2[i];
    }
    for(int i=0; i<dim; i++)
    {
      k3[i] = dt*f(ytemp2,t+dt/2.0)[i];
      ytemp3[i] = y[i] + k3[i];
    }
    for(int i=0; i<dim; i++)
    {
      k4[i] = dt*f(ytemp3,t+dt)[i];
    }


    for(int i=0; i<dim; i++)
    { 
      dy[i] = (k1[i]+2.0*k2[i]+2.0*k3[i]+k4[i])/6.0; 
    }

    for(int i=0; i<dim; i++)
    {  
      y[i] += dy[i];  
    }

    t = t + dt;
  }

  myfile.close();
}


#endif
