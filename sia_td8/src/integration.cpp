#include "integration.h"
#include <iostream>
using namespace std;

void explicitEulerStep (ODESystem *system, double dt) {
    // TODO: implement this
    VectorXd state(system->getDimensions());
    VectorXd deriv(system->getDimensions());

    system->getState(state);
    system->getDerivative(deriv);

    VectorXd newState(system->getDimensions());
    newState = state + dt * deriv;

    system->setState(newState);
}

void midPointStep (ODESystem *system, double dt) {
    // TODO: implement this
    VectorXd deriv(system->getDimensions());
    system->getDerivative(deriv);

    VectorXd dx(system->getDimensions());
    dx = dt * deriv;

    VectorXd state(system->getDimensions());
    system->getState(state);

    VectorXd fmid(system->getDimensions());
    fmid = (state + dx) / 2;
    system->setState(fmid);

    VectorXd newState(system->getDimensions());
    newState = state + dt * deriv;
    system->setState(newState);
}
