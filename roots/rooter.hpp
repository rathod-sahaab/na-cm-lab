#pragma once

#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>

using Limit = std::pair<double, double>;
using OneVarRealFunction = std::function<double(double)>;
using TwoVarRealFunction = std::function<double(double, double)>;
using OneVarDifferentiableFunction = std::function<double(double, bool)>;

double base_rooter(TwoVarRealFunction intermidiate_calculation_function,
                   OneVarRealFunction func, Limit limit,
                   int n_digit_precision = 6);

double newton_raphson(OneVarDifferentiableFunction func, double initial_guess,
                      int n_digit_precision = 6) {
  const double precision = pow(10, -1 * n_digit_precision);

  auto x = initial_guess;
  auto fx = func(x, false);

  while (fabs(fx) > precision) {
    x = (x - (fx / func(x, true)));
    fx = func(x, false);
  }
  return x;
}

double bisection(OneVarRealFunction func, Limit limit,
                 int n_digit_precision = 6) {
  auto bisection_intermidiate = [](double x1, double x2) {
    return (x1 + x2) / 2;
  };
  return base_rooter(bisection_intermidiate, func, limit, n_digit_precision);
}

double regular_falsi(OneVarRealFunction func, Limit limit,
                     int n_digit_precision = 6) {
  auto regular_falsi_intermidiate = [&func](double x1, double x2) {
    return x2 - (func(x2) * (x2 - x1)) / (func(x2) - func(x1));
  };

  return base_rooter(regular_falsi_intermidiate, func, limit);
}

double base_rooter(TwoVarRealFunction intermidiate_calculation_function,
                   OneVarRealFunction func, Limit limit,
                   int n_digit_precision) {

  const double precision = pow(10, -1 * n_digit_precision);
  auto x1 = limit.first, x2 = limit.second;
  std::cout << x1 << ' ' << x2 << "\n";

  if (not(func(x1) < 0 xor func(x2) < 0)) {
    // same as func(x1)*func(x2) < 0, but, fucking faster
    std::cerr << "No roots in the interval (" << limit.first << ", "
              << limit.second << ")\n";
    throw std::invalid_argument("No roots in given limit");
  }
  auto fx1 = func(x1);
  while (true) {
    const auto x = intermidiate_calculation_function(x1, x2);
    const auto fx = func(x);

    if (std::fabs(fx) < precision) {
      return x;
    }
    if (fx < 0 xor fx1 < 0) {
      x2 = x;
    } else {
      x1 = x;
      fx1 = fx;
    }
  }
}
