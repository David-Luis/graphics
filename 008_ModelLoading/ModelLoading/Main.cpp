#include <ModeLoadingApplication.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
	ModeLoadingApplication* app = new ModeLoadingApplication();
	app->Init();
}