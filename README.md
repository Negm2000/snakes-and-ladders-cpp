# Snakes & Ladders board editor (C++)

The graphics and input layer of a Snakes & Ladders game with a built-in board editor, in C++ on Windows. Phase 1 of the team project for *Programming Techniques* at Cairo University (spring 2023), built by Karim Negm, Amr Ashraf and Mohamed Alhabashi on the course's starter skeleton and the CMUgraphics library.

This phase covers everything the player sees and clicks. The game logic was the second phase and is not in this repository.

## What is here

- **`Output`**: draws the window. A toolbar that switches between design mode (add ladder, snake or card; copy, cut, paste and delete objects; save and open a grid) and play mode (new game, roll dice, enter a dice value), the numbered grid, cells with cards, players, ladders, snakes, and a status bar for messages.
- **`Input`**: turns mouse clicks into actions. It works out which toolbar icon or grid cell was clicked and reads validated integers and strings typed by the user.
- **`CellPosition`**: converts between a cell number and its row and column on the board, with range checks, in both directions.
- **`TestCode.cpp`**: a click-through demo that exercises each drawing and input function in turn.

My part: the toolbar and action handling in `Input` and `Output`, the cell-number-to-position conversion, and the snake and ladder drawing.

## Build

Open `PT-Project.sln` in Visual Studio on Windows and run. The toolbar icons are loaded from `images/` relative to the working directory.

`CMUgraphicsLib/` is the third-party graphics library supplied with the course.
