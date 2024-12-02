# Cub3d

## Quick description
Small-scale replication of DOOM/wolfstein focusing in ray-casting.
![Gameplay Demo](./cub3d.gif)


## Usage
1. Run `make` to compile the files;
2. Initialize the program with ```./cub3D <map_path>.cub```
3. Use `W` to move forward;
4. Use `S` to move back;
5. Use `D` to move to the right;
6. Use `A` to move to the left;
7. Use `RIGHT ARROW` to turn the angle to the right;
8. Use `LEFT ARROW` to turn the angle to the left;
9. Have fun!

## Raycasting
Raycasting is a computational technique used to determine the intersection of rays (lines extending infinitely in one direction) with objects in a scene, often employed in graphics, simulations, and collision detection. The method involves tracing a ray from a source point, usually defined by an origin **O** and a direction vector **D**, and checking if it intersects any objects using parametric equations. For a ray, the equation is:

`R(t) = O + t * D`

where `t ≥ 0` is a scalar defining points along the ray. By solving for t in geometric equations representing objects (e.g., planes, spheres), raycasting identifies intersection points, if any exist. Efficient algorithms optimize these checks to handle complex scenes quickly, making raycasting foundational in rendering and physics engines.



## Result
- Status: <span style="color:green">Complete</span>
- Result: <span style="color:green">100%</span>

## Contact
Felipe Dessoy
- 42-email: fdessoy-@student.hive.fi
- 42-profile: [https://profile.intra.42.fr/users/fdessoy-](https://profile.intra.42.fr/users/fdessoy-)

Alexandra Raveala
- 42-email: araveala@student.hive.fi
- 42-profile: [https://profile.intra.42.fr/users/araveala](https://profile.intra.42.fr/users/araveala)
