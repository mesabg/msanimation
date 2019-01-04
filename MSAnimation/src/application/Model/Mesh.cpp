#include <Model/Mesh.h>


pair<GLint, GLint> Mesh::oppositeVerticesToEdge(GLuint i, GLuint j)
{
	SparseMatrix<bool> adjacent = *(this->adjacent);
	GLint r = -1;
	GLint s = -1;

	for (SparseMatrix<bool>::InnerIterator it(adjacent, i); it; ++it) {
		bool edgeA = it.value();
		Index in = it.col();
		Index out = it.row();

		bool edgeB = adjacent.coeff(out, j);

		if (edgeA && edgeB) {
			//-- Both vertices (i and j) have a COMMON EXIT VERTEX
			GLint commonVertex = (GLint)out;
			if (r == -1) r = commonVertex;
			else if (s == -1) s = commonVertex;
			else break;
		}
	}

	return std::make_pair(r, s);
}

Mesh::Mesh(vector<Vertex> vertices, 
	vector<GLuint> indices, 
	vector<Texture> textures, 
	vector<vec3>components, 
	vector<TripletBoolean> adjacency, 
	vec3 min, vec3 max): vertices(vertices), indices(indices), textures(textures), min(min), max(max)
{
	this->buildBuffers();

	//Adjacency matrix
	this->components = components;
	this->adjacent = new SparseBoolean(this->components.size(), this->components.size());
	this->adjacent->setFromTriplets(adjacency.begin(), adjacency.end());
	this->calculateLaplacianMatrix();

	SparseMatrix<GLfloat> laplacian = *(this->laplacian);
	for (int k = 0; k < laplacian.outerSize(); ++k) {
		for (SparseMatrix<GLfloat>::InnerIterator it(laplacian, k); it; ++it) {
			GLfloat value = it.value();
			Index row = it.row();
			Index col = it.col();

			cout << row << ", " << col << ", " << value << endl;
		}
	}

	/*cout << "Adjacent matrix\n" << endl;
	std::cout << MatrixXd( (*(this->adjacent)).cast<double>() ) << std::endl;

	cout << "After laplacian calculation\n";
	std::cout << MatrixXd( (*(this->laplacian)).cast<double>() ) << std::endl;*/
}

Mesh::~Mesh()
{
	// Do something
}

vector<Vertex> Mesh::getVertices()
{
	return this->vertices;
}

vector<GLuint> Mesh::getIndices()
{
	return this->indices;
}

vector<Texture> Mesh::getTextures()
{
	return this->textures;
}

void Mesh::setVertices(vector<Vertex> vertices)
{
	this->vertices = vertices;
}

void Mesh::setIndices(vector<GLuint> indices)
{
	this->indices = indices;
}

void Mesh::setTextures(vector<Texture> textures)
{
	this->textures = textures;
}

void Mesh::render(Shader* shader)
{
	// Bind appropriate textures
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
										  // Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = this->textures[i].type;

		if (name == "texture_diffuse")
		{
			ss << diffuseNr++; // Transfer GLuint to stream
		}
		else if (name == "texture_specular")
		{
			ss << specularNr++; // Transfer GLuint to stream
		}

		number = ss.str();
		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader->getProgram(), (name + number).c_str()), i);
		// And finally bind the texture
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	glUniform1f(glGetUniformLocation(shader->getProgram(), "material.shininess"), 16.0f);

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Mesh::buildBuffers()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &(this->vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &(this->indices[0]), GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(struct Vertex, normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(struct Vertex, texCoords));

	glBindVertexArray(0);
}

void Mesh::normalize()
{
	if (this->min == vec3(0.0f, 0.0f, 0.0f) || this->max == vec3(0.0f, 0.0f, 0.0f)) {
		// Mesh cannot be normalized
		return;
	}

	// Normalize mesh
	float maximun = glm::max(this->max.x, glm::max(this->max.y, this->max.z));

	vec3 centro;
	centro.x = (this->max.x + this->min.x) / 2.0f;
	centro.y = (this->max.y + this->min.y) / 2.0f;
	centro.z = (this->max.z + this->min.z) / 2.0f;

	int index = 0;
	for (Vertex vertex : this->vertices) {
		vec3 position = vertex.position;
		position.x = (position.x - centro.x) / maximun;
		position.y = (position.y - centro.y) / maximun;
		position.z = (position.z - centro.z) / maximun;
		this->vertices[index].position = position;
		index++;
	}

	this->max.x = (this->max.x - centro.x) / 2.0f;
	this->max.y = (this->max.y - centro.y) / 2.0f;
	this->max.z = (this->max.z - centro.z) / 2.0f;

	this->min.x = (this->min.x - centro.x) / 2.0f;
	this->min.y = (this->min.y - centro.y) / 2.0f;
	this->min.z = (this->min.z - centro.z) / 2.0f;
}

SparseMatrix<bool>* Mesh::calculateAdjacentMatrix()
{
	if (this->adjacent != NULL) return this->adjacent;

	SparseBoolean *adjacent = new SparseBoolean(this->vertices.size(), this->vertices.size());
	vector< TripletBoolean > triplets;

	// Iterate over each triangle
	for (GLuint i = 0; i < this->indices.size(); i += 3) {
		GLuint indexA = this->indices[i];
		GLuint indexB = this->indices[i+1];
		GLuint indexC = this->indices[i+2];

		// Add edges as entries
		triplets.push_back(TripletBoolean(indexA, indexB, true));
		triplets.push_back(TripletBoolean(indexB, indexA, true));
		triplets.push_back(TripletBoolean(indexB, indexC, true));
		triplets.push_back(TripletBoolean(indexC, indexB, true));
		triplets.push_back(TripletBoolean(indexA, indexC, true));
		triplets.push_back(TripletBoolean(indexC, indexA, true));
	}

	adjacent->setFromTriplets(triplets.begin(), triplets.end());
	this->adjacent = adjacent;
}

SparseMatrix<GLfloat>* Mesh::calculateLaplacianMatrix()
{
	if (this->laplacian != NULL) return this->laplacian;
	SparseMatrix<GLfloat> *laplacian = new SparseMatrix<GLfloat>(this->components.size(), this->components.size());

	// Per edges, ordered calculation
	SparseMatrix<bool> adjacent = *(this->adjacent);
	//cout << "pair :: (" << r << ", " << s << ")" << endl << endl;
	for (int k = 0; k < adjacent.outerSize(); ++k) {
		for (SparseMatrix<bool>::InnerIterator it(adjacent, k); it; ++it) {
			bool edge = it.value();
			GLuint i = it.row();
			GLuint j = it.col();

			// Up triangle validation (Symmetry)
			if (i > j) continue;

			if (edge) {
				// Opposite vertices to edge (triangles)
				pair<GLint, GLint> opposite = this->oppositeVerticesToEdge(i, j);
				GLint r = opposite.first;
				GLint s = opposite.second;

				// Vectors calculation
				vec3 ri = r != -1 ? this->components[i] - this->components[r] : vec3(0.0f);
				vec3 rj = r != -1 ? this->components[j] - this->components[r] : vec3(0.0f);
				vec3 si = s != -1 ? this->components[i] - this->components[s] : vec3(0.0f);
				vec3 sj = s != -1 ? this->components[j] - this->components[s] : vec3(0.0f);

				// Magnitudes calculation
				GLfloat riMagnitude = glm::length(ri);
				GLfloat rjMagnitude = glm::length(rj);
				GLfloat siMagnitude = glm::length(si);
				GLfloat sjMagnitude = glm::length(sj);

				// Dot product calculation
				GLfloat riXrj = glm::dot(ri, rj);
				GLfloat siXsj = glm::dot(si, sj);

				// Angles calculation
				GLfloat cosTheta = riXrj / (riMagnitude*rjMagnitude);
				GLfloat cosAlpha = siXsj / (siMagnitude*sjMagnitude);
				GLfloat theta = glm::acos(cosTheta);
				GLfloat alpha = glm::acos(cosAlpha);

				// Laplacian definition
				GLfloat cotTheta = r != -1 ? glm::cot(theta) : 0.0f;
				GLfloat cotAlpha = s != -1 ? glm::cot(alpha) : 0.0f;
				GLfloat wij = cotTheta + cotAlpha;
				laplacian->insert(i, j) = wij;
				laplacian->insert(j, i) = wij;
				laplacian->coeffRef(i, i) += (-1.0f*wij);
				laplacian->coeffRef(j, j) += (-1.0f*wij);
			}
			else continue;
		}
	}

	this->laplacian = laplacian;
	return this->laplacian;
}