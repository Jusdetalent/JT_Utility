# 
# Make file for chasse aux sorciere
# By Henock :: 06/ 11/ 2018
#

CC = g++
BIN = bin/libHN_Utility.a 
AR = ar
INC = -I/usr/local/include/SDL -I/usr/local/include 
LIBS = -L/usr/local/lib -Wl,-rpath,/usr/local/lib 
CXXFLAGS = $(INC) -D_REENTRANT -D_THREAD_SAFE $(LIBS) 

# Base folder
DATETIME_OBJ_DIR = objs/HN_DateTime/
DATETIME_DIR = HN_DateTime/
PROCESS_OBJ_DIR = objs/HN_Process/
PROCESS_DIR = HN_Process/
PATH_OBJ_DIR = objs/HN_Path/
PATH_DIR = HN_Path/

# Main objects
OBJ = $(DATETIME_OBJ_DIR)HN_Clock.o $(DATETIME_OBJ_DIR)HN_Date.o $(DATETIME_OBJ_DIR)HN_Interval.o $(DATETIME_OBJ_DIR)HN_Period.o 
OBJ+= $(DATETIME_OBJ_DIR)HN_Ticks.o $(DATETIME_OBJ_DIR)HN_Time.o $(DATETIME_OBJ_DIR)HN_TimePoint.o  $(PROCESS_OBJ_DIR)HN_Thread.o 
OBJ+= $(PATH_OBJ_DIR)HN_File.o 

# Assemblate link objects
LINKOBJ = $(OBJ) 

# Make all
$(BIN): $(OBJ)
	$(AR) r $(BIN) $(LINKOBJ) 

# Build date time objects
$(DATETIME_OBJ_DIR)HN_Clock.o: $(DATETIME_DIR)HN_Clock.cpp
	$(CC) -c $(DATETIME_DIR)HN_Clock.cpp -o $(DATETIME_OBJ_DIR)HN_Clock.o $(CXXFLAGS)
	
$(DATETIME_OBJ_DIR)HN_Date.o: $(DATETIME_DIR)HN_Date.cpp
	$(CC) -c $(DATETIME_DIR)HN_Date.cpp -o $(DATETIME_OBJ_DIR)HN_Date.o $(CXXFLAGS)
	
$(DATETIME_OBJ_DIR)HN_Interval.o: $(DATETIME_DIR)HN_Interval.cpp
	$(CC) -c $(DATETIME_DIR)HN_Interval.cpp -o $(DATETIME_OBJ_DIR)HN_Interval.o $(CXXFLAGS)
	
$(DATETIME_OBJ_DIR)HN_Period.o: $(DATETIME_DIR)HN_Period.cpp
	$(CC) -c $(DATETIME_DIR)HN_Period.cpp -o $(DATETIME_OBJ_DIR)HN_Period.o $(CXXFLAGS)
	
$(DATETIME_OBJ_DIR)HN_Ticks.o: $(DATETIME_DIR)HN_Ticks.cpp
	$(CC) -c $(DATETIME_DIR)HN_Ticks.cpp -o $(DATETIME_OBJ_DIR)HN_Ticks.o $(CXXFLAGS)
	
$(DATETIME_OBJ_DIR)HN_Time.o: $(DATETIME_DIR)HN_Time.cpp
	$(CC) -c $(DATETIME_DIR)HN_Time.cpp -o $(DATETIME_OBJ_DIR)HN_Time.o $(CXXFLAGS)
	
$(DATETIME_OBJ_DIR)HN_TimePoint.o: $(DATETIME_DIR)HN_TimePoint.cpp
	$(CC) -c $(DATETIME_DIR)HN_TimePoint.cpp -o $(DATETIME_OBJ_DIR)HN_TimePoint.o $(CXXFLAGS)

# Build process objects
$(PROCESS_OBJ_DIR)HN_Thread.o: $(PROCESS_DIR)HN_Thread.cpp
	$(CC) -c $(PROCESS_DIR)HN_Thread.cpp -o $(PROCESS_OBJ_DIR)HN_Thread.o $(CXXFLAGS)

# Build path objects
$(PATH_OBJ_DIR)HN_File.o: $(PATH_DIR)HN_File.cpp
	$(CC) -c $(PATH_DIR)HN_File.cpp -o $(PATH_OBJ_DIR)HN_File.o $(CXXFLAGS)
	
# Perform clean operation
clean:
	rm $(BIN) $(OBJ)

install:
	mkdir /usr -p
	mkdir /usr/local -p
	mkdir /usr/local/lib -p
	cp -f $(BIN) /usr/local/lib/libHN_Utility.a
	
	mkdir /usr/local/include -p
	mkdir /usr/local/include/HN_Utility -p
	mkdir /usr/local/include/HN_Utility/HN_DateTime -p
	cp -f $(DATETIME_DIR)HN_Clock.hpp /usr/local/include/HN_Utility/HN_DateTime/HN_Clock.hpp
	cp -f $(DATETIME_DIR)HN_Date.hpp /usr/local/include/HN_Utility/HN_DateTime/HN_Date.hpp
	cp -f $(DATETIME_DIR)HN_Interval.hpp /usr/local/include/HN_Utility/HN_DateTime/HN_Interval.hpp
	cp -f $(DATETIME_DIR)HN_Period.hpp /usr/local/include/HN_Utility/HN_DateTime/HN_Period.hpp
	cp -f $(DATETIME_DIR)HN_Ticks.hpp /usr/local/include/HN_Utility/HN_DateTime/HN_Ticks.hpp
	cp -f $(DATETIME_DIR)HN_Time.hpp /usr/local/include/HN_Utility/HN_DateTime/HN_Time.hpp
	cp -f $(DATETIME_DIR)HN_TimePoint.hpp /usr/local/include/HN_Utility/HN_DateTime/HN_TimePoint.hpp
	
	mkdir /usr/local/include/HN_Utility/HN_Process -p
	cp -f $(PROCESS_DIR)HN_Thread.hpp /usr/local/include/HN_Utility/HN_Process/HN_Thread.hpp
	
	mkdir /usr/local/include/HN_Utility/HN_Path -p
	cp -f $(PATH_DIR)HN_File.hpp /usr/local/include/HN_Utility/HN_Path/HN_File.hpp
	
	