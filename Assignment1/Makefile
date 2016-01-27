## -*- Makefile -*-
##
## User: peterpan
## Time: Jan 26, 2016 2:26:24 PM
## Makefile created by Oracle Solaris Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CCC = g++
CXX = g++
BASICOPTS = -g
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
CCADMIN = 


# Define the target directories.
TARGETDIR_inch_to_cm=./bin


all: $(TARGETDIR_inch_to_cm)/inch_to_cm

## Target: inch_to_cm
CPPFLAGS_inch_to_cm = \
	-Iinch_to_cm.cpp
OBJS_inch_to_cm =  \
	$(TARGETDIR_inch_to_cm)/inch_to_cm.o
USERLIBS_inch_to_cm = $(SYSLIBS_inch_to_cm) 
DEPLIBS_inch_to_cm =  
LDLIBS_inch_to_cm = $(USERLIBS_inch_to_cm)


# Link or archive
$(TARGETDIR_inch_to_cm)/inch_to_cm: $(TARGETDIR_inch_to_cm) $(OBJS_inch_to_cm) $(DEPLIBS_inch_to_cm)
	$(LINK.cc) $(CCFLAGS_inch_to_cm) $(CPPFLAGS_inch_to_cm) -o $@ $(OBJS_inch_to_cm) $(LDLIBS_inch_to_cm)


# Compile source files into .o files
$(TARGETDIR_inch_to_cm)/inch_to_cm.o: $(TARGETDIR_inch_to_cm) inch_to_cm.cpp
	$(COMPILE.cc) $(CCFLAGS_inch_to_cm) $(CPPFLAGS_inch_to_cm) -o $@ inch_to_cm.cpp



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_inch_to_cm)/inch_to_cm \
		$(TARGETDIR_inch_to_cm)/inch_to_cm.o
	$(CCADMIN)
	rm -f -r $(TARGETDIR_inch_to_cm)


# Create the target directory (if needed)
$(TARGETDIR_inch_to_cm):
	mkdir -p $(TARGETDIR_inch_to_cm)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-Linux

