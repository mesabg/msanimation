#include <Model/ComplexMesh.h>

ComplexMesh::ComplexMesh()
{
	//-- Do something
}

ComplexMesh::ComplexMesh(MatrixXd vertices, MatrixXi indices)
{
	this->vertices = vertices;
	this->indices = indices;
}

ComplexMesh::~ComplexMesh()
{
	//-- Do something
}

MatrixXd ComplexMesh::getVertices()
{
	return this->vertices;
}

MatrixXi ComplexMesh::getIndices()
{
	return this->indices;
}

void ComplexMesh::setVertices(MatrixXd vertices)
{
	this->vertices = vertices;
}

void ComplexMesh::setIndices(MatrixXi indices)
{
	this->indices = indices;
}

/*SparseMatrix<double> ComplexMesh::calculateLaplacian()
{
	SparseMatrix<double> L;
	igl::cotmatrix(this->vertices, this->indices, L);
	return L;
}*/
