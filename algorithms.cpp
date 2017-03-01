//
//  main.cpp
//  long numbers
//
//  Created by Maksim Lopatin on 01/03/2017.
//  Copyright © 2017 Maksim Lopatin. All rights reserved.
//

#include "main.hpp"

#include<iostream>
#include <math.h>
using namespace std;
void Vallis();
void Lejbnics();
void Nilakant();
long double arctan(long double x);
void Metchin();
void Bejli();
void Bellar();
void Chudnovsky();
long double factorial(long int a);

const long int e = 10000;



int main()
{
    Vallis();
    Lejbnics();
    Nilakant();
    Metchin();
    Bejli();
    Bellar();
    Chudnovsky();
    return 0;
}


void Chudnovsky()
{
    long double pi = 0.0;
    for (long int i = 0; i<12; i++)
    {
        pi +=(pow(-1, i)*(factorial(6*i))*(13591409+545140134*i))/(factorial(3*i)*pow(factorial(i), 3)*pow(640320,3*i+1.5));
    }
    pi *=12;
    pi = pow(pi, -1);
    cout<<pi<<endl;
}

long double factorial(long int a)
{
    long int x = 1;
    for (long int i = 1; i <= a; i++)
    {
        x*=i;
    }
    return x;
}

void Bellar()
{
    long double pi = 0.0;
    for (long int i = 0; i<e; i++)
    {
        pi += pow(-0.0009765625, i)*(-(32.0/(4.0*i+1.0))-(1.0/(4.0*i+3.0))+(256.0/(10.0*i+1.0))-(64.0/(10.0*i+3.0))-(4.0/(10.0*i+5.0))-(4.0/(10.0*i+7.0))+1.0/(10.0*i+9.0));
    }
    cout<<pi/64.0<<endl;
}



void Bejli()
{
    long double pi = 0.0;
    for (long int i = 0; i<e; i++)
    {
        pi += (pow(0.0625, i))*((4.0/(8.0*i+1.0))-(2.0/(8.0*i+4.0))-(1.0/(8.0*i+5.0))-(1.0/(8.0*i+6.0)));
    }
    cout<<pi<<endl;
}


void Metchin()
{
    long double pi = 4.0*(4.0*arctan(0.20000000) -  arctan(0.00418410041));
    cout<<pi<<endl;
}

long double arctan(long double a)
{
    long double iter = 0.0, x = a;
    for (long int i = 1; i<e; i++)
    {
        
        iter = pow(-1.0, i)*((pow(a, 2.0*i+1.0))/(2.0*i+1.0));
        x += iter;
    }
    return x;
}


void Nilakant()
{
    long double pi = 0.0;
    int n = 2;
    for (long int i = 0; i<e; i++)
    {
        pi += pow(-1.0, i)/((n)*(n+1.0)*(n+2.0));
        n+=2;
    }
    cout << 3+pi*4<<endl;
    
}

void Lejbnics()
{
    long double pi = 1.0, iter = 0;
    for(long int i = 1; i<e; i++)
    {
        iter = (pow(-1.0, i))/(2.0*i+1.0);
        pi += iter;
    }
    cout<<pi*4.0000000000<<endl;
}





void Vallis()
{
    long double pi = 1.0;
    for(long int i = 1; i<e; i++)
    {
        pi *= (i*i*2.0*2.0)/((i*2.0-1.0)*(i*2.0+1.0));
    }
    cout.precision(1000);
    cout<<pi*2.0<<endl;
}
