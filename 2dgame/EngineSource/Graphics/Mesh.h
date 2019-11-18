#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../Shaders/Shader.h"
#include "Primitives.h"

class Primitive;



namespace GameEngine
{
	class Shader;

	class Mesh
	{
	private:
		unsigned number_of_vertices;
		unsigned number_of_indices;
		
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;


		GLuint VAO; // vertex array object
		GLuint VBO; // vertex buffer object
		GLuint EBO; // elements buffer object


		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 ModelMatrix;

		
		void initVertexData(Vertex* vertexArray, const unsigned & number_of_vertices, GLuint * indexArray, const unsigned & number_of_indices);

		void initVAO();

		void initVAO(Primitive* primitive);

		
		void initMatrix();

		void updateUniforms(Shader *shader);
	public:
		Mesh(Vertex* vertexArray, const unsigned& number_of_vertices, GLuint* indexArray,
			const unsigned& number_of_indices);

		Mesh(Primitive* primitive, glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));

		
		~Mesh();

		
		void update();
		
		void render(Shader*shader);
		
	};

}


#endif