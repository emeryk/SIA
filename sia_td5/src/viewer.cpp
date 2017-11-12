#include "viewer.h"
#include "camera.h"
#include "quad.h"

extern int WIDTH;
extern int HEIGHT;

using namespace Eigen;

Viewer::Viewer()
{
}

Viewer::~Viewer()
{
}

////////////////////////////////////////////////////////////////////////////////
// GL stuff

// initialize OpenGL context
void Viewer::init(int w, int h){
    _winWidth = w;
    _winHeight = h;

    // Couleur d'arrière plan
    glClearColor(0.0, 0.0, 0.0, 0.0);

    loadProgram();

    Quad* quad = new Quad();
    quad->init();
    quad->setTransformationMatrix( AngleAxisf((float)M_PI_2, Vector3f(-1,0,0)) * Scaling(20.f,20.f,1.f) * Translation3f(0,0,-0.5));
    _shapes.push_back(quad);
    _specularCoef.push_back(0.);

    Mesh* mesh = new Mesh();
    mesh->load(DATA_DIR"/models/tw.off");
    mesh->init();
    _shapes.push_back(mesh);
    _specularCoef.push_back(0.75);

    mesh = new Mesh();
    mesh->load(DATA_DIR"/models/sphere.off");
    mesh->init();
    mesh->setTransformationMatrix(Translation3f(0,0,2.f) * Scaling(0.5f) );
    _shapes.push_back(mesh);
    _specularCoef.push_back(0.2);

    Sphere* sphere1 = new Sphere(0.020f);
    sphere1->init();
    sphere1->setTransformationMatrix(Affine3f(Translation3f(1.0, 1.0, 1.0)));
    _pointLight.push_back(sphere1);

    Sphere* sphere2 = new Sphere(0.040f);
    sphere2->init();
    sphere2->setTransformationMatrix(Affine3f(Translation3f(1.0, 1.0, -1.0)));
    _pointLight.push_back(sphere2);

    Sphere* sphere3 = new Sphere(0.050f);
    sphere3->init();
    sphere3->setTransformationMatrix(Affine3f(Translation3f(-1.0, 1.0, 1.0)));
    _pointLight.push_back(sphere3);

    Vector3f c1 = Vector3f(1.0, 1.0, 1.0);
    Vector3f c2 = Vector3f(1.0, 0.5, 0.0);
    Vector3f c3 = Vector3f(1.0, 0.0, 1.0);

    _lightColor.push_back(c1);
    _lightColor.push_back(c2);
    _lightColor.push_back(c3);

    AlignedBox3f aabb;
    for(int i=0; i<_shapes.size(); ++i)
        aabb.extend(_shapes[i]->boundingBox());

    _cam.setSceneCenter(aabb.center());
    _cam.setSceneRadius(aabb.sizes().maxCoeff());
    _cam.setSceneDistance(_cam.sceneRadius() * 3.f);
    _cam.setMinNear(0.1f);
    _cam.setNearFarOffsets(-_cam.sceneRadius() * 100.f,
                            _cam.sceneRadius() * 100.f);
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));

    fbo.init(w, h);

    quad1.init();

    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
}

void Viewer::reshape(int w, int h){
    _winWidth = w;
    _winHeight = h;
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));
    glViewport(0, 0, w, h);
}


/*!
   callback to draw graphic primitives
 */
void Viewer::display()
{
    /*fbo.bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _gbufferPrg.activate();

    glUniformMatrix4fv(_gbufferPrg.getUniformLocation("projection_matrix"), 1, false, _cam.computeProjectionMatrix().data());
    glUniformMatrix4fv(_gbufferPrg.getUniformLocation("view_matrix"), 1, false, _cam.computeViewMatrix().data());

    for(int i=0; i<_shapes.size(); ++i)
    {
        glUniformMatrix4fv(_gbufferPrg.getUniformLocation("model_matrix"),1,false,_shapes[i]->getTransformationMatrix().data());
        Matrix3f normal_matrix = (_cam.computeViewMatrix()*_shapes[i]->getTransformationMatrix()).linear().inverse().transpose();
        glUniformMatrix3fv(_gbufferPrg.getUniformLocation("normal_matrix"), 1, false, normal_matrix.data());
        glUniform1f(_gbufferPrg.getUniformLocation("specular_coef"),_specularCoef[i]);

        _shapes[i]->display(&_gbufferPrg);
    }

    _gbufferPrg.deactivate();

    fbo.unbind();
    fbo.savePNG("couleurs", 0);
    fbo.savePNG("normales", 1);*/

    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    _blinnPrg.activate();

    glUniformMatrix4fv(_blinnPrg.getUniformLocation("projection_matrix"),1,false,_cam.computeProjectionMatrix().data());
    glUniformMatrix4fv(_blinnPrg.getUniformLocation("view_matrix"),1,false,_cam.computeViewMatrix().data());

    // draw meshes
    for(int i=0; i<_pointLight.size(); ++i)
    {
        glUniformMatrix4fv(_blinnPrg.getUniformLocation("model_matrix"),1,false,_shapes[i]->getTransformationMatrix().data());
        Matrix3f normal_matrix = (_cam.computeViewMatrix()*_shapes[i]->getTransformationMatrix()).linear().inverse().transpose();
        glUniformMatrix3fv(_blinnPrg.getUniformLocation("normal_matrix"), 1, GL_FALSE, normal_matrix.data());
        glUniform1f(_blinnPrg.getUniformLocation("specular_coef"),_specularCoef[i]);
        glUniform3fv(_blinnPrg.getUniformLocation("light_col"),1,_lightColor[i].data());

        _shapes[i]->display(&_blinnPrg);
    }

    _blinnPrg.deactivate();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    // Draw pointlight sources
    for (int i(0); i < _pointLight.size(); i++)
    {
      _simplePrg.activate();
      glUniformMatrix4fv(_simplePrg.getUniformLocation("projection_matrix"),1,false,_cam.computeProjectionMatrix().data());
      glUniformMatrix4fv(_simplePrg.getUniformLocation("view_matrix"),1,false,_cam.computeViewMatrix().data());
      glUniformMatrix4fv(_simplePrg.getUniformLocation("model_matrix"),1,false,_pointLight[i]->getTransformationMatrix().data());
      glUniform3fv(_simplePrg.getUniformLocation("light_col"),1,_lightColor[i].data());
      _pointLight[i]->display(&_simplePrg);
      _simplePrg.deactivate();
    }
}


void Viewer::updateScene()
{
    display();
}

void Viewer::loadProgram()
{
    _blinnPrg.loadFromFiles(DATA_DIR"/shaders/blinn.vert", DATA_DIR"/shaders/blinn.frag");
    _simplePrg.loadFromFiles(DATA_DIR"/shaders/simple.vert", DATA_DIR"/shaders/simple.frag");
    _gbufferPrg.loadFromFiles(DATA_DIR"/shaders/gbuffer.vert", DATA_DIR"/shaders/gbuffer.frag");
    _deferredPrg.loadFromFiles(DATA_DIR"/shaders/deferred.vert", DATA_DIR"/shaders/deferred.frag");
    checkError();
}

////////////////////////////////////////////////////////////////////////////////
// Events

/*!
   callback to manage mouse : called when user press or release mouse button
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::mousePressed(GLFWwindow *window, int button, int action)
{
    if(action == GLFW_PRESS) {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            _cam.startRotation(_lastMousePos);
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            _cam.startTranslation(_lastMousePos);
        }
        _button = button;
    }else if(action == GLFW_RELEASE) {
        if(_button == GLFW_MOUSE_BUTTON_LEFT)
        {
            _cam.endRotation();
        }
        else if(_button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            _cam.endTranslation();
        }
        _button = -1;
    }
}


/*!
   callback to manage mouse : called when user move mouse with button pressed
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::mouseMoved(int x, int y)
{
    if(_button == GLFW_MOUSE_BUTTON_LEFT)
    {
        _cam.dragRotate(Vector2f(x,y));
    }
    else if(_button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        _cam.dragTranslate(Vector2f(x,y));
    }
    _lastMousePos = Vector2f(x,y);
}

void Viewer::mouseScroll(double x, double y)
{
    _cam.zoom((y>0)? 1.1: 1./1.1);
}

/*!
   callback to manage keyboard interactions
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::keyPressed(int key, int action, int mods)
{
    if(key == GLFW_KEY_R && action == GLFW_PRESS)
        loadProgram();
}

void Viewer::charPressed(int key)
{
}
