
#include "mesh_processing_app.h"
#include "neighborhood.h"
#include "laplacian.h"

using namespace Eigen;
using namespace surface_mesh;

MeshProcessingApp::MeshProcessingApp()
 : Viewer(), _mesh(0)
 {
 }

MeshProcessingApp::~MeshProcessingApp()
{
  delete _mesh;
}

void MeshProcessingApp::init(int w, int h, int argc, char **argv)
{
  std::cout << "Usage: " << argv[0] << " [file]" << std::endl;
  std::cout << "  where must be a mesh file (e.g. .off) " << std::endl << std::endl;
  std::cout << "**************************************************" << std::endl;
  std::cout << "Selection:" << std::endl;
  std::cout << "  ctrl+left+drag: selection" << std::endl;
  std::cout << "  s:    enable/disable display of selected vertices" << std::endl;
  std::cout << "  c:    clear the selection" << std::endl;
  std::cout << "Mesh processing:" << std::endl;
  std::cout << "  y/Y:  decrease/increase selection brush size" << std::endl << std::endl;
  std::cout << "  1:    perform harmonic interpolation" << std::endl;
  std::cout << "  2:    perform bi-harmonic interpolation" << std::endl;
  std::cout << "  3:    perform tri-harmonic interpolation" << std::endl;



  _mesh = new Mesh();
  if(argc>1)
    _mesh->load(argv[1]);
  else
  {
//     _mesh->load(DATA_DIR"/models/sphere.off");
    _mesh->load(DATA_DIR"/models/bunny70k.off");
//   _mesh->load(DATA_DIR"/models/colorfull.off");
  }
  _mesh->init();
  _meshes.push_back(Object3D(_mesh,&_main_shader));

  _pickingRadius = 0.03 * _mesh->boundingBox().sizes().maxCoeff();

  Viewer::init(w,h,argc,argv);
}


bool MeshProcessingApp::pickAt(const Eigen::Vector2f &p, Hit &hit) const
{
  Matrix4f proj4 = _cam.projectionMatrix();
  Matrix3f proj3;
  proj3 << proj4.topLeftCorner<2,3>(),
           proj4.bottomLeftCorner<1,3>();
  Matrix4f C = _cam.viewMatrix().inverse();

  Vector3f q(  (2.0*float(p.x() + 0.5f)/float(_winWidth)  - 1.),
              -(2.0*float(p.y() + 0.5f)/float(_winHeight) - 1.),
                1);

  Ray ray;
  ray.origin = C.col(3).head<3>();
  ray.direction = C.topLeftCorner<3,3>() * (proj3.inverse() * q);
  return _mesh->intersect(ray, hit);
}

bool MeshProcessingApp::selectAround(const Eigen::Vector2f &p) const
{
  Hit hit;
  if(pickAt(p,hit))
  {
    // Here we found the closest triangle under the mouse pointer (its index is "hit.faceId()").
    // Let's found the closest vertex and extend the selection through select_neighbors:
    int clostest_id = 0;
    hit.baryCoords().maxCoeff(&clostest_id);
    Surface_mesh::Vertex closest_v(_mesh->faceIndices()(clostest_id,hit.faceId()));
    std::vector<Surface_mesh::Vertex> neighbors = select_neighbors(*_mesh, closest_v, _pickingRadius);
    auto masks = _mesh->get_vertex_property<int>("v:mask");
    for(auto v:neighbors)
      masks[v] = 1;
    return true;
  }
  return false;
}

/*!
   callback to manage mouse : called when user press or release mouse button
   You can change in this function the way the user
   interact with the system.
 */
void MeshProcessingApp::mousePressed(GLFWwindow *window, int button, int action, int mods)
{
  if((mods&GLFW_MOD_CONTROL)==GLFW_MOD_CONTROL)
  {
    if(action == GLFW_PRESS)
    {
      // picking
      _pickingMode = true;
      _disp_selection = true;
      if(selectAround(_lastMousePos.cast<float>()))
        _mesh->updateVBO();
    }
    else
    {
      _pickingMode = false;
    }
  }
  else if((mods&GLFW_MOD_SHIFT)==GLFW_MOD_SHIFT)
  {
    if(action == GLFW_PRESS)
    {
      Hit hit;
      if(pickAt(_lastMousePos.cast<float>(), hit))
      {
        int clostest_id = 0;
        hit.baryCoords().maxCoeff(&clostest_id);
        Surface_mesh::Vertex * tmpVert = new Surface_mesh::Vertex(_mesh->faceIndices()(clostest_id, hit.faceId()));
        auto masks = _mesh->get_vertex_property<int>("v:mask");
        auto colors = _mesh->get_vertex_property<Vector3f>("v:color");

        if (selectedVertex != NULL)
        {
          colors[*selectedVertex] = selectedColor;
          masks[*selectedVertex] = 1;
          selectedVertex = NULL;
        }

        if (masks[*tmpVert] == 1)
        {
          masks[*tmpVert] = 0;
          selectedVertex = tmpVert;
          selectedColor = colors[*tmpVert];
          colors[*tmpVert] = Vector3f(0, 0, 1);
        }
        _mesh->updateVBO();
      }
    }
  }
  else
    Viewer::mousePressed(window,button,action,mods);
}

/*!
   callback to manage mouse : called when user move mouse with button pressed
   You can change in this function the way the user
   interact with the system.
 */
void MeshProcessingApp::mouseMoved(int x, int y)
{
  if(_pickingMode)
  {
    if(selectAround(Vector2f(x,y)))
      _mesh->updateVBO();
  }
  else
  {
    Viewer::mouseMoved(x,y);
  }
  _lastMousePos = Vector2i(x,y);
}

void MeshProcessingApp::updateScene()
{
  Viewer::updateScene();
}

void MeshProcessingApp::moveVertex(Vector3f m)
{
  if (selectedVertex != NULL)
  {
    auto deplacement = _mesh->get_vertex_property<Vector3f>("v:deplacement");
    deplacement[*selectedVertex] += m;
    _mesh->updateVBO();
  }
}

void MeshProcessingApp::keyEvent(int key, int action, int mods)
{
  if (key == GLFW_KEY_X && action > 0)
  {
    Vector3f m(1, 0, 0);
    if (mods == GLFW_MOD_SHIFT)
      m = Vector3f(-1, 0, 0);
    moveVertex(m);
  }
  else if (key == GLFW_KEY_Y && action > 0)
  {
    Vector3f m(0, 1, 0);
    if (mods == GLFW_MOD_SHIFT)
      m = Vector3f(0, -1, 0);
    moveVertex(m);
  }
  else if (key == GLFW_KEY_Z && action > 0)
  {
    Vector3f m(0, 0, 1);
    if (mods == GLFW_MOD_SHIFT)
      m = Vector3f(0, 0, -1);
    moveVertex(m);
  }
}

void MeshProcessingApp::charPressed(int key)
{
  if(key==GLFW_KEY_Y)
  {
    _pickingRadius *= 1.2;
  }
  else if(key=='y')
  {
    _pickingRadius /= 1.2;
  }
  else if(key=='c')
  {
    _mesh->masks().setZero();
    _mesh->updateVBO();
  }
  else if(key >= GLFW_KEY_1 && key <= GLFW_KEY_3)
  {
    int k = key-GLFW_KEY_1+1; // k = 1, 2 ou 3 (harmonique, bi-harmonique, tri-harmonique
    // TODO appeler _mesh->poly_harmonic_interpolation avec l'attribut que l'on souhaite reconstruire/interpoler,
    //      et mettre à jour le maillage en fonction de ce qui a été modifié
    poly_harmonic_interpolation(*_mesh, _mesh->positions(), k);
//     poly_harmonic_interpolation(*_mesh,_mesh->colors(), k);
    _mesh->updateAll();
  }
  else
    Viewer::charPressed(key);
}
