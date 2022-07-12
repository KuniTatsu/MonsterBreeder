#pragma once
#include"Scene.h"
#include"../../dxlib_ext/dxlib_ext.h"

#include<vector>
#include<list>
#include<string>
#include<memory>


class GameManager;
class MapManager;
class Camera;
class Player;
class Object;

class TitleScene :public BaseScene
{
public:
	TitleScene();
	~TitleScene();


	void Update();
	void Draw();

private:

	GameManager* gManager = nullptr;
	MapManager* mManager = nullptr;

	std::shared_ptr <Camera>camera = nullptr;
	std::shared_ptr<Player>player = nullptr;

	//debug
	std::vector < std::vector<std::string>> MapCsvPass;

	//objectƒŠƒXƒg
	//std::list<std::shared_ptr<Object>>objects:
	std::list<std::shared_ptr<Object>> liveObjects;

};

