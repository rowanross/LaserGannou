#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := note_player_gpio.cpp rtttl_player.cpp

# header files in this project
HEADERS += bieperControl.h
HEADERS += ButtonListener.h
HEADERS += display.h
HEADERS += gameParametersControl.h
HEADERS += initGameControl.h
HEADERS += note.hpp
HEADERS += note_player.hpp
HEADERS += note_player_gpio.hpp
HEADERS += receiveIRMessageControl.h
HEADERS += rtttl_player.hpp
HEADERS += runGameControl.h
HEADERS += sendIRMessageControl.h
HEADERS += transferHitControl.hpp
HEADERS += struct.h

# other places to look for files for this project
SEARCH  := 

# set RELATIVE to the next higher directory and defer to the Makefile.due
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
