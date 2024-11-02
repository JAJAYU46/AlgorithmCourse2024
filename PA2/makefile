# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/mps   #the default 的時候是去build  bin/NTU_sort
	@echo -n ""

# optimized version
#bin/NTU_sort 那個final executable file
bin/mps	: maxPlanarSubset.o main_opt.o
			$(CC) $(OPTFLAGS) maxPlanarSubset.o main_opt.o -o bin/mps
# -o bin/NTU_sort: 要這個executable在bin file中叫的名字(executable name)

#main_opt.o is the compiled object file from src/main.cpp
main_opt.o 	   	: src/main.cpp
			$(CC) $(CFLAGS)	 $< -o $@ 
# 			$(CC) $(CFLAGS)  $< -Ilib -o $@ 
#$(CC): The compiler, g++ in this case.
#$(CFLAGS): Compilation flags, here set to -c, which compiles the source file into an object file without linking
#$<: 就是指上面這個executable的第一個項src/main.cpp， The first prerequisite in the rule. In this context, it represents the source file being compiled (e.g., src/main.cpp or src/sort_tool.cpp).
#-Ilib: Specifies the lib directory as an additional include path for header files. This allows the compiler to locate header files (e.g., lib/tm_usage.h) when compiling.
#-o $@: 表那個target "main_opt.o"，Specifies the output file name. $@ represents the target of the rule, typically the name of the object file to be generated (e.g., main_opt.o or sort_tool_opt.o).

maxPlanarSubset.o	: src/maxPlanarSubset.cpp # src/sort_tool.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@ 
# $< -o $@ 在上面的第一項加-o這個optimize的符號			

# # DEBUG Version
# dbg : bin/NTU_sort_dbg
# 	@echo -n ""

# bin/NTU_sort_dbg	: sort_tool_dbg.o main_dbg.o lib
# 			$(CC) $(DBGFLAGS) sort_tool_dbg.o main_dbg.o -ltm_usage -Llib -o bin/NTU_sort_dbg
# main_dbg.o 	   	: src/main.cpp lib/tm_usage.h
# 			$(CC) $(CFLAGS) $< -Ilib -o $@
# sort_tool_dbg.o	: src/sort_tool.cpp src/sort_tool.h
# 			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

# lib: lib/libtm_usage.a

# #建立東東放在lib libtm_usage.a: This is a library containing functions from tm_usage.o
# lib/libtm_usage.a: tm_usage.o
# 	$(AR) $(ARFLAGS) $@ $<
# #Including -ltm_usage and -Llib links this static library with the executable.
# #-ltm_usage tells the linker to include functions defined in libtm_usage.a, allowing NTU_sort to use those functions＃

# tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
# 	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o bin/*

