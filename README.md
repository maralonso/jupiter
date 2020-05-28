# Jupiter  
[![Build Status](https://travis-ci.org/maralonso/jupiter.svg?branch=master)](https://travis-ci.org/maralonso/jupiter)  
[![codecov](https://codecov.io/gh/maralonso/jupiter/branch/master/graph/badge.svg)](https://codecov.io/gh/maralonso/jupiter)  


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
    * **fics**: Script and files to play online
    * config: Engine configuration file.    

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


## Play online on FICS

You can find jupiter on FICS as `JupiterCallisto`, so go and play some games against him.

Also, you can connect jupiter, or other chess engine using `fics/callipsto.py` script.
`fics/callipsto.py` will connect to FICS as guest, and plays random games.
Games are saved as .pgn files.


```
fics/callisto.py --help
usage: callisto.py [-h] [-u USER] [-p PASSWORD] [-e ENGINE]

optional arguments:
  -h, --help            show this help message and exit
  -u USER, --user USER  FICS username
  -p PASSWORD, --password PASSWORD
                        FICS password
  -e ENGINE, --engine ENGINE
                        Engine binary file
```
