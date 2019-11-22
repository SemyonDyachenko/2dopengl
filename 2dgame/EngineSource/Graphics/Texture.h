#ifndef ENIGNE_TEXTURE_H
#define ENGINE_TEXTURE_H


namespace Engine

{

	class Texture
	{
	private:
		GLuint id;
		int width, height;
		GLenum target;
		GLint unit;
	public:
		Texture(GLenum target);

		GLint & getUnit();

		~Texture();

		void loadFromFile(const char *path);

		void bind();

		void unbind();
	};


}

#endif
