#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H
#include "Vertex.h"
#include "../Shaders/Shader.h"



class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	
	GLuint VAO, VBO, EBO;

	void setupMesh();
public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, );

	~Mesh();


	void Render(Shader shader);
};


#endif