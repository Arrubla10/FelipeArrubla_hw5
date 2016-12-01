#include<iostream>
#include<math.h>
#include <random>

#define TAB "\t"
#define N 100000

using namespace std;

const double x[8] = {0.324190175, -0.701534590, -0.982564148, 1.104185888, 3.266443877, -9.218802228, 19.930781147, 24.323085642 };
const double y[8] = {0.090955208, -0.168809218, -0.191145980, -0.826097003, -3.888055863, 1.788299816, -2.555241579, -17.606227355};
const double z[8] = {-0.022920510, 0.037947785, -0.000014724, -0.044595990,-0.057015321, 0.335737817, -0.267710968, -0.197974999};
const double vx[8] = {-4.6277851589, 1.725066954, 1.126784520, 3.260215854, 2.076140727, -0.496457364, 0.172224285, 0.664855006};
const double vy[8] = {10.390063716, -7.205747212, -6.187988860, 4.524583075, 1.904040630, -2.005021061, 1.357933443, 0.935497207};
const double vz[8] = {1.273504997, -0.198268558, 0.000330572, 0.014760239, -0.054374153, 0.054667082, 0.002836325, -0.034716967 };
const double sigma = 0.10;
const double v = 5.0;

void my_model(double m, double b, double res[8]){
    double ri = 0.0;
    for(int i = 0; i < 6; i++){
        ri = sqrt( x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
        res[i] = m*log(ri) + b;
    }
}

double likelihood( double y_model[8] ){
    double tmp = 0.0;
    double vi = 0.0;
    for(int i=0; i < 8; i++){
        vi = sqrt( vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);
        tmp += pow( log(vi) - y_model[i] , 2 );
    }
    return tmp;
}

int main(){
    double y_init[8], y_prime[8];
    default_random_engine generator;
    
    double m_walk = ((double) rand() / (RAND_MAX));
    double b_walk = ((double) rand() / (RAND_MAX));
    
    my_model(m_walk, b_walk, y_init);
    double l_walk = likelihood( y_init );

    double m_prime = 0.0, b_prime = 0.0, l_prime = 0.0, l_init;
    double alpha = 0.0, beta = 0.0;

    for( int i = 0; i < N; i++){
        normal_distribution<double> distribution_m( m_walk, 0.1 );
        normal_distribution<double> distribution_b( b_walk, 0.1 );

        m_prime = distribution_m(generator);
        b_prime = distribution_b(generator);

        my_model( m_walk, b_walk, y_init );
        my_model( m_prime, b_prime, y_prime );
        
        l_init = likelihood( y_init );
        l_prime = likelihood( y_prime );
        
        alpha = exp(-(l_prime - l_init));
        
        if(alpha >= 1){
            m_walk = m_prime;
            b_walk = b_prime;
            l_walk = l_prime;
            cout << m_walk << TAB << b_walk << TAB << l_walk << endl;
        } else {
            beta = ((double) rand() / (RAND_MAX));

            if(beta <= alpha){
                m_walk = m_prime;
                b_walk = b_prime;
                l_walk = l_prime;
                cout << m_walk << TAB << b_walk << TAB << l_walk << endl;
            } else{
                l_walk = l_init;
                cout << m_walk << TAB << b_walk << TAB << l_walk << endl;
            }
        }
    }
    return 0;
}
