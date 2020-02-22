## Description
This is my program created for pset3(last), cs50x. It tries to recover accidentally deleted jpgs files that are yet remained in the memory. 
User would be prompted to input a "filename" that contains bytes of jpgs, and then the program would iterate through the file, searching for existing jpgs, separating the jpgs by inputting them into newly created files until the end of the file.

Two examples of recoveries from the example raw file "card.raw" that contains all the memories, "000.jpg" and "001.jpg", are shown to demonstrate the effect.

## Usage
```python
$ make recover
$ ./recover file # file (.raw) that yet contains memories of deleted jpgs
```

## What I have learned
* Allocating, using, and freeing memories using dynamic memory allocation
* Manipulation (copying, creating) of jpg files
* Tracing of file cursor
