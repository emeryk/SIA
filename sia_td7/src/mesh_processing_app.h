
#ifndef MESH_PROCESSING_APP_H
#define MESH_PROCESSING_APP_H

#include <Eigen/SparseCholesky>
#include "viewer.h"

class MeshProcessingApp : public Viewer {
public:
  //! Constructor
  MeshProcessingApp();
  ~MeshProcessingApp();

  void init(int w, int h, int argc, char **argv);
  void updateScene();

  // events
  void mousePressed(GLFWwindow* window, int button, int action, int mods);
  void mouseMoved(int x, int y);
  void charPressed(int key);
  void keyEvent(int key, int action, int mods);

protected:

  bool pickAt(const Eigen::Vector2f &p, Hit &hit) const;
  bool selectAround(const Eigen::Vector2f &p) const;
  void moveVertex(Vector3f m);

  // main mesh to work on:
  Mesh* _mesh;

  surface_mesh::Surface_mesh::Vertex * selectedVertex = NULL;
  Eigen::Vector3f selectedColor;

  bool first = true;

  Eigen::SparseMatrix<float> L;

  float _pickingRadius = 0.1;
  bool _pickingMode = false;

};

#endif // MESH_PROCESSING_APP_H
