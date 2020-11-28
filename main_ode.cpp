#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<fstream>
#include<vector>       //vector is a container defined in the standard library
#include"Solver.hpp"
#include"Paint.hpp"
#include"SphericalPendulum.hpp"

using namespace std;

int main()
{
  // ask for pendulum initial conditions
  vector<double> y0(4);
  double dt, tmax;
  cout << "Please enter the initial Theta, initial ThetaPrime, initial Phi, and initial PhiPrime:  " << endl;
  cin >> y0[0] >> y0[1] >> y0[2] >> y0[3];

  for(int i=0; i<4; ++i)
  {
    y0[i] = (3.1415926535)*y0[i]/180.0;
  }

  // ask for time step and total simulation time
  cout << "Please enter the time step: " << endl;
  cin >> dt;   
  cout << "Please enter the maximum time: " << endl;
  cin >> tmax;
  
  // ask for geometry of the pendulum setup
  double response;
  cout << "Use default geometry of length = 1, height = 1.5? (1 = yes, 0 = no) " << endl;
  cin >> response;
  if (response == 0)
  {
    cout << "Please enter the length and height of the pendulum: " << endl;
    cin >> SphericalPendulum::l >> SphericalPendulum::height;
    cout << "Please enter mass of pendulum: " << endl;
    cin >> SphericalPendulum::m;
  }

  // ask for friction coefficients
  cout << "Use default friction coefficients of delta1 = 0.03 and delta2 = 0.04? (1 = yes, 0 = no) " << endl;
  cin >> response;
  if (response == 0)
  {
    cout << "Please enter delta1 and delta2: " << endl;
    cin >> SphericalPendulum::delta1 >> SphericalPendulum::delta2;
  }
 
  // initialize RungeKutta solver to find pendulum trajectory
  RungeKutta Pendulum(&SphericalPendulum::diff_eqn,y0,"RungeKuttaSolution.dat");
  Pendulum.SetDt(dt);
  Pendulum.SetTmax(tmax);
  Pendulum.Solve();

  RungeKutta PendulumFriction(&SphericalPendulum::diff_eqn_friction,y0,"RungeKuttaSolutionFR.dat");
  PendulumFriction.SetDt(dt);
  PendulumFriction.SetTmax(tmax);
  PendulumFriction.Solve();

  // rewrite pendulum position in x, y, z coordinates
  SphericalPendulum::translate_coordinates("RungeKuttaSolution.dat", "xyz.dat", tmax, dt);
  SphericalPendulum::translate_coordinates("RungeKuttaSolutionFR.dat", "xyzFR.dat", tmax, dt);

  // find the final location of the piant drops
  Paint drops("xyz.dat", tmax, dt);
  drops.DropParticles();
  drops.WriteToFile("drops.dat"); 

  Paint drops_fr("xyzFR.dat", tmax, dt);
  drops_fr.DropParticles();
  drops_fr.WriteToFile("dropsFR.dat");

  return 0;
}
