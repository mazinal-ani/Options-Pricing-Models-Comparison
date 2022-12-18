#include <iostream>
#include <cmath>
using namespace std;

///////////////////////////////////////////////////////////////////
// Input definitions

int underlying_price()
{
    int price;
    cin >> price;
    return(price);
}

int strike_price()
{
    int strike;
    cin >> strike;
    return(strike);
}

int maturity()
{
    int maturity;
    cin >> maturity;
    return(maturity);
}

int interest_rate()
{
    int ir;
    cin >> ir;
    return ir;
}

int implied_volatility()
{
    int iv;
    cin >> iv;
    return(iv);
}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Black-Scholes Model

double black_scholes_model(asset, strike, days, interest, volatility)
{
    double volatility_squared = pow (volatility, 2)
    double d1 = (log(asset / strike) + (interest + (volatility_squared / 2) * days)) / (volatility * sqrt(days))
    double d2 = d1 - (volatility * sqrt(days))
}
///////////////////////////////////////////////////////////////////

int main()
{
    return(0);


}