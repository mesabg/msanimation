#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4146)

// Global includes
#include <vector>
//#include <igl/cotmatrix.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>

// Using spaces
using Eigen::MatrixXd;
using Eigen::MatrixXi;
using Eigen::SparseMatrix;

// Using spaces
using std::vector;

class ComplexMesh {
private:

	// Brute Data
	MatrixXd vertices;
	MatrixXi indices;

public:
	ComplexMesh();
	ComplexMesh(MatrixXd vertices, MatrixXi indices);
	~ComplexMesh();

	// Getter and setters
	MatrixXd getVertices();
	MatrixXi getIndices();
	void setVertices(MatrixXd vertices);
	void setIndices(MatrixXi indices);

	// General functions
	//SparseMatrix<double> calculateLaplacian();
};