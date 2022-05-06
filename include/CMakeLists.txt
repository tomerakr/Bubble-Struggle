#target_include_directories (${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_sources (${CMAKE_PROJECT_NAME} PRIVATE "GameObject.h"  "Animation.h"  "Ball.h" "Bear.h" "Button.h" 
                                            "Controller.h" "Floor.h" " Macros.h" "Resources.h" "Rope.h"
                                            "Time.h" "Wall.h" "Window.h")