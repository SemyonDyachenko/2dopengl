#include "Mesh.h"


namespace GameEngine
{
	
	


	void Mesh::initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray,
		const unsigned& nrOfIndices)
	{
		this->number_of_vertices = nrOfVertices;
		this->number_of_indices = nrOfIndices;

		//Create VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->number_of_vertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->number_of_indices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

		//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//Texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//BIND VAO 0
		glBindVertexArray(0);
	}

	void Mesh::initVAO(Primitive* primitive)
	{
		//Set variables
		this->number_of_vertices = primitive->getNrOfVertices();
		this->number_of_indices = primitive->getNrOfIndices();

		//Create VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->number_of_vertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->number_of_indices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);

		//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//Texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//BIND VAO 0
		glBindVertexArray(0);
		glBindVertexArray(0);
		
	}


	void Mesh::initMatrix()
	{
		this->position = glm::vec3(0.f);
		this->rotation = glm::vec3(0.f);
		this->scale = glm::vec3(1.f);
		
	}

	void Mesh::updateUniforms(Shader *shader)
	{
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}
	

	Mesh::Mesh(Vertex* vertexArray, const unsigned& number_of_vertices, GLuint* indexArray,
		const unsigned& number_of_indices)
	{

		this->initVAO(vertexArray, number_of_vertices, indexArray, number_of_indices);
		this->initMatrix();
	}

	Mesh::Mesh(Primitive* primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVAO(primitive);
		this->initMatrix();
	}


	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteVertexArrays(1, &this->VBO);
		glDeleteVertexArrays(1, &this->EBO);
	}

	void Mesh::update()
	{

	}


	void Mesh::render(Shader*shader)
	{
		this->updateUniforms(shader);

		shader->useProgram();
		
		glBindVertexArray(this->VAO);

		//render
		glDrawElements(GL_TRIANGLES, this->number_of_indices, GL_UNSIGNED_INT, 0);
	}
	
}
