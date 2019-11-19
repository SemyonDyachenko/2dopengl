#include "Game.h"


void Game::initGLFW()
{
	//INIT GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initWindow(const char* winTitle)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_RESIZABLE, true);

	this->window = glfwCreateWindow(this->SCREEN_WIDTH, this->SCREEN_HEIGHT, winTitle, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	glfwMakeContextCurrent(this->window); //IMPORTANT!!
}

void Game::initGLEW()
{
	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initOpenGL()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Game::initShaders()
{
	char vertex_file[] = "vertex_core.glsl";
	char fragment_file[] = "fragment_core.glsl";

	this->shader = new GameEngine::Shader(vertex_file, fragment_file);
}

void Game::initTextures()
{

	this->texture = new GameEngine::Texture();
	this->texture->loadFromFile("../res/images/tree.png", GL_TEXTURE_2D);
}

void Game::initMeshes()
{
	GameEngine::Vertex vertices[] =
	{
		//Position								//Color							//Texcoords					//Normals
		glm::vec3(-0.5f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, 0.5f, 0.f),			glm::vec3(1.f, 1.f, 0.f),	    glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(GameEngine::Vertex);

	GLuint indices[] =
	{
		0, 1, 2,	//Triangle 1
		0, 2, 3		//Triangle 2
	};
	nrOfIndices = sizeof(indices) / sizeof(GLuint);





	//Create VAO
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//GEN VBO AND BIND AND SEND DATA
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, nrOfVertices * sizeof(GameEngine::Vertex), vertices, GL_STATIC_DRAW);

	//GEN EBO AND BIND AND SEND DATA
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrOfIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

	//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GameEngine::Vertex), (GLvoid*)offsetof(GameEngine::Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GameEngine::Vertex), (GLvoid*)offsetof(GameEngine::Vertex, color));
	glEnableVertexAttribArray(1);
	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GameEngine::Vertex), (GLvoid*)offsetof(GameEngine::Vertex, texcoord));
	glEnableVertexAttribArray(2);
	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(GameEngine::Vertex), (GLvoid*)offsetof(GameEngine::Vertex, normal));
	glEnableVertexAttribArray(3);

	//BIND VAO 0
	glBindVertexArray(0);

	
	this->mesh = new GameEngine::Mesh(vertices,nrOfVertices,indices,nrOfIndices);
}

Game::Game(const char* winTitle) 
{
	this->SCREEN_WIDTH = 1440;
	this->SCREEN_HEIGHT = 900;
	
	//this->window = nullptr;
	this->framebufferWidth = this->SCREEN_WIDTH;
	this->framebufferHeight = this->SCREEN_HEIGHT;



	
	this->initGLFW();
	this->initWindow(winTitle);
	this->initGLEW();
	this->initOpenGL();
	this->initShaders();
	this->initTextures();
	this->initMeshes();
	
}


Game::~Game()
{

	glfwDestroyWindow(this->window);
	glfwTerminate();
	delete this->shader;
	delete this->texture;
	delete this->mesh;
}






void Game::update()
{
		glfwPollEvents();
		//time
		this->currentTime = static_cast<float>(glfwGetTime());
		this->deltaTime = currentTime - lastTime;
		this->lastTime = currentTime;
		glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
}

void Game::render()
{
	glClearColor(0.f,0.f,0.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	
	this->shader->useProgram();

	this->shader->set1i(0, "texture0");
	this->texture->bind(GL_TEXTURE_2D,0);

	glBindVertexArray(this->VAO);

	//render
	glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
	// Swap the screen buffers
	glfwSwapBuffers(window);
	
	glFlush();
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
 
void Game::run()
{
	
	while (!glfwWindowShouldClose(window))
	{
		this->update();
		this->render();
	}

}