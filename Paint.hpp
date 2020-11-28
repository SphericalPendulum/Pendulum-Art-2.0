#ifndef __Paint_
#define __Paint_

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

class Paint
{
    private:
        const double g = 9.81;
        vector<double> x, y, z, vx, vy, vz;  // location and velocity of each drop
        vector<double> time;
        int num;  // number of paint drops
        double tmax, dt;
        
    public:
        Paint();
        Paint(string filename, double time, double timeStep);
        void DropParticles(void);
        void WriteToFile(string filename);

};

// empty constructor
Paint::Paint()
{
  time.resize(0);
  x.resize(0);
  y.resize(0);
  z.resize(0);
  vx.resize(0);
  vy.resize(0);
  vz.resize(0);
}

// construct Paint object from file of data
Paint::Paint(string filename, double totalTime, double timeStep)
{
  num = (int) (totalTime/timeStep);
  tmax = totalTime;
  dt = timeStep;

  ifstream pendulum;
  pendulum.open(filename);
  double temptime, tempx, tempy, tempz, tempvx, tempvy, tempvz;

  for(int i = 0; i < num; ++i)
  {
    pendulum >> temptime >> tempx >> tempy >> tempz >> tempvx >> tempvy >> tempvz ;

    time.push_back(temptime);
    x.push_back(tempx);
    y.push_back(tempy);
    z.push_back(tempz);
    vx.push_back(tempvx);
    vy.push_back(tempvy);
    vz.push_back(tempvz); 

  }

  pendulum.close();
}

// calculate final positions of paint drops
void Paint::DropParticles(void)
{
  double newtime;
  for(int i = 0; i < num; ++i)
  {
    newtime = ( vz[i] + sqrt( pow(vz[i],2) + 2*g*z[i]) ) / g;
    time[i] = newtime + time[i];

    x[i] = newtime*vx[i] + x[i];
    y[i] = newtime*vy[i] + y[i];
    
    z[i] = 0;
  }
}

// write final positions to a file
void Paint::WriteToFile(string filename)
{
  ofstream output;
  output.open(filename);
  
  for(int i = 0; i < num ; ++i)
  {
    output << time[i] << setw(20) << x[i] << setw(20) << y[i] << endl;
  }

  output.close();
}


#endif
