target_include_directories (${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_sources (${CMAKE_PROJECT_NAME} PRIVATE "Animation.h"
											  "Ball.h"
											  "Bear.h"
											  "Board.h"
											  "Button.h"
											  "Controller.h"
											  "GameObject.h"
											  "LevelCreator.h"
											  "Macros.h"
											  "MovingObject.h"
											  "Resources.h"
											  "Rope.h"
											  "StaticObject.h"
											  "Tile.h"
											  "Timer.h"
											  "Window.h"
												)