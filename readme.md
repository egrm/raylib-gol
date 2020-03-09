# Raylib Game of Life

## Features

Shortcuts are QWERTY-based regaldless of the layout.

- hold left mouse button and drag to draw
- hold SPACE to progress through generations
- R to randomize the board
- C to clean the board

## Run a release binary
[Download](https://github.com/egrm/raylib-gol/releases) latest release binary.


Give it executable rights & run:
```bash
chmod +x ./raylib-gol && ./raylib-gol
```

## Build with CMake
1. Make sure you have CMake

macOS:
```bash
brew install cmake
```

Ubuntu:
```bash
sudo apt-get -y install
```

2. Clone the repo
```bash
git clone https://github.com/egrm/raylib-gol.git
```

3. Build & Run
```bash
mkdir build # Create a build directory
cd build && cmake .. # Build from that directory so the build files are in one place
cmake --build . # Actually build the project
./raylib-gol
```

In case you have issues or need to build using something else, consult
[this guide](https://github.com/raysan5/raylib/wiki/Working-with-CMake)
