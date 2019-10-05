#pragma once



#include <string>
#include <vector>
#include <map>

class ShaderManager
{
public:
	class Shader
	{
	public:
		Shader();
		~Shader();
		enum eShaderType
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			UNKNOWN
		};
		eShaderType shaderType;
		std::string getShaderTypeString(void);

		unsigned int ID;	// or "name" from OpenGL
		std::vector<std::string> vecSource;
		bool bSourceIsMultiLine;
		std::string fileName;

	};

	class ShaderProgram
	{
	public:
		ShaderProgram() : ID(0) {};
		~ShaderProgram() {};
		unsigned int ID;	// ID from OpenGL (calls it a "name")
		std::string friendlyName;	// We give it this name

		// TODO: For the students to do, because it's FUN, FUN, FUN
		std::map< std::string, /*name of uniform variable*/
				  int  >/* uniform location ID */
			mapUniformName_to_UniformLocation;
		// Returns -1 (just like OpenGL) if NOT found
		int getUniformID_From_Name(std::string name);
		// Look up the uniform location and save it.
		bool LoadUniformLocation(std::string variableName);

	};

	ShaderManager();
	~ShaderManager();

	bool useShaderProgram(unsigned int ID);
	bool useShaderProgram(std::string friendlyName);
	bool createProgramFromFile(std::string friendlyName,
							   Shader& vertexShad,
							   Shader& fragShader);
	void setBasePath(std::string basepath);
	unsigned int getIDFromFriendlyName(std::string friendlyName);

	// Used to load the uniforms. Returns NULL if not found.
	ShaderProgram* pGetShaderProgramFromFriendlyName(std::string friendlyName);


	// Clears last error
	std::string getLastError(void);
private:
	// Returns an empty string if it didn't work
	bool m_loadSourceFromFile(Shader& shader);
	std::string m_basepath;

	bool m_compileShaderFromSource(Shader& shader, std::string& error);
	// returns false if no error
	bool m_wasThereACompileError(unsigned int shaderID, std::string& errorText);
	bool m_wasThereALinkError(unsigned int progID, std::string& errorText);

	std::string m_lastError;

	std::map< unsigned int /*ID*/, ShaderProgram > m_ID_to_Shader;
	std::map< std::string /*name*/, unsigned int /*ID*/ > m_name_to_ID;
};