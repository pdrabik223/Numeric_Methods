#include <iostream>
double f(double x, double y) { return 1.0 + y / x; }

int main() {
  const int n = 100;
  // PRZEDZIAL

  double a = 1;
  double b = 5;

  double h = (b - a) / n;

  double x[n + 1];
  double y[n + 1];
  double k[4];
  x[0] = a;
  x[n] = b;
  // x[n-1] = b;
  y[0] = 1;
  for (int i = 0; i < n - 1; i++) {
    x[i + 1] = a + (i + 1) * h;
  }
  std::cout << "Pierwsza metoda:" << std::endl;
  std::cout << "h: " << h << std::endl;
  for (int i = 0; i < n; i++) {
    k[0] = f(x[i], y[i]);
    k[1] = f(x[i] + h / 2, y[i] + k[0] / 2 * h);
    k[2] = f(x[i] + h / 2, y[i] + k[1] / 2 * h);
    k[3] = f(x[i] + h, y[i] + k[2] * h);
    //  std::cout<<"k[0] "<<k[0]<<" k[1]: "<<k[1]<<" k[2]: "<<k[2]<<" k[3]:
    //  "<<k[3]<<std::endl;
    std::cout << "x: " << x[i] << " y: " << y[i] << std::endl;
    y[i + 1] = 1.0 * y[i] + (h * (k[0] + 2.0 * k[1] + 2.0 * k[2] + k[3]) / 6);
  }
  std::cout << "x: " << x[n] << " y: " << y[n] << std::endl;
  std::cout << "---------------------------------------------------------------"
               "----------------------"
            << std::endl;
  std::cout << "Druga metoda rzedu piatego:" << std::endl;
  double y2[n + 1];
  y2[0] = y[0];
  y2[n] = y[n];
  double j[5];
  for (int i = 0; i < n; i++) {
    j[0] = f(x[i], y2[i]);
    j[1] = f(x[i] + h / 4.0, y2[i] + j[0] / 4.0 * h);
    j[2] = f(x[i] + 3.0 * h / 8.0, y2[i] + 3.0 * j[1] / 8.0 * h);
    j[3] = f(x[i] + 12.0 * h / 13.0, y2[i] + 12.0 * j[2] / 13.0 * h);
    j[4] = f(x[i] + 1.0 * h, y2[i] + 1.0 * j[3] * h);

    //  std::cout<<"k[0] "<<k[0]<<" k[1]: "<<k[1]<<" k[2]: "<<k[2]<<" k[3]:
    //  "<<k[3]<<std::endl;
    std::cout << "x: " << x[i] << " y: " << y2[i] << std::endl;
    y2[i + 1] = 1.0 * y2[i] + ((25 * j[0] / 216 + 1408 * j[2] / 2565 +
                                2197 * j[3] / 4104 - j[4] / 5) *
                               h);
  }
  std::cout << "x: " << x[n] << " y: " << y2[n] << std::endl;
  std::cout << "---------------------------------------------------------------"
               "----------------------"
            << std::endl;
  std::cout << "Druga metoda rzedu szóstego:" << std::endl;
  y2[0] = 1;
  double l[6];
  for (int i = 0; i < n; i++) {
    l[0] = f(x[i], y2[i]);
    l[1] = f(x[i] + h / 4.0, y2[i] + j[0] / 4.0 * h);
    l[2] = f(x[i] + 3.0 * h / 8.0, y2[i] + 3 * j[1] / 8.0 * h);
    l[3] = f(x[i] + 12.0 * h / 13.0, y2[i] + 12.0 * j[2] / 13.0 * h);
    l[4] = f(x[i] + 1.0 * h, y2[i] + 1.0 * j[3] * h);
    l[5] = f(x[i] + h / 2.0, y2[i] + j[4] * h / 2.0);
    std::cout << "x: " << x[i] << " y: " << y[i] << std::endl;
    y2[i + 1] =
        1.0 * y2[i] + ((16.0 * l[0] / 135.0) + (6656.0 * l[2] / 12825.0) +
                       (28561.0 * l[3] / 56430.0) - (9.0 * l[4] / 5.0) +
                       (2.0 * l[5] / 55.0)) *
                          h;
  }
  std::cout << "x: " << x[n] << " y: " << y[n] << std::endl;
  return 0;
}
