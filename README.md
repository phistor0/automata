# Atomic Cellular Automata 

## About

This is my attempt at a novel cellular automata. It attempts to simulate certain aspects of atomic physics in an attempt to observe life in a simulated environment.

My first commit was on 12 July 2026 and my latest commit was on 22 October 2026.

This project was created by Ravi G. R. Laakso, also known as phistor0. For inquiries, contact me at:
rgrlaakso@gmail.com





## How to Use

Build this project and input your desired grid size, and simulation version. Once your simulation grid has loaded, click on individual grid squares to add "atoms." Use the top row of keys and arrows to modify particle attributes, and use the space bar to start and stop the simulation. Hit CTRL while hovering your cursor on an atom to view its particle attributes. 





## Keybinds

### Outside of Simulation

**Left Click**: Left click on any grid square to add an "atom" to it. 

**Right Click**: Right click on any grid square with an "atom" to remove it.

**Q**: Modify protons of inspected atom.

**W**: Modify neutrons of inspected atom.

**E**: Modify electrons of inspected atom.




### In Modification Mode

**↑**: Increase selected modification.

**↓**: Decrease selected modification. 




### At Any Point

**Left CTRL**: Open inspector on an atom. 

**Space**: Start/Stop simulation.





## About the Code

This project functions through an application loop defined in src/main.cpp. 

SDL Events enter a query which is processed by running each event in the query through the SDL_EventHandler defined in src/sdl_eventhandler.hpp. The SDL_EventHandler communicates with the GridArray (defined in src/gridarray.hpp) to modify two vectors (a 2D vector representing every cell with a 0 or a 1, and a list of cells and their attributes) and with the Window (defined in src/window.hpp) to modify attributes that determine rendering.

The GridArray then calls the Cell (defined in src/cell.hpp) members of the cellIndex vector to update, and then updates the arrayIndex to reflect the positions of the cells from the cellIndex.

Finally, the Window is called to render the scene and update the window surface.




## About the Simulation

Unlike many other cellular automatas, this automata represents each live cell as its own object (an "atom") with a velocity and attributes. More in-line with standard automatas, each atoms's state is directly the result of the states of its neighbors. 

"Attraction" or "repulsion" is determined by the charge of each atom (protons - electrons), and the "strength" of that factor is determined by the cummulative atomic mass (protons + neutrons) of a set of neighbors (or a "molecule"). Mathmatically, the velocity is a difference of the sum of the opposite charge strengths of other atoms and the sum of same charge strengths of other atoms. Then, a modulus is calculated, by adding the difference an atom's transform and all of the other atoms' transforms.

To determine attraction/repulsion, the simulation uses the function, f(v, u) = (2/π) * arctan(v^3/72u), where U is the euclidean distance calculated as √(modX^2 + modY^2). Then, to determine the X and Y components, f is multiplied by modX/(modX + modY) and modY/(modX + modY), respectively.






## THIS PROJECT IS A WORK IN PROGRESS!