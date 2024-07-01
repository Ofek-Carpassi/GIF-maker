# Magshimim Movie Maker

A simple, command-line video editing tool for creating and editing video projects.

## Features

- Create new video projects
- Load existing projects
- Add or remove frames
- Save projects for future editing

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection)

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/Ofek-Carpassi/GIF-maker.git

2. Navigate to the project directory:
    ```sh
    cd GIF-maker

3. Compile the project:
    ```sh
    gcc -o GIFMaker source/main.c source/creatingProject.c source/loadingProject.c source/functions.c source/video.c

4. Run the project:
    ```sh
    ./GIFMaker

## Project Structure

- `source/main.c`: Main program logic
- `source/creatingProject.c`: The main function for the project creation process
- `source/loadingProject.c`: Functions for loading existing projects
- `source/functions.c`: Utility functions
- `source/video.c`: Video manipulation functions

## Authors

- **Ofek Carpassi** - *Project Creator* - [Ofek-Carpassi](https://github.com/Ofek-Carpassi)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.