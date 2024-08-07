G A M E - Bubble Trouble - [Game Video](https://www.youtube.com/watch?v=2vfWpLdXIw0)
=========================



G A M E - R U L E S
=========================
In Bubble Trouble your goal is to pop all the balls in each level without getting
hit by the balls. In our version we actualized the normal game + survival mode.
Normal: you can either play SOLO or DUO (same PC or online), play along the levels
	and win, when you pop a ball you got a chance of getting a gift, each time you 
	get hit by ball the level will reset and you'll lose 1 life, when the lives
	end the game will be over.

Survival: 1 endless level without any walls (so you can go in either direction 
	for ever) and the balls spawn on you infinitely the game is over when you lose
	all the lives. In this mode you can only play SOLO

Level Creator: you can create your own levels and play them, just click save and
	reload the game and the level will be waiting for you (last one).
	you can choose which balls to put (8 - smallest, 0 - biggest) which direction
	they'll go, choose to add walls or floors.

O B J E C T S
=========================
Ball	- The player needs to shoot ropes at the ball to make it split into 2 smaller balls. 
				The ball disappears if small enough when hit.
				If hits the player the lives decrease. If hit there is a chance for a gift to appear.

Bear	- The object which represents the player. The player can control it, shoot from it and avoid the balls.
				If collided with a ball the lives decrease or transfers back to the menu if 0 lives reached.
				Can collide with gifts which will give the player more lives, power-ups etc.

Rope	- The object the player shoots the balls with. Disappears once hit a ball or tile. Can be frozen in place until
				collided with ball if player acquired the freeze gift.

Tile	- The walls, defines the borders. Balls can't move through them.

Button	- The player will see buttons when in the menu. Will need to press some of them to reach the level creator
				or the survival/normal game-modes. Required to be pressed if one wishes to start the game.

Gift	- Will appear at random when the player hits balls. There are gifts of freeze rope, add time, add additional rope to be shot
				simultaneously by the same player, add lives.

F I L E - D E S C R I P T I O N
=========================
## .h files
Animation.h - accountable for the animation properties in the game.

Ball.h - can create a ball with rigid body for the game or just the shape for level
	creator.

Bar.h - accountable for all the game info, for example: time, lives, score and more.

Bear.h - multiple access functions, inherit from movingObjects.

Board.h - world of the game, contains balls, base and added tiles and gifts.

Button.h - can rotate, change colors, return if pressed.

ContactListener.h - accountable for collision detection.

Controller.h - controls the game, whether will show the game the menu or level creator
	has window member.

GameObject.h - has virtual draw function and pointer to b2Body.

GameScreen.h - accountable for all the game activities: normal or survival game.

Gun.h - has rope member and knows how many can he fire, which abilities he has.

Input.h - virtual class for input in game, either from same PC or from online.

LevelCreator.h - has members of ball and tile to place on the "board" to create a level.

Macros.h - Including all constants used across the program. For example: window and bear size, filter indexes etc.

MenuScreen.h - accountable for menu show: buttons, help etc.

MovingObject.h - a class for moving objects.

OnlineInput.h - reads input from online (LAN) and send it to second player.

PcInput.h - reads input from keyboard.

Resources.h - singleton class thats hold all the resources for the entire game.

Rope.h - rope popper.

StaticObject.h - a class for static objects.

Tile.h - using it as a wall, floor, floating floor or any tile in the game.

Timer.h - time in class.

## .cpp files
Animation.cpp - A class which manages all animations of objects that uses animation in the game, like the bears.
					Based on movement and direction it shows the appropriate sprites.

Ball.cpp - The balls the player needs to destroy. Handles all things related to the balls.
			For example: Destroy itself and spawn 2 smaller balls, movement etc.

Bar.cpp - Handles and draws all UI related objects during the game itself.
			For example: The timer, level number, background, info about the bears etc.

Bear.cpp - Derived from the MovingObject class. Handles all things related to the bear object the player controls.
			For example: Handles different inputs based on the game mode, movement, animation, has a Gun member to 
							manage its ropes and so on.

Board.cpp - Manages all objects related to the game itself, has vectors of gifts, balls, tiles and the box2d world.
				Handles their drawings, builds the level and so on.

Button.cpp - Derived from the RectangleObjects, the class handles and manages itself as a button.
				It detects when it is pressed, when the mouse hovers over it, draws itself etc.

ContactListener.cpp - Derived from the built in base class b2ContactListener. 
						Checks and handles collisions between certain objects in the game. 
						For example: rope with ball, ball with player and so on.

Controller.cpp - Controls the flow of the game. Manages different stages of the entire game flow like the menu, game screen,
					and level creator.

GameObject.cpp - Base class for objects in the game like Button, Moving and Static Objects etc.
					Handles the size, position and texture of the object. In addition has function to draws itself.

GameScreen.cpp - Manages all things related to the objects in the game mode itself.
					Handles sub-managers of the different game modes (normal and survival),
						handles the bears, victory and loss conditions, camera movement, keyboard input, drawing all objects etc.

Gun.cpp - Manages a list of ropes for each bear. Handles their drawings, shot cool-down and their destruction.

LevelCreator.cpp - Handles the creation of a new level based on the imagination of the player.
						The player can: Add balls with different sizes and different starting movement direction,
											add horizontal and vertical walls, erase added objects one by one if the player regrets
											or erase the whole new level and start creating from scratch.
										After carefully planning, the satisfied player can hit the save button to save the level to
											a text file which will be added to the rest of the created/built-in levels which the player
											will be able to play!

MenuScreen.cpp - Manages all things related to the menu. Handles click on buttons, starts the level according to the appropriate button
					like: survival, normal, solo or co-op, or level creation. Can also read input from keyboard and of course draws
					all objects related to the menu like buttons, background etc.
					

MovingObject.cpp - Derived from the RectangleObjects class, this class can move itself across the window with direction as input.

OnlineInput.cpp - Handles internet connection and data received from that connection (For multiplayer through different PCs)

PcInput.cpp - Reads and handles input from the keyboard such as arrows for move direction of player and shooting.

Resources.cpp - A singleton which stores and handles all textures, levels, balls colors and so on for the other
					objects to use.

Rope.cpp - Handles the ropes shot by the guns. Handles its size, movement, destruction and box2d attributes.

Tile.cpp - Derived from the StaticObject class, this class represents all tiles (walls) in the game.
				It handles their destruction, position and size and can detect when mouse is inside them.

Timer.cpp - A class that simulates a timer based on number of seconds given to it when created. Stores how much time is left and
				detects if the time ended.


C O N T A I N E R S
=========================
Vectors - holding the game objects: bears, dummy bear (for survival level), balls, gifts

A L G O R I T H M S
=========================
Endless level: So the level can be "endless", the program calculate the position
	of the player, and swiches between two viwes, and resize them acorrdin to the player position.

K N O W N - B U G
=========================
In the survival mode, if a ball is popped right between the 2 windows (survival move consists of 2 windows right next to each other)
	there is undefined behavior.

Sometimes when a ball collides with rope, 2 smaller balls appear but the original ball that was supposed to be destroyed remains all the same.

Sometimes no collision is detected between the rope and the ceiling, although most of the time it works fine.

When playing online, from each player's perspective the character is on the right side and the other player on the left.

In the survival mode it takes 2 hits from balls so the lives will start to go down (as if we have 5 lives and not 3).


C O M M E N T S
=========================
Survival mode: we created a endles level - you can go right or left forever and 
	always go back to the same place (the level created in a circular mode).
	Bubbles are randomly formed in different places every 7 seconds.

Level creator: every one can create levels easily.
	the level creator have the option to select the ball size, and his initia direction.
	also, the player can set the time limit to the level.

Multiplayer: The player can choose if to play alone or with friend.
	if he decide to play with his friends, he also can choose if to play with two PCs 
	(in the same network) or with the same PS.
	 
Internet connction: If two players wants to play, first, they need to decide who is the host and who is the gust.
	the gust need to enter the IP address of the host.
	the host IP will apeer automaticly after clicking on "HOST" button.
	affter both are connected the game will start.

Graphics: all the graphics created by us, including the spritesheet.

Because of the way box2D is built, it was not possible for us to create a d-tor for the objects,
	but were forced to create a brand new function to fulfill these needs.
	We discussed this problem with the teacher and the advice that was given was to stick with our solution.

In general, we found that the box2D engine has quite an unpredictable behavior that we couldn't put our finger on it.

C O N T R I B U T O R S
=========================
- Tomer Akrish
- Miriam Manolache
- Netanel Bondar

