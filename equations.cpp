#include <iostream>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <random>
#include <iomanip>
#include <chrono>
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
    cout << "What is the dividend yield? ";
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

double black_scholes_model(float asset, float strike, float years, float div_yield, float interest, float volatility, bool call)
{
    float pred;
    double volatility_squared = pow (volatility, 2);
    double d1 = (log(asset / strike) + (interest - div_yield + (volatility_squared / 2)) * years) / (volatility * sqrt(years));
    double d2 = d1 - (volatility * sqrt(years));

    if(call == true)
    {
        pred = asset * c_std_normal_dist(d1) - (strike * (exp (-interest * years)) * c_std_normal_dist(d2));
    }
    else
    {
        pred = (strike * (exp (-interest * years)) * c_std_normal_dist(-d2)) - (asset * c_std_normal_dist(-d1));
    }

    return pred;
}
///////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////
// Monte Carlo Simulation

double randn(float volatility)
{

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0.0,volatility);
    return distribution(generator);
    
}

double monte_carlo(float asset, float strike, float years, float interest, float volatility)
{
    const double time_steps = years / 252;
    int total_payout = 0;
    for (int i = 0; i < 10000; i ++)
    {
        float s_0 = asset;
        for (int j = 0; j < 252; j++)
        {
          double random_variable = randn(volatility);
          s_0 *= exp((interest - 0.5 * volatility * volatility) * time_steps + volatility * (sqrt(time_steps)) * random_variable);
        }
        float payout = s_0 - strike;
        total_payout += max(float(1-1), payout);
    }
   total_payout /= 10000;
   return (total_payout * exp(-interest * years));
}
///////////////////////////////////////////////////////////////////



int main()
{
    float asset = underlying_price();
    float strike = strike_price();
    float years = maturity();
    float div = div_yield();
    float interest = interest_rate();
    float volatility = implied_volatility();
    bool call = true;

    float black_scholes_prediction = black_scholes_model(asset, strike, years, div, interest, volatility, call);
    float monte_carlo_prediction = monte_carlo(asset, strike, years, interest, volatility);

    cout << setprecision (2) << fixed << "Black-Scholes Formula Prediction: " << black_scholes_prediction << "\n";
    cout << setprecision (2) << fixed << "Monte Carlo Simulation Prediction: " << monte_carlo_prediction << "\n";
    cout << setprecision (2) << fixed << "Difference: " << abs(black_scholes_prediction - monte_carlo_prediction);

    return 0;
}