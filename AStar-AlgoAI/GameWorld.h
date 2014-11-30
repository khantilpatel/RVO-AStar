#pragma once
#include "Node.h"
#include "Player.h"
#include "Agent.h"
#include "ROVNavigationSystem.h"
const int _GRID_RESOLUTION_X_AXIS = 25;
const int _GRID_RESOLUTION_Y_AXIS = 15;

extern ds::Node m_map[_GRID_RESOLUTION_X_AXIS][_GRID_RESOLUTION_Y_AXIS] ;

extern std::vector<Agent*> m_agents;

extern std::vector<ds::Node> collisionNodes ; 

extern std::vector<ds::Node> coverNodes;
extern 	std::vector<std::vector<int> > agent_hashtable;

class GameWorld
{


public:
	GameWorld(void);

	const int static _WINDOW_WIDTH = 640;
	const int static _WINDOW_HEIGHT = 480;

	glm::vec4 _COLOR_WALKABLE_NODE;
	glm::vec4 _COLOR_COLLISON_NODE ;
	glm::vec4 _COLOR_TARGET_NODE ;
	glm::vec4 _COLOR_START_NODE ;


	void GameWorld::WorldInit();

	static int* getGameMap(); // returns game map variable m_map

	ds::CubeGeomerty* getPlayerCurrentLocation();
	
	void createGrid();//ds::Node nodes[_GRID_RESOLUTION_X_AXIS][_GRID_RESOLUTION_Y_AXIS], std::vector<Node>);

	void AIupdate();

	void renderGame();

	void renderGameEnviornment();

	void updatePF();

	void setPlayer(Player*);

	Player* m_player;

	float delta_time;

	//std::vector<std::vector<int> > agent_hashtable;
	
	//void setAgents(vector<Agent*>);

private:	
	


	



};

