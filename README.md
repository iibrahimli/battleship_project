[![Build Status](https://travis-ci.com/iibrahimli/battleship_project.svg?branch=master)](https://travis-ci.com/iibrahimli/battleship_project)

# Battleship project

The traditional Battleship game developed in C++ with terminal interface.


## Getting Started

Go to a folder you want the project to be in your file system and type the following in your terminal

``` bash
git clone https://github.com/iibrahimli/battleship_project.git
```

Then, install dependencies with:

``` bash
sudo bash install_dependencies.sh
```

Or download as archive an unzip in a directory of your choice.
Enter the downloaded folder and create a build folder with the following commands

``` bash
mkdir build
cd build
```

Compile the project with:

``` bash
cmake ..
cd ..
make
```

This will create battleship and tests executables in 'bin' folder and libbs.a static library in 'lib' folder

## Running the Game
Game can be executed with the following command from the `build` directory:

``` bash
./bin/battleship
```

In the beginnning the user is asked to enter a name. Then the user will add ships of different sizes ( 2-5 ) to the grid.

## Running the tests

This repository contains also the unit tests written in CPPUnit unit testing framework. In order to make use of these tests you have to install libcppunit-dev library.

```bash
sudo apt-get install libcppunit-dev
```

Tests can be run with the following command from `build`:

``` bash
./bin/tests
```

or

``` bash
make test
```

or 

``` bash
ctest .
```

## Authors

* **Imran Ibrahimli** - [iibrahimli](https://github.com/iibrahimli)
* **Ughur Aghakishiyev** - [Theagh](https://github.com/theagh)
* **Javid Huseynov** - [cavid990](https://github.com/cavid990)

## Screenshots

User name input and difficulty selection:

![greet](https://raw.githubusercontent.com/iibrahimli/battleship_project/master/diff_select.png)

Ship placement phase:

![ingame1](https://raw.githubusercontent.com/iibrahimli/battleship_project/master/ingame1.png)

Shooting phase:

![ingame2](https://raw.githubusercontent.com/iibrahimli/battleship_project/master/ingame2.png)
