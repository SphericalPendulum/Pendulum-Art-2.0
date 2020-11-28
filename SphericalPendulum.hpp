#ifndef __Sp_
#define __Sp_

#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<fstream>
#include<vector>       //vector is a container defined in the standard library

using namespace std;

class SphericalPendulum
{
  public:
    static double m;      // mass of pendulum (not used)
    static double l;      // length of pendulum
    static double g;      // gravitiational constant (9.81 m/s^2)
    static double height; // height of attachement point above the ground
    static double delta1; // friction coefficient for theta
    static double delta2; // friction coefficient for phi
    
    // static method describing motion of pendulum without friction
    static vector<double> diff_eqn(vector<double> y, double t)
    {
      // y[0] = Theta
      // y[1] = dTheta/dt
      // y[2] = Phi
      // y[3] = dPhi/dt

      vector<double> dydt(4);
      dydt[0] = y[1];
      dydt[1] = sin(y[0])*cos(y[0])*pow(y[3],2) - (g/l)*sin(y[0]);
      dydt[2] = y[3];
      dydt[3] = -(2*cos(y[0])*y[1]*y[3])/ sin(y[0]);
      return dydt;
    }

    // static method describing motion of pendulum with friction
    static vector<double> diff_eqn_friction(vector<double> y, double t)
    {
      // y[0] = Theta
      // y[1] = dTheta/dt
      // y[2] = Phi
      // y[3] = dPhi/dt

      vector<double> dydt(4);
      dydt[0] = y[1];
      dydt[1] = sin(y[0])*cos(y[0])*pow(y[3],2) - (g/l)*sin(y[0]) - delta1*y[1];
      dydt[2] = y[3];
      dydt[3] = -(2*cos(y[0])*y[1]*y[3])/ sin(y[0]) - delta2*y[3];
      return dydt;
    }

    // method to find (x, y, z) position and (vx, vy, vz) velocities from theta, theta', phi, phi'
    static void translate_coordinates(string initial_file, string final_file, double tmax, double dt)
    {
      ifstream old_file;
      ofstream new_file;
      old_file.open(initial_file);
      new_file.open(final_file);

      double theta, theta_prime, phi, phi_prime;
      double x, y, z, vx, vy, vz;
      double t;

      old_file >> t;
      for (int i =0; i< (int) (tmax/dt); ++i)
      {
        new_file << t << "  ";
        old_file >> theta >> theta_prime >> phi >> phi_prime;
        x = l*sin(theta)*cos(phi);
        y = l*sin(theta)*sin(phi);
        z = l*(1-cos(theta)) + height - l;  // consider pendulum height above the ground
        vx = l*cos(theta)*cos(phi)*theta_prime - l*sin(theta)*sin(phi)*phi_prime;
        vy = l*cos(theta)*sin(phi)*theta_prime + l*sin(theta)*cos(phi)*phi_prime;
        vz = l*sin(theta)*theta_prime;
        new_file << x << "  " << y << "  " << z << "  " << vx << " " << vy << "  " << vz << endl;
        old_file >> t;
      }

      old_file.close();
      new_file.close();
    }   
};

// define default values for pendulum geometry and friction
double SphericalPendulum::m = 1;
double SphericalPendulum::l = 1;
double SphericalPendulum::g = 9.81;
double SphericalPendulum::height = 1.5;
double SphericalPendulum::delta1 = 0.03;
double SphericalPendulum::delta2 = 0.04;

#endif


