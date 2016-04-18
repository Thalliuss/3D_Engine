#include "model.h"


Model::Model()
{
	_texture = NULL;
}

Model::~Model()
{

}

void Model::addMesh(const char* o, const char* string)
{
	texture_name = string;
	if(string != NULL){
		std::cout << "##### New Model Initialized  #####" << std::endl;
		_texture = t->loadDDS(texture_name.c_str());
	}else {
		_texture = t->loadDDS("assets/temp.DDS");
	}

	object_name = o;
	loadOBJ(object_name.c_str(), _vertices, _uvs, _normals);

	std::cout << "\n" << std::endl;
}

bool Model::loadOBJ(
	const char* path,
	std::vector<vec3> & out_vertices,
	std::vector<vec2> & out_uvs,
	std::vector<vec3> & out_normals
	) {
	printf("Reading .OBJ file %s\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<vec3> temp_vertices;
	std::vector<vec2> temp_uvs;
	std::vector<vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! ");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		vec3 vertex = temp_vertices[vertexIndex - 1];
		vec2 uv = temp_uvs[uvIndex - 1];
		vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}
	buffers();
	return true;
}

void Model::buffers() {
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(vec3), &vertices()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs().size() * sizeof(vec2), &uvs()[0], GL_STATIC_DRAW);


	glGenBuffers(1, &_normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals().size() * sizeof(vec3), &normals()[0], GL_STATIC_DRAW);
}
