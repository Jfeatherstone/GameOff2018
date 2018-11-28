# GameOff2018
My project for the Github Game Jam 2018

The idea for now is a 2D platformer where the player can switch between two characters which will have different abilities, both of which will be need to be used to complete levels.

The game is being written in C++17, using SFML as the framework for basic window/sound/etc. functions.

All art will be original and created on my piskel account linked below!

[Piskel link!](https://www.piskelapp.com/user/4977014434955264)

A sample of movement!
![movement](https://raw.githubusercontent.com/Jfeatherstone/GameOff2018/master/screenshots/movement.gif)


# What we have so far:
 - A 3 dimensional linked list to organize our levels (NLLinkedList)

 - A Level parser that can read in data from level .txt files (LoadLevel & levels/)

 - Lateral movement and jumping/flying for both characters

 - Some basic sprites

 - A dynamic camera view based on the level size

 - An updating health bar

 - The ability to move between levels

 - Reasonable collisions

 - Pause menu

# Fonts used:

[Komikap](https://www.dafont.com/komika-parch.font)

[Pixellari](https://www.dafont.com/pixellari.font)


# Controls:

W - Jump

A + D - Left and right movement

E - Switch characters

Esc - Pause


# Running the game

Linux:

  - Download all of the files from the repo
  - cd to the directory and run ./Main

Windows:

  - Working on it...
  - For now, if you can compile the source yourself, that should work, just be
  sure to include sfml as well as c++ filesystem
