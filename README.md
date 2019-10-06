# C++ Basics: Rendering Fractals

## Get the Code and Start Developing

    mkdir cpp-basics
    cd cpp-basics
    git clone https://github.com/lyrahgames/cpp-basics-fractal.git fractal
    cd fractal

**Fast Building:**
In-source build without persistent configuration:
    
    # Build the executable with ad-hoc configuration and compiler flags.
    b config.cxx=clang++ "config.cxx.coptions=-O3 -march=native"
    # Run the application.
    fractal/fractal
    # Clean build output.
    b clean

**Persistent Building:**
Out-of-source build with persistent configuration:

    # Create the persistent configuration out-of-source and set appropiate compiler flags.
    bdep init -C @gcc cc config.cxx=g++ "config.cxx.coptions=-O3 -march=native"
    # Build the executable.
    b
    # Run the executable.
    fractal/fractal
    # Clean build output.
    b clean

From here on, open your editor inside the directory and look at the code and start with further developments.


## Get the Package and Install the Application

    # Create persistent configuration for all packages in the new directory
    # 'cpp-basics-packages' with appropriate compiler flags and installation options.
    bpkg create -d cpp-basics-packages cc \
        config.cxx=clang++ \
        "config.cxx.coptions=-O3 -march=native" \
        config.install.root=/usr/local \
        config.install.sudo=sudo
    # Download and build this packages inside the configuration folder.
    bpkg build fractal@https://github.com/lyrahgames/cpp-basics-fractal.git#master
    # Install the built executable with its documentation.
    bpkg install fractal
    # Run the application in any directory.
    fractal
    # Uninstall the executable while in 'cpp-basics-packages'.
    bpkg uninstall fractal

## Using the Executable
- Left Mouse Button: Move the origin.
- Right Mouse Button: Change complex coefficient.
- Mouse Wheel: Zoom in and out.
- Escape: Close the window.
- M: Draw Mandelbrot set.
- J: Draw Julia set.
- C: Draw circle.