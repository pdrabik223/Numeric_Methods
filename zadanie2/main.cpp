//
// Created by studio25 on 22.06.2021.
//
#include <array>
#include <iostream>
#include <vector>

#define H 0.5
#define PI 3.141592653589793238463
double Function(double x, double y) { return (1 - (2 * y)) * y * y; }
double Rk4(double xn, double yn);
int main() {


   // y(0) = 1

   double y0 = 1;


  std::cout<<0<<"\t"<<y0<<"\n";
  for (double i = H; i < 5; i += H) {
    y0 += Rk4(0,i);
    std::cout<<i<<"\t"<<y0<<"\n";
  }

  return 0;
}

double Rk4(double xn, double yn) {

  double k_1 = H * Function(xn, yn);
  double k_2 = H * Function(xn + H / 2, yn + k_1 / 2);
  double k_3 = H * Function(xn + H / 2, yn + k_2 / 2);
  double k_4 = H * Function(xn + H, yn + k_3);

  return (k_1 + 2 * k_2 + 2 * k_3 + k_4) / 6;
}