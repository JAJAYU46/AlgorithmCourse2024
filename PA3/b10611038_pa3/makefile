# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
# CFLAGS = -g
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2
CFLAGS += $(DBGFLAGS)

all	: bin/mps   #the default 的時候是去build  bin/NTU_sort
	@echo -n ""

# optimized version
#bin/NTU_sort 那個final executable file
bin/mps	: main_opt.o
			$(CC) $(OPTFLAGS) main_opt.o -o bin/cb
#			$(CC) $(OPTFLAGS) main_opt.o -o bin/cb
# -o bin/NTU_sort: 要這個executable在bin file中叫的名字(executable name)

#main_opt.o is the compiled object file from src/main.cpp
main_opt.o 	   	: src/main.cpp
			$(CC) $(CFLAGS)	 $< -o $@ 
#			$(CC) $(CFLAGS)	 $< -o $@ 
# 			$(CC) $(CFLAGS)  $< -Ilib -o $@ 
#$(CC): The compiler, g++ in this case.
#$(CFLAGS): Compilation flags, here set to -c, which compiles the source file into an object file without linking
#$<: 就是指上面這個executable的第一個項src/main.cpp， The first prerequisite in the rule. In this context, it represents the source file being compiled (e.g., src/main.cpp or src/sort_tool.cpp).
#-Ilib: Specifies the lib directory as an additional include path for header files. This allows the compiler to locate header files (e.g., lib/tm_usage.h) when compiling.
#-o $@: 表那個target "main_opt.o"，Specifies the output file name. $@ represents the target of the rule, typically the name of the object file to be generated (e.g., main_opt.o or sort_tool_opt.o).
# ///////////////////////////////////////////////////////////////////////////
# maxPlanarSubset.o	: src/maxPlanarSubset.cpp # src/sort_tool.h
# 			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@ 
# sort_tool.o	: src/sort_tool.cpp src/sort_tool.h # src/sort_tool.h
# 			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@ 
# ///////////////////////////////////////////////////////////////////////////
# $< -o $@ 在上面的第一項加-o這個optimize的符號			

# clean all the .o and executable files
clean:
		rm -rf *.o bin/*

