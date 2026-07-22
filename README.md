# Atomic Cellular Automata 

## About

This is my attempt at a novel cellular automata. It attempts to simulate certain aspects of atomic physics in an attempt to observe life in a simulated environment.

My first commit was on 12 July 2026 and my latest commit was on 21 July 2026.

This project was created by Ravi G. R. Laakso, also known as phistor0. For inquiries, contact me at:
rgrlaakso@gmail.com





## How to Use

Build this project and input your desired grid size, and simulation version. Once your simulation grid has loaded, click on individual grid squares to add "atoms." Use the top row of keys to modify particle attributes, and use the space bar to start and stop the simulation. Right click on a particle to view its attributes. 





## Keybinds (IN PROGRESS)

### Outside of Simulation

**Left Click**: Left click on any grid square to add an "atom" to it. 

**Right Click**: Right click on any grid square with an "atom" to remove it.

**Q**: Modify protons of inspected atom.

**W**: Modify neutrons of inspected atom.

**E**: Modify electrons of inspected atom.

**A**: Modify x-component of velocity factor of inspected atom.

**S**: Modify y-component of velocity factor of inspected atom.




### In Modification Mode

**↑**: Increase selected modification.

**↓**: Decrease selected modification. 

**Esc**: Exit modification mode without saving changes.

**Enter**: Save modifications and exit modification mode.



### At Any Point

**Left CTRL**: Open inspector on an atom. 

**Space**: Start/Stop simulation.





## About the Code

This project functions through an application loop defined in src/main.cpp. 

SDL Events enter a query which is processed by running each event in the query through the SDL_EventHandler defined in src/sdl_eventhandler.hpp. The SDL_EventHandler communicates with the GridArray (defined in src/gridarray.hpp) to modify two vectors (a 2D vector representing every cell with a 0 or a 1, and a list of cells and their attributes) and with the Window (defined in src/window.hpp) to modify attributes that determine rendering (for example, the inspector).

The GridArray then calls the Cell (defined in src/cell.hpp) members of the cellIndex vector, and then the arrayIndex to reflect the positions of the cells from the cellIndex.

Finally, the Window is called to render the scene and update the window surface.




## About the Simulation

Unlike many other cellular automatas, this automata represents each live cell as its own object (an "atom") with a velocity and attributes. More in-line with standard automatas, each atoms's state is directly the result of the states of its neighbors. 

"Attraction" or "repulsion" is determined by the charge of each atom (protons - electrons), and the "strength" of that factor is determined by the cummulative atomic mass (protons + neutrons) of a set of neighbors (or a "molecule").

Velocity is represented as a factor---the "velocity factor" is the number of ticks it takes for an atom to move one square. Therefore, 1/v is the number of cell each atom moves per tick (although obviously atoms are confined to a cell until their "tangible" position, or their theoretical position rounded down, increases).






## THIS PROJECT IS A WORK IN PROGRESS!