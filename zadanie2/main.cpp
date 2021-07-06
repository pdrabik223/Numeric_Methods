//
// Created by studio25 on 22.06.2021.
//
#include <array>
#include <iostream>
#include <vector>

#define H 0.5
double Function(double x, double y) { return (1 - (2 * y)) * y * y; }

double Rk4(double xn, double yn);
int main() {

  const double kH = 0.5; // step
  const double kA = 0;   // t ∈ 〈0,5〉  so a is the leftmost value
  const double kB = 10;   // b is end of a range

  const int kN = (kB - kA) / kH; // the number of slices

  double x[kN + 1];
  double y[kN + 1];

  x[0] = kA;
  for (int i = 1; i < kN; i++)
    x[i] = kA + i * kH;

  x[kN] = kB;

  y[0] = 1;
  for (int i = 0; i < kN; i++)
    y[i + 1] = y[i] + Rk4(x[i], y[i]);

  for (int i = 0; i <= kN; i++)
    std::cout << x[i] << "\t" << y[i] << "\n";

  return 0;
}

double Rk4(double xn, double yn) {

  double k_1 = Function(xn, yn);
  double k_2 = Function(xn + (H / 2.0), yn + (k_1 / 2.0) * H);
  double k_3 = Function(xn + (H / 2.0), yn + (k_2 / 2.0) * H);
  double k_4 = Function(xn + H, yn + k_3 * H);

  return H * (k_1 + (2.0 * k_2) + (2.0 * k_3) + k_4) / 6.0;
}