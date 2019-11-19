#pragma once
#include <glm/detail/type_vec3.hpp>


namespace GameEngine
{

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texcoord;
		glm::vec3 normal;
	};

}
