#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "gnuplot_i.hpp"

using namespace std;

double int_mc(double(*)(double), double&, double, double, int);
double varf(double(*)(double), double, double, int);
double f(double);
double f2(double);
void wait_for_key ();

int main()
{
    Gnuplot g("lines");

    double a = 0.0;              // left endpoint
    double b = 1.0;               // right endpoint
    int N = 500;
    srand(time(NULL));

    double varest, mc, variance;
    std::vector<double> x, err, var_e, var_t;

    for (int n=5; n <= N; n++)
    {
        mc = int_mc(f, varest, a, b, n);

        variance = varf(f, a, b, n);

        x.push_back(n);
        err.push_back(fabs(mc-1.0));
        var_t.push_back(fabs(variance-1.0));
        var_e.push_back(fabs(varest));
    }

    g.reset_plot();
    g.set_grid();
    g.set_style("lines").plot_xy(x,err,"erreur d'estimation");
    g.set_style("lines").plot_xy(x,var_t,"variance numerique");
    g.set_style("lines").plot_xy(x,var_e,"variance analytique");

    wait_for_key();

    return 0;
}

/*
    Fonction à intégrer
*/
double f(double x)
{
    double y;
    y = 5 * pow(x, 4);
    return y;
}

double f2(double x)
{
    double y;
    y = 25/9*pow(x, 9) - 10/5*pow(x, 5) + x;
    return y;
}

double varf(double(*f)(double), double a, double b, int n)
{
    double sum(0.0);

    for (int i(1); i < n; i++)
    {
        double xi = a + (b - a);
        sum += f2(xi);
    }

    return sum / n;
}

/*
    Integration de Monte-Carlo
*/
double int_mc(double(*f)(double), double& varest, double a, double b, int n)
{
    double sum(0.0);
    double sum2(0.0);
    double u;

    for (double i(1.0); i < n; i++)
    {
        u = 1.0 * rand() / (RAND_MAX + 1);
        double xi = a + u * (b - a);
        sum += f(xi);
        sum2 += (f(xi) * f(xi));
    }

    varest = sum/n - sum2/n;
    varest /= (n-1);

    return sum / n;
}

void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}
