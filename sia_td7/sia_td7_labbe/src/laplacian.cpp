
#include "mesh.h"
#include "laplacian.h"
#include <Eigen/SparseCholesky>

using namespace Eigen;
using namespace surface_mesh;

typedef SparseMatrix<float> SpMat;
typedef PermutationMatrix<Dynamic> Permutation;
typedef Eigen::Triplet<double> T;

double cotan_weight(const Surface_mesh& mesh, Surface_mesh::Halfedge he)
{
  auto points = mesh.get_vertex_property<Point>("v:point");

  // TODO

  Surface_mesh::Vertex pj = mesh.to_vertex(he);
  Surface_mesh::Vertex pk = mesh.to_vertex(mesh.next_halfedge(he));
  he = mesh.opposite_halfedge(he);
  Surface_mesh::Vertex pi = mesh.from_vertex(he);
  Surface_mesh::Vertex pl = mesh.to_vertex(mesh.next_halfedge(he));

  Vector3f vli = points[pl] - points[pi];
  Vector3f vlj = points[pl] - points[pj];
  Vector3f vki = points[pk] - points[pi];
  Vector3f vkj = points[pk] - points[pj];

  float cosA = vli.dot(vki) / (vli.norm() * vki.norm());
  float sinA = vli.cross(vki).norm() / (vli.norm() * vki.norm());
  float cosB = vlj.dot(vkj) / (vlj.norm() * vkj.norm());
  float sinB = vlj.cross(vkj).norm() / (vlj.norm() * vkj.norm());

  float cotA = cosA / sinA;
  float cotB = cosB / sinB;

  return (cotA + cotB) / 2.f;
}

/// Computes the Laplacian matrix in matrix \a L using cotangent weights or the graph Laplacian if useCotWeights==false.
void create_laplacian_matrix(const Surface_mesh& mesh, SpMat& L, bool useCotWeights)
{
  // number of vertices in mesh
  int n = mesh.n_vertices();

  // TODO
  std::vector<T> tripletList;
  tripletList.reserve(n);

  Surface_mesh::Vertex_iterator it;
  for (it = mesh.vertices_begin(); it != mesh.vertices_end(); ++it)
  {
    Surface_mesh::Halfedge he = mesh.halfedge(*it);
    float wii = 0;
    Surface_mesh::Vertex v = *it;
    for (auto vj : mesh.vertices(v))
    {
      if (useCotWeights)
        float wij = cotan_weight(mesh, he);
      float wij = 1;
      tripletList.push_back(T(v.idx(), vj.idx(), wij));
      wii += wij;
    }
    tripletList.push_back(T(v.idx(), v.idx(), -wii));
  }
  L.setFromTriplets(tripletList.begin(), tripletList.end());
}

/// Computes the permutation putting selected vertices (mask==1) first, and the others at the end.
/// It returns the number of selected vertices.
int create_permutation(const Surface_mesh& mesh, Permutation & perm)
{
  auto masks = mesh.get_vertex_property<int>("v:mask");

  // number of vertices in mesh
  int n = mesh.n_vertices();

  // TODO
  perm.resize(n);

  int nb_unknowns = 0;
  int nb_knowns = n - 1;
  Surface_mesh::Vertex_iterator it;
  for (it = mesh.vertices_begin(); it != mesh.vertices_end(); ++it)
  {
    Surface_mesh::Vertex v = *it;
    if (masks[v] == 1)
    {
      perm.indices()[v.idx()] = nb_unknowns;
      nb_unknowns++;
    }
    else
    {
      perm.indices()[v.idx()] = nb_knowns;
      nb_knowns--;
    }
  }

  return nb_unknowns;
}

/// Performs the poly-harmonic interpolation (order k) over the selected vertices (mask==1) of the vertex attributes u.
/// For each vertex V of index i,
///     if  mask[V]!=1 then u.col(i) is used as input constraints,
///     otherwise, mask[V}==1, and u.col(i) is replaced by the poly-harmonic interpolation of the fixed values.
void poly_harmonic_interpolation(const Surface_mesh& mesh, Ref<MatrixXf> u, int k)
{
  // Number of vertices in the mesh
  int n = mesh.n_vertices();

  // 1 - Create the sparse Laplacian matrix
  SpMat L(n,n);
  create_laplacian_matrix(mesh, L, false);

  SpMat cpt = L;

  for (int i = 0; i < k - 1; i++)
    L = L * cpt;

  // 2 - Create the permutation matrix putting the fixed values at the end,
  //     and the true unknown at the beginning
  Permutation perm;
  int nb_unknowns = create_permutation(mesh, perm);

  // 3 - Apply the permutation to both rows (equations) and columns (unknowns),
  //     i.e., L = P * L * P^-1

  // TODO
  L = L.twistedBy(perm);

  // 4 - solve L * [x^T u^T]^T = 0, i.e., L00 x = - L01 * u

  // TODO
  MatrixXf up = perm * u.transpose();

  SpMat LTL = L.topLeftCorner(nb_unknowns, nb_unknowns);
  SpMat LTR = L.topRightCorner(nb_unknowns, n - nb_unknowns);

  SimplicialLDLT<SpMat> solver;
  solver.compute(LTL);
  up.topRows(nb_unknowns) = solver.solve( - LTR * up.bottomRows(n - nb_unknowns));

  // 5 - Copy back the results to u

  // TODO
  up = perm.inverse() * up;
  u = up.transpose();
}
