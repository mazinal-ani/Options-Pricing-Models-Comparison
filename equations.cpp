#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

///////////////////////////////////////////////////////////////////
// Input definitions

float underlying_price()
{
    float price;
    cout << "Please enter the price of the underlying asset: ";
    cin >> price;
    return price;
}

float strike_price()
{
    float strike;
    cout << "Please enter the strike price of the option: ";
    cin >> strike;
    return strike;
}

float maturity()
{
    float maturity;
    cout << "Please enter the number of years until maturity for the contract: ";
    cin >> maturity;
    return maturity;
}

float div_yield()
{
    float div;
    cout << "What is the dividend yield? "
    cin >> div;
    return div;
}

float interest_rate()
{
    float ir;
    cout << "What is the nominal risk-free interest rate? ";
    cin >> ir;
    return ir;
}

float implied_volatility()
{
    float iv;
    cout << "What is the volatility of the underlying asset? ";
    cin >> iv;
    return iv;
}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Black-Scholes Model

// Cumulative Standard Normal Distribution Function
double c_std_normal_dist(double x)
{   
    double result = 0.5 * (1 + erf(x / sqrt(2)));

    return result;
}

double black_scholes_model(float asset, float strike, float days, float div_yield, float interest, float volatility, bool call)
{
    float pred;
    double volatility_squared = pow (volatility, 2);
    double d1 = (log(asset / strike) + (interest - div_yield + (volatility_squared / 2)) * days) / (volatility * sqrt(days));
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

///////////////////////////////////////////////////////////////////
// Monte Carlo Simulation



int main()
{
    float asset = underlying_price();
    float strike = strike_price();
    float days = maturity();
    float div = div_yield();
    float interest = interest_rate();
    float volatility = implied_volatility();
    bool call = true;

    cout << black_scholes_model(asset, strike, days, div, interest, volatility, call);

    return 0;
}