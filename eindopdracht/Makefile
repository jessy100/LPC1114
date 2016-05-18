#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2015
#
# This file is in the public domain.
#
#############################################################################

# Specify target chip or board or system
TARGET     := lpc1114fn28

# Specify the location of the bmptk library
BMPTK      := ../../../..

# Specify project files (other than $(PROJECT).cpp) (if any)
SOURCES    := sw-uart.c timer.c lcd5510.c
HEADERS    := sw-uart.h timer.h pins.h sr-04.h lcd5510.h servo.h

# Specify directories, other than the current, that contain sources
SEARCH     := ../lib

# The Makefile.inc does all the work
include $(BMPTK)/Makefile.inc
