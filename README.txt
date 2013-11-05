Project 2: Ray Tracer

Steven Hewitt: cs184-eu  (submitted here)
Huiming Han: cs184-dc

Platform: Ubuntu




Website: http://www-inst.eecs.berkeley.edu/~cs184-dc/as2.html

To run code, run make, then ./scene with the correct args.

First arg: input file path in the format specified by <http://inst.eecs.berkeley.edu/~cs184/fa12/assignments/hw5.pdf>.  (But without vertexnormal nor attenuation implementations).

Then any order of:

-screen //will render output image to the screen similar to AS1
-file   //will render to output file called img.png.  If it already exists, it will replace img.png file without asking.







Extra features implemented:

Anti-aliasing:
	To use this, go into the input file and add [aa depth jitter] (ex/ aa 4.0 0.3) to any line.
	depth in range [1.0, and up]:
		How many more rays per pixel squared.  So if 4.0, it will take 16 rays for each 1 ray without aa.  Note: This will take 16 times longer.
	jitter in range [0.0, and up]:
		strength of randomized offset for each ray.  Recommended strength: 0.1 to 1.  If you have a lot of aa, then 
	







Scenes used:



image-01: command "./scene demo/input-01.test -screen -file"
This is a modification of scene 2 where we use diffuse and specular light and anti-aliasing.  Not super interesting, although it demonstrates a lot of basic features for a ray-tracer, such as shadowing, and 2 primitives, triangles and spheres with Phong shading.
time: 3-5 minutes

image-02:  command "./scene demo/input-02.test -screen -file"
This is a modification of scene 4.  Here, each component of light is highlighted.  Ambient/emission is in red, Diffuse is in green, and Specular is in blue.  It also shows how rotation and scaling of sheres into ellipsoids produces the expected interaction with light.
time: 4-6 minutes

image-03: command "./scene demo/input-03.test -screen -file"
This is scene 6 re-rendering with anti-aliasing of depth 4 (16 rays per 1 pixel).  It re-iterates features from above, but also shows rotation on triangles and specular reflection in an actual room-like scene.
time: 4-6 minutes

image-04: command "./scene demo/input-04.test -screen -file"
This is just the 1000 spheres rendering with anti-aliasing.  Unfortunately, we did not have time to implement acceleration structures for this project, so it takes a while to render with anti-aliasing.
time: 2 hours

image-05: command "./scene demo/input-05.test -screen -file"
This is an abstract scene that demonstrates arbitary polygonal shapes can be represented.  It's abstract art.
time: 4-6 minutes





