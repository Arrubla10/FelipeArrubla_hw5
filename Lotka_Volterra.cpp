#include<iostream>
#include <fstream>

using namespace std;

const double h = 0.01;

double dxdt(double x, double y,double a,double b,double t){
    return a*x - b*x*y ;
}

double dydt(double x, double y,double c,double d,double t){
    return -c*y + d*x*y;
}

void runge4_step(double t,double &x,double &y, double a, double b, double c, double d ){
    double k11,k12,k21,k22,k31,k32,k41,k42;
    k11 = h*dxdt(x,y,a,b,t);                    k12 = h*dydt(x,y,c,d,t);
    k21 = h*dxdt(x+k11/2,y+k12/2,a,b,t+h/2);    k22 = h*dydt(x+k11/2,y+k12/2,c,d,t+h/2);
    k31 = h*dxdt(x+k21/2,y+k22/2,a,b,t+h/2);    k32 = h*dydt(x+k21/2,y+k22/2,c,d,t+h/2);
    k41 = h*dxdt(x+k31,y+k32,a,b,t+h);          k42 = h*dydt(x+k31,y+k32,c,d,t+h);
    x += (k11 + 2*(k21 + k31) + k41)/6;     y += (k21 + 2*(k22 + k32) + k42)/6;
}

void integrate_to(double ta){
    double x = 1.0, y=1.0,t;
    double a = 1, b = 0.1, c=1.5, d = 0.75;
    
    while( t <= ta){
        cout << t << "\t" << x << "\t" << y <<endl;
        runge4_step(t,x,y,a,b,c,d);
        t += h;
    }
}

int main(){
    integrate_to( 10);
    return 0;
}
