# Points

This is my first try implementing an evolutive algorithm, this has only education purpose.

## Problem
in a rectangle of `m x n` a point is put randomly on any cell, the point will try to move in any direction (top, left, right, bottom) while the point doesn't hit a wall can continue. 

I defined a  population of points that represents the number of points, and repeat the same process described above with each one. after that picked the points with more moves and then reproduce between them and repeat the same process depending on the `iterations` defined on [`main.cpp:127`](https://github.com/granactate/points/blob/master/main.cpp#L127)

#### Requirements

I'm not a  C++ developer then I'm not sure if that code is supported to be executed in other operative systems differents from Ubuntu additionally that is beside the scope of this exercise.

to execute this code you need to have the `g++` should be defined such as an environment variable and you should have the `c++11` version configured, have nvm installed.

if you have all the configuration to execute the C++ code you can  execute the script `script.sh` using
```
sh script.sh
```

##### Backup Option
> in the case that you can't execute the C++ code you can download the JSON generations on this [link](https://drive.google.com/uc?id=1zLmsp6fTHCY2o0B_PzZfC4Gt1SLiXV2c&export=download) and uncompress the zip inside `outputs` folder

if everything is ok you should see in the console a counter telling to you the Iteration number and if is reproducing or sorting the population the counter should arrive until the number defined on [`main.cpp:127`](https://github.com/granactate/points/blob/dfa7c1fecdd7a80276b366f1d02387da844bb3c5/main.cpp#L127) after to that in the folder  `./outputs` should exist a JSON file by each one generation.

```
cd node_server/
nvm use
npm install
npm run build
npm start
```

if everything is ok then the server should be running in the URL: `http://localhost:8080` go to the browser in that URL and, you can start the preview by clicking the play button then in the matrix will appear a gray point showing the moves starting with the better parents that produced the best point in the last generation in the browser's console you can check the log of the points those finished the presentation.

usually, the initial points will take short time to finish the animation but are possible that the time to present the animation increase more with each point, you have to reload the page to stop the execution, if you can set the initial step only to see a segment of the population, for example, setting the input such as 60 the animation will start with that generation.

---
# Pending tasks
 * _include validation to penalize points that repeat a lot of time the same cells_
 * _include in the front-end a shadow to have a reference of cells previous visited by a point_
 * _split the movements in twice chromosomes to improve the reproduction process_
 *_include walls inside the matrix to create a labyrinth_