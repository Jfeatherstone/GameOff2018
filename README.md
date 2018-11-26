# GameOff2018
My project for the Github Game Jam 2018

The idea for now is a 2D platformer where the player can switch between two characters which will have different abilities, both of which will be need to be used to complete levels.

The game is being written in C++17, using SFML as the framework for basic window/sound/etc. functions.

All art will be original and created on my piskel account linked below!

[Piskel link!](https://www.piskelapp.com/user/4977014434955264)

A sample of movement!
![movement](https://raw.githubusercontent.com/Jfeatherstone/GameOff2018/master/screenshots/level_transition.gif)


# What we have so far:
 - A 3 dimensional linked list to organize our levels (NLLinkedList)

 - A Level parser that can read in data from level .txt files (LoadLevel & levels/)

 - Lateral movement and jumping/flying for both characters

 - Some *very* basic sprites

 - A dynamic camera view based on the level size

 - An updating health bar

 - The ability to move between levels

 - Reasonable collisions
