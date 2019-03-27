#pragma once
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <string>
#include <OgreVector3.h>
#include <dirent.h>
#include <jsonParser.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

class Ogre::SceneNode;
class Ogre::Entity;

using json = nlohmann::json;

class TerrainGenerator;

class GestorRecursos 
{
public:
	~GestorRecursos();

	static GestorRecursos* instance();

	Ogre::Camera* createCamera(Ogre::SceneManager* scnMgn, std::string name, Ogre::SceneNode* FatherNode,
				Ogre::Real NearClipDist, Ogre::Real FarClipDist,
				bool autoAspectRatio,  Ogre::Real AspectRatio = 1.3);

	Ogre::Entity* createPlane(Ogre::SceneManager* scnMgn, std::string name, std::string MaterialName,
									Ogre::Real width, Ogre::Real height, int Xsegments, int Ysegments,
									Ogre::SceneNode* FatherNode, std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	TerrainGenerator* createTerrain(Ogre::SceneManager* scnMgn, Ogre::Light* light, std::string terrainFile);

	void initializeResources();
	void ceguiInit();


	json getJsonByKey(const std::string &key);

private:
	GestorRecursos();

	static std::unique_ptr<GestorRecursos> instance_;

	void loadJsonsFiles(const std::string resourcesPath);
	void loadJson(const std::string &streamFilePath, const std::string &fileName);

	const std::string FOLDER_PATH = "Assets\\jsons\\";

	

	//Contenedores de los recursos
	std::map<std::string, json> jsonMap;

};