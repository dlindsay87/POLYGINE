This project is a bare-bones c++ game engine using SDL2 and OpenGL. It aims to be an open source asset that allows for game development with minimal abstraction. 

As of June 21, 2024 we can move around the cabin! The horizontal and vertical planes have shifted and your mouse controls the angle at which your "character" moves. The floating white ball is the foundation of a lighting system. Input and update methods have been altered.

The program also includes dedicated timing, shading, object, and mesh classes. You can enable or disable vsync (press v), progress the gamestate (press space), resize the window or change background color (press any key while gamestate is in PLAY).

You can also create 3D cube spheres or 2D polygons by pressing return. These can be moved around (arrows or wasd), or scaled (+ or -). Adjust the shape by pressing 1-9 on your number pad. Press z or esc to quit. 0 returns your active object to the center and delete clears all objects.

Please contact me with any feedback or advice, especially regarding platform comptability. I have much to learn, and there's much, much more to come. Thanks.

-Dylan