#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Problem
{
    double epsilon;
    double x0; // initial point
    
    virtual double f(double x)
    {
        return sin(x / 2) + cos(x / 4);
    }

    double df(double x)
    {
        return cos(x / 2) / 2 - sin(x / 4) / 4;
    }

    // solve the subproblme
    // argmin_x\in [xt-epsilon, xt+epsilon] f(x)
    double subproblem(double xt, double epsilon)
    {
        double x = xt - epsilon;
        double fmax = -100;
        double xmax = x;
        while (x <= xt + epsilon)
        {
            if (f(x) > fmax)
            {
                fmax = f(x);
                xmax = x;
            }
            x += epsilon / 100; // you can choose fixed spacing.
        }
        return xmax;
    }

public:
    Problem(double epsilon, double x0)
    {
        this->epsilon = epsilon;
        this->x0 = x0;
    }

    // solve the problem
    void solve()
    {
        double epsilon = .5;
        double x0 = -4; // initial point

        double xt = x0;
        double xt_1 = 100; // xt-1

        while (fabs(xt - xt_1) >= 1e-5)
        { // fabs absolute value function
            xt_1 = xt;
            xt = subproblem(xt, epsilon);
            printf("f(%.4f) = %.4f\n", xt, f(xt));
        }

        printf("Maximum is at %f with value %f\n", xt, f(xt));
    }

    // gradient ascent algorithm
    void GAsolve()
    {

        double xt = x0;
        double xt_1 = 100; // xt-1

        while (fabs(xt - xt_1) >= 1e-5)
        { // fabs absolute value function
            xt_1 = xt;
            xt = xt + epsilon * df(xt);
            printf("f(%.4f) = %.4f\n", xt, f(xt));
        }

        printf("Maximum is at %f with value %f\n", xt, f(xt));
    }
};


class NewProblem: public Problem // this is a new problem 
{
    double f(double x) override // now, we have a new function to be maximized 
    {
        return -x*x;
    }
public: 
    NewProblem(double epsilon, double x0): Problem(epsilon, x0) {}
};


int main()
{
    Problem p(0.5, -4);
    printf("hill climbing... \n");
    p.solve();
    printf("\ngradient ascent... \n");
    p.GAsolve();

    printf("\nsolving a new problem... \n");
    NewProblem p2(.5, -4);
    p2.solve();
}