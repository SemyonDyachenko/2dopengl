#ifndef MESH_H
#define MESH_H

class Vertex
{
private:
	glm::vec3 pos;
	glm::vec2 texcoord;
	
public:
	
	
	Vertex(const glm::vec3 & pos,const glm::vec2 & texcoord)
	{
		this->pos = pos;
		this->texcoord = texcoord;
	}
	inline glm::vec3 * getPos()
	{
		return &this->pos;
	}
	inline glm::vec2 * getTexCoord()
	{
		return &this->texcoord;
	}
};


class Mesh
{
private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NUMBER_BUFFERS
	};
	
	GLuint VAO;
	
	GLuint VBO[NUMBER_BUFFERS];

	unsigned int num_vertices;

	
	
public:
	Mesh(Vertex* vertices,unsigned int numVertices);
	virtual ~Mesh();

	void Render();
};


#endif