# SuDokuL
This is a Sudoku game made in C++ and SDL2. It is currently only playable in Windows, but I intend to port it to Gamecube, Wii, Vita, and possibly other systems.

### Features
- Play Sudoku puzzles of Easy, Normal, Hard, or Very Hard difficulty
  - These puzzles are generated on-demand using a built-in algorithm; however, to eliminate computation time on weaker devices, Hard and Very Hard puzzles have been pre-generated.
- Supports both mouse and keyboard controls
- Supports many resolution options ranging from 320x240 to 5120x2160
- Scrolling background with customizable settings (scroll speed, angle, size)
- Includes calm and envigorating MOD music to suit your mood
- Shaded text for a nice, 3D look
- Runs on a potato

### Screenshots
This game was designed for 640x480 (Gamecube resolution) displays, but it is compatible with any resolution, and higher resolutions will utilize more detailed text and support for smaller background tiles.

### Credits
Everything in this game is made by me except for the following assets:

#### Music
- [Nuke of Anarchy - "Wonder Flow"](http://modarchive.org/index.php?request=view_by_moduleid&query=38132) (alternate version can be found [here](http://modarchive.org/index.php?request=view_by_moduleid&query=133262))
- [Okeanos - "Sudoku Padawan"](http://modarchive.org/index.php?request=view_by_moduleid&query=64812)
- [Nuke of Anarchy - "Electroquest"](http://modarchive.org/index.php?request=view_by_moduleid&query=41515)
- [Soundscape - "Main Menu"](http://modarchive.org/index.php?request=view_by_moduleid&query=49158)
- [Okeanos - "Insomnia"](http://modarchive.org/index.php?request=view_by_moduleid&query=45908)
- [Solon - "Ontario"](http://modarchive.org/index.php?request=view_by_moduleid&query=128908)
- [Noiseless - "Addiction"](http://modarchive.org/index.php?request=view_by_moduleid&query=32912)

#### Font
Commodore Pixelized v1.2 by by Devin Cook

#### Sound Effects
[Luke.RUSTLTD](https://opengameart.org/users/lukerustltd)

#### Libraries
- SDL2 2.0.14
- SDL2_image 2.0.5
- SDL2_ttf 2.0.15
- SDL2_mixer 2.0.4
