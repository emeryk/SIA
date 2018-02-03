#include "particles.h"
#include <cmath>
#include <iostream>

using namespace std;
using namespace Eigen;

void makeGrid(ParticleSystem *psys);

void ParticleSystem::init() {
    makeGrid(this); // also creates spring forces
    forces.push_back(new DragForce(this, 0.01));
    forces.push_back(new GravityForce(this, Vector3d(0,-9.807,0)));

    // OpenGL allocation
    glGenVertexArrays(2,_vao);
    glGenBuffers(2,_vbo);

    updateGL(true);
}

void ParticleSystem::updateGL(bool first)
{
    // Particles
    vector<Vector3f> positions;
    positions.resize(particles.size());
    for(int i=0; i<particles.size(); i++){
        positions[i] = particles[i]->x.cast<float>();
        _bbox.extend(positions[i]);
    }
    glBindVertexArray(_vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    if(first)
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*particles.size(), positions.data(), GL_DYNAMIC_DRAW);
    else
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vector3f)*particles.size(), positions.data());
    glBindVertexArray(0);

    // Spring forces
    positions.resize(0);
    positions.reserve(forces.size()*2);
    for(int i=0; i<forces.size(); i++){
        SpringForce* s = dynamic_cast<SpringForce*>(forces[i]);
        if(s) {
            positions.push_back(s->p0->x.cast<float>());
            positions.push_back(s->p1->x.cast<float>());
        }
        AnchorForce* a = dynamic_cast<AnchorForce*>(forces[i]);
        if(a && a->p != nullptr) {
            positions.push_back(a->p->x.cast<float>());
            positions.push_back(a->x.cast<float>());
        }
    }

    glBindVertexArray(_vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    if(first || nbSpringForces != positions.size()){
        nbSpringForces = positions.size();
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*nbSpringForces, positions.data(), GL_DYNAMIC_DRAW);
    }else
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vector3f)*nbSpringForces, positions.data());
    glBindVertexArray(0);
    _ready = true;
}

ParticleSystem::~ParticleSystem() {
    glDeleteBuffers(2, _vbo);
    glDeleteVertexArrays(2, _vao);
}

void ParticleSystem::display(Shader *shader) {
    if(!_ready)
        init();

    // Draw particles
    glBindVertexArray(_vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);

    GLuint vertex_loc = shader->getAttribLocation("vtx_position");
    glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(vertex_loc);

    glPointSize(5.f);
    glDrawArrays(GL_POINTS, 0, particles.size());

    glDisableVertexAttribArray(vertex_loc);
    glBindVertexArray(0);

    // Draw spring forces
    glBindVertexArray(_vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);

    vertex_loc = shader->getAttribLocation("vtx_position");
    glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(vertex_loc);

    glLineWidth(2.f);
    glDrawArrays(GL_LINES, 0, nbSpringForces*2);

    glDisableVertexAttribArray(vertex_loc);
    glBindVertexArray(0);
}

void ParticleSystem::step(double dt) {
    // TODO: implement this
    //explicitEulerStep(this, dt);
    midPointStep(this, dt);
    updateGL(false);
}

int ParticleSystem::getDimensions() {
     // TODO: implement this
     return 6 * this->particles.size();
}

void ParticleSystem::getState (VectorXd &state) {
    // TODO: implement this
    int offset(0);
    for (Particle* p : this->particles)
    {
      state.segment(offset, 3) = p->x;
      state.segment(offset+3, 3) = p->v;
      offset += 6;
    }
}

void ParticleSystem::setState (const VectorXd &state) {
    // TODO: implement this
    int offset(0);
    for (Particle* p : this->particles)
    {
      p->x = state.segment(offset, 3);
      p->v = state.segment(offset+3, 3);
      offset += 6;
    }
}

void ParticleSystem::getDerivative (VectorXd &deriv) {
    // TODO: implement this
    for (Particle* p : this->particles)
      p->f = Vector3d(0, 0, 0);

    for (Force* f : this->forces)
      f->addForces();

    int offset(0);
    for (Particle* p : this->particles)
    {
      deriv.segment(offset, 3) = p->v;
      deriv.segment(offset+3, 3) = p->f / p->m;
      offset += 6;
    }
}

void GravityForce::addForces() {
    // TODO: implement this
    for (Particle* p : this->ps->particles)
      p->f += p->m * this->g;
}

void DragForce::addForces() {
    // TODO: implement this
    for (Particle* p : this->ps->particles)
      p->f += - this->kd * p->v;
}

void SpringForce::addForces() {
    // TODO: implement this
    Vector3d l = p0->x - p1->x;
    Vector3d f_mass_spring = - ks * (l.norm() - l0) * (l / l.norm());
    Vector3d f_mass_damper = - kd * (p0->v - p1->v).dot(l) / l.norm() * (l / l.norm());

    Vector3d f = f_mass_spring + f_mass_damper;
    p0->f += f;
    p1->f += - f;
}

void AnchorForce::addForces() {
    if (p == NULL)
        return;
    Vector3d dx = p->x - x;
    p->f += -ks*dx - kd*p->v;
}

void makeGrid(ParticleSystem *psys) {
    const int m = 10, n = 10;                      // resolution of system
    double mass = 1;                               // total mass
    double pmass = mass/((m + 1)*(n + 1));         // mass per particle
    double x0 = 0.3, x1 = 0.7, y0 = 0.3, y1 = 0.7; // extent of rectangle
    double dx = (x1 - x0)/m, dy = (y1 - y0)/n;     // lengths of springs
    double k = 200, d = 0.1;                       // spring constant, damping
    double kdia = k / 4;
    double ddia = sqrt(dx * dx + dy * dy);
    // create particles
    Particle *particles[m+1][n+1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            Vector3d x(x0+dx*i, y0+dy*j, 0);
            Vector3d v(0, 0, 0);
            particles[i][j] = new Particle(pmass, x, v);
            psys->particles.push_back(particles[i][j]);
        }
    }

    // create anchor points
    psys->forces.push_back(new AnchorForce(particles[0][n], particles[0][n]->x, 1000, 0.1));
    psys->forces.push_back(new AnchorForce(particles[m][n], particles[m][n]->x, 1000, 0.1));

    // create springs
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            Particle *p0 = particles[i][j];
            if (i < m) {
                Particle *p1 = particles[i+1][j];
                psys->forces.push_back(new SpringForce(p0, p1, k, d, dx));
            }
            if (j < n) {
                Particle *p1 = particles[i][j+1];
                psys->forces.push_back(new SpringForce(p0, p1, k, d, dy));
            }
            // TODO: add shear springs
            if (i < m && j < n)
            {
              Particle *p1 = particles[i + 1][j + 1];
              psys->forces.push_back(new SpringForce(p0, p1, kdia, d, ddia));
            }
            if(i < m && j > 0)
            {
              Particle *p1 = particles[i + 1][j - 1];
              psys->forces.push_back(new SpringForce(p0, p1, kdia, d, ddia));
            }
        }
    }
}
