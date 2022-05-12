target_include_directories (${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_sources (${CMAKE_PROJECT_NAME} PRIVATE "Animation.h"
											  "Ball.h"
											  "Bear.h"
											  "Button.h"
											  "Controller.h"
											  "Tile.h"
											  "GameObject.h"
											  "Macros.h"
											  "LevelCreator.h"
											  "Board.h"
											  "MovingObject.h"
											  "Resources.h"
											  "Rope.h"
											  "StaticObject.h"
											  "Timer.h"
											  "Window.h"
												)