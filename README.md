This project is a bare-bones c++ game engine using SDL2 and OpenGL. It aims to be an open source asset that allows for game development with minimal abstraction. 

As of July 7, 2024 we have a point lighting sytem! We got all sorts of colored lights and responsive object shading.

The program also includes dedicated timing, input, shading, object, camera, and mesh classes. You can enable or disable vsync (press v), progress the gamestate (press space), zoom with the mouse wheel (and by pressing o) resize the window or change background color (press any key while gamestate is in PLAY).

You can also create 3D cube spheres or 2D polygons by pressing return. These can be moved around (arrows or wasd), or scaled (+ or -). Adjust the shape by pressing 1-9 on your number pad. 0 returns your active object to the center and delete clears all objects and rearranges the lights. Press z or esc to quit.

A current bug is that the mouse will remain visible when it shouldn't and it seems it depends on the previous run of the game. Toggling the gamestate a few times (with space) seems to get it right, but it's annoying. Next step will probably be having a more dynamic and directional lighting system. Maybe adding textures. Maybe physics. Stay tuned!

Please contact me with any feedback or advice, especially regarding platform comptability. I have much to learn, and there's much, much more to come. Thanks.

-Dylan