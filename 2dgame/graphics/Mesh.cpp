#include "../stdafx.h"
#include "Mesh.h"



Mesh::Mesh(Vertex* vertices, unsigned numVertices)
{
	this->num_vertices = numVertices;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(VAO);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoord;

	positions.reserve(numVertices);
	texcoord.reserve(numVertices);


	for(unsigned int i = 0;i < numVertices;i++)
	{
		positions.push_back(*vertices[i].getPos());
		texcoord.push_back(*vertices[i].getTexCoord());
	}

	glGenBuffers(NUMBER_BUFFERS, VBO);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	

	

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texcoord[0]), &texcoord[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void Mesh::Render()
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, this->num_vertices);
	
	
	glBindVertexArray(0);
}
