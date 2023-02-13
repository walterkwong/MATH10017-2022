#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x){
    return sin(x/2) + cos(x/4);
}

// solve the subproblme
// argmin_x\in [xt-epsilon, xt+epsilon] f(x)
double subproblem(double xt, double epsilon){
    double x = xt - epsilon;
    double fmax = -100;
    double xmax = x;
    while(x <= xt + epsilon){
        if(f(x) > fmax){
            fmax = f(x);
            xmax = x;
        }
        x += epsilon/100; //you can choose fixed spacing.
    }
    return xmax;
}

int main(){
    double epsilon = .5;
    double x0 = -4; //initial point
    
    double xt = x0; 
    double xt_1 = 100; // xt-1
    
    while( fabs(xt - xt_1) >= 1e-5){ // fabs absolute value function
        xt_1 = xt; 
        xt = subproblem(xt, epsilon);
        printf("f(%.4f) = %.4f\n", xt, f(xt));
    }

    printf("Maximum is at %f with value %f\n", xt, f(xt));

}