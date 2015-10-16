# -*- Makefile -*-

# You may add -std=c++11
CXXFLAGS= -g `pkg-config --cflags opencv` # -std=c++11 -DUSE_OLD_FFMPEG
LDFLAGS = `pkg-config --libs opencv`

# objects to compile
OBJS = DataManagement/VideoIO.o DataManagement/Pipe.o

# Root rule
all: Makefile Test

# Build test program
Test: $(OBJS) Example.o 
	${CXX} $(OBJS) Example.o -o $@  $(LDFLAGS)

# Rule to build all .o 
%.o: %.cpp %.h
	${CXX} -c -g ${CXXFLAGS} ${CPPFLAGS} -o $@ $<

# cleaning rule
clean:
	rm  -f *.o DataManagement/*.o Test Doc

# Create documentation
doc:
	# Create documentation in the DataManagement subfolder
	cd DataManagement && doxygen Doxyfile
	# Create doc here
	doxygen Doxyfile
