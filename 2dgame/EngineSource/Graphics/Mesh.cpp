#include "Mesh.h"


namespace GameEngine
{
	
	void Mesh::initVertexData(Vertex* vertexArray, const unsigned& number_of_vertices, GLuint* indexArray,
		const unsigned& number_of_indices)
	{
		
		for(size_t i = 0; i < number_of_vertices;i++)
		{
			this->vertices.push_back(vertexArray[i]);
		}

		for(size_t i = 0;i < number_of_indices;i++)
		{
			this->indices.push_back(indexArray[i]);
		}
	}

	void Mesh::initVAO()
	{
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		glBindVertexArray(0); // Unbind VAO
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
		
	}


	void Mesh::initMatrix()
	{
		this->position = glm::vec3(0.f);
		this->rotation = glm::vec3(0.f);
		this->scale = glm::vec3(1.f);

		
		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
		
	}

	void Mesh::updateUniforms(Shader *shader)
	{
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}
	

	Mesh::Mesh(Vertex* vertexArray, const unsigned& number_of_vertices, GLuint* indexArray,
		const unsigned& number_of_indices)
	{

		this->initVertexData(vertexArray, number_of_vertices, indexArray, number_of_indices);
		this->initVAO();
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

		glBindVertexArray(this->VAO);

		//render
		if(indices.empty())
			glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
		else
			glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	}
	
}
