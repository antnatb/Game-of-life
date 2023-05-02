# Game-of-life

This is a modified version of Conway's Game of Life, a cellular automaton that simulates the growth and decay of cells.

The game is played on a 2D square grid; each square (or "cell") on the grid can be either alive (white) or dead (black), and cells evolve
according to the state of their eight neighbors, which are the cells that are orizontally, vertically and diagonally adjacent.
In particular, the three simple rules of the Game are the following:
- Any live cell with two or three live neighbours survives.
- Any dead cell with three live neighbours becomes a live cell.
- All other live cells die in the next generation. Similarly, all other dead cells stay dead.
The initial configuration is random with a 0.1 chance for each cell to be alive.
The evolution of the system only depends on the initial state of the grid, so the game literally plays itself.
In this version of the Game, the grid "wraps around", which means that the left and right border and the top and bottom border are actually
adjacent with each other.
This version features a standard mode (basically the traditional Game of Life) and currently two modifiers:

- The Age Modifier: each cell has its age; a newborn cell has its age set to 0; when a cell survives a generation,
   it ages (and slightly changes its color). Cells age up to the max age of 15, after which it dies. The rules of the Game stay the same.

- The Color Modifier: each cell has a random initial color; when a new cell is born, its color is defined as the "average" color of
   the 3 alive cells that caused its birth. The rules of the Game stay the same.

This project was written in C++ using the SFML graphic library.
