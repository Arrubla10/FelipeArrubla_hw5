#include<iostream>
#include<math.h>
#include <random>

#define TAB "\t"
#define N 100000

using namespace std;

const int x_obs[6] = {3,4,5,3,4,5};
const int y_obs[6] = {15,15,15,16,16,16};
const double t_obs[6] = {3.12, 2.98,2.84,3.26,3.12,2.98};
const double sigma = 0.10;
const double v = 5.0;

void my_model(double x, double y, double res[6]){
    for(int i = 0; i < 6; i++)
        res[i] = 1/v*sqrt( pow(x-x_obs[i],2) + pow(y-y_obs[i],2) );
}

double likelihood( double t_model[6] ){
    double tmp = 0.0;
    for(int i=0; i < 6; i++)
        tmp += pow(t_model[i] - t_obs[i],2 );
    return tmp;
}

int main(){
    double t_i[6];
    default_random_engine generator;

    double x_walk = ((double) rand() / (RAND_MAX));
    double y_walk = ((double) rand() / (RAND_MAX));

    double x_prime = 0.0, y_prime = 0.0;
    double error=0.0, alpha = 0.0, beta = 0.0;

    for( int i = 0; i < N; i++){
        normal_distribution<double> distribution_x( x_walk, 0.5 );
        normal_distribution<double> distribution_y( y_walk, 0.5 );

        x_prime = distribution_x(generator);
        y_prime = distribution_y(generator);

        my_model( x_prime, y_prime, t_i );
        error = likelihood( t_i );
        alpha = exp(-error/(2*sigma));

        if(alpha >= 1){
            x_walk = x_prime;
            y_walk = y_prime;
            cout << x_walk << TAB << y_walk << endl;
        } else {
            beta = ((double) rand() / (RAND_MAX));

            if(beta <= alpha){
                x_walk = x_prime;
                y_walk = y_prime;
                cout << x_walk << TAB << y_walk << endl;
            } else{
                cout << x_walk << TAB << y_walk << endl;
            }
        }
    }

    return 0;
}
