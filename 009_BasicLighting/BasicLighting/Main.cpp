#include <BasicLightingApplication.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
	BasicLightingApplication* app = new BasicLightingApplication();
	app->Init();
}