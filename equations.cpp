#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

///////////////////////////////////////////////////////////////////
// Input definitions

float underlying_price()
{
    float price;
    cin >> price;
    return price;
}

int strike_price()
{
    int strike;
    cin >> strike;
    return strike;
}

int maturity()
{
    int maturity;
    cin >> maturity;
    return maturity;
}

float interest_rate()
{
    float ir;
    cin >> ir;
    return ir;
}

float implied_volatility()
{
    float iv;
    cin >> iv;
    return iv;
}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Black-Scholes Model

// Cumulative Standard Normal Distribution Function
double c_std_normal_dist(double x)
{
    const double pi = M_PI;
    double result;

    // Approximation using the trapezoidal rule

    const int n = 100;
    const int h = x / n;
    for(int i = 0; i <= n; i++)
    {
        double t = -x + i * h;
        double f = exp(-t * t / 2) / sqrt(2 * pi);
        result += (i == 0 || i == n) ? f : 2 * f;
    }
    
    result *= h / 2;

    return result;
}

double black_scholes_model(float asset, int strike, int days, float interest, float volatility, bool call)
{
    float pred;
    double volatility_squared = pow (volatility, 2);
    double d1 = (log(asset / strike) + (interest + (volatility_squared / 2) * days)) / (volatility * sqrt(days));
    double d2 = d1 - (volatility * sqrt(days));

    if(call == true)
    {
        pred = asset * c_std_normal_dist(d1) - (strike * (exp (-interest * days)) * c_std_normal_dist(d2));
    }
    else
    {
        pred = (strike * (exp (-interest * days)) * c_std_normal_dist(-d2)) - (asset * c_std_normal_dist(-d1));
    }

    return pred;
}
///////////////////////////////////////////////////////////////////

int main()
{
    return(0);


}