# Jupiter

                            = =
               ........  =    =
             ............   =
            ..............=
            .......... =..
          = ........=.....
        =    ...=........
       =     = ........
       =  =     \..../
                ------
                 |  |
                 |  |
                 |  |
                 |  |
                /    \
              (________)        JUPITER CHESS
   ----------------------------------------------
   
Jupiter is an UCI-compatible chess engine for Linux.

You can use it with any User Interface that support UCI protocol, like:   
    - pychess (http://www.pychess.org/)     
    - scid    (http://scid.sourceforge.net/) 

## Files
    * **engine**: Engine source files
    * **tests**: Engine tests source files
    * config: Engine configuration file.    

## Dependencies
OPENMP needs to be installed to use parallelism

As root, run:
* apt-get install libgomp1

## Build and run engine

* make -C engine/
* engine/jupiter

## Build and run tests

* make -C tests/
* tests/jupitests

## Configuration File
You can edit this file to change some options.

### Logging Level
Log level can be DEBUG, INFO or ERROR. It's set to INFO by default.

`LOG_LEVEL = INFO`

### Logging File
By default the engine will log to `./jupiter.log`

`LOG_FILE = jupiter.log`

