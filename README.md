
Project 2

Requirements Implemented:
1.1-  yes,  see blow Grammer Define section
1.2-  yes,  BRANCH_ANGLE, RECURSION_DEPTH, TALLNESS, COLOR
1.3 - yes,  LEAF_SIZE: each sphere represent a leaf , the size can be adjusted ; BRANCH_WIDTH: cylinder represent plant trunk, its widtch can be adjusted
1.4-  yes,  use Cylinder and Sphere
2.1-  yes : see Flock.cpp, Boid.h, plant.cpp for detail implentation
2.2-  yes : Boid.h, it defines 4 attributes(position,velocity,acceleration) and a constuctor (initiate attributes); use sphere to represent boid
2.3-  yes : Flock.cpp , it implements 3 rules(seperation, cohension and align) and methods (add Boid, update Boid, bordering boids, limit boid speed, drive boids fly to some place etc) ;
2.4 - yes : ORIENTATION
2.5 - yes : PECEP_DISTANCE
2.6 - yes : MIN_DISTANCE_ADJUST
2.7 - yes : Flock.cpp, limit_velocity method limits speed to 0.2
2.8 - yes : Flock.cpp, get_target method set the target, boids fly towards it. By design boids fly around the tree in a circle, so target get updated every draw with a small angle
2.9 - yes : Flock.cpp, borders method sets up border area
2.10 -yes : once animiation is checked, boids will fly around the tree



[Grammer Define]

variables : 0, 1
constants: "[", "]","{","}","^"
axiom  : 0
rules  : (1 → 10), (0 → 1[0]0^{0}0^1)
1st recursion: 1[0]0^{0}0^1
2nd recursion: 10[1[0]0^{0}0^1]1[0]0^{0}0^1^{1[0]0^{0}0^1}1[0]0^{0}0^1^10


0: draw a cylinder segment(branch) ending in a sphere(leaf)
1: draw a cylinder segment(branch)

^: pop current matrix

[: push position and angle, turn left 45 degrees
]: pop position and angle, turn right 45 degrees

{: push position and angle, turn up 45 degrees
}: pop position and angle, turn down 45 degrees

