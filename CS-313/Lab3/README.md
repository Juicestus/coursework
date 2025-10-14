# The Task
In this assignment you'll create a parallel runtime library for cooperative multitasking. Note that it is __not__ required that you use multiple processors for this runtime. All that we require is a runtime which can support concurrent execution. The starter code directory contains the following files:
## Directory Structure
* `main.c`: This file showcases the how to use the API of the library that you'll create. You are __not__ allowed to modify this file.
* `Makefile`: This is the Makefile which you'll use to compile your code. You are allowed to modify this file, but you most likely won't have to.
* `threading.c`: This the file where you are expected to implement the library. Please fill in the function bodies which are indicated by `TODO`s.
* `threading.h`: This is the header file for the library which would be used by other applications which want to use your library. You are __only__ allowed to add code in this file. You are __not__ allowed to remove and/or change the function declarations mentioned in this file. This file will also give you a brief description of what each function is expected to do.
* `threading_data.c`: This file holds all the variables associated with your library. You can modify this file if you so desire. Please note that if you want the variables defined in this file to be accessible in `threading.c`, you'll have to define them at the global scope and add corresponding `extern` declarations for them in the header.

## API Details
* `void t_init()`: This function initializes various variables which you may or may not be using in your library.
* `int32_t t_create(fptr foo, int32_t arg1, int32_t arg2)`: This function is used to spawn a worker. The worker is supposed to execute the function function `foo` by passing it `arg1` and `arg2`.
* `int32_t t_yield()`: Since this library implements cooperative multitasking, each worker is expected to yield the control after it finishes it's execution. The workers call this function to yield the control.
* `void t_finish()`: This function is called by a worker to indicate that it has completed its work.

# How to Compile
To compile the code, simply execute `make` from this directory. This will created two files: the shared object file for your threading library, `libthreading.so`, and the executable for the code which uses this library, `main`.

# How to Clean the Build
To clean the built files, simply run `make clean`. This will delete both `libthreading.so` and `main` from the directory.

# How to Run
To run the code, you can simply execute the `main` file by running `./main` from this directory.
