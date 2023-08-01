DEBUG_DIR = bin/debug
RELEASE_DIR = bin/release

TITLE = LaserMaze

CXX = g++
CPPFLAGS = -std=c++14 -m64 -g -Wall -I

debug: $(DEBUG_DIR)/$(TITLE)

release: $(RELEASE_DIR)/$(TITLE)

$(DEBUG_DIR)/$(TITLE): src/*.cpp 
	$(CXX) -c $^ -O3 $(CPPFLAGS) include && $(CXX) *.o -o $(DEBUG_DIR)/$(TITLE) -lSDL2main -lSDL2 -lSDL2_image && ./$(DEBUG_DIR)/$(TITLE)

$(RELEASE_DIR)/$(TITLE): src/*.cpp 
	$(CXX) -c $^ -O3 $(CPPFLAGS) include && $(CXX) *.o -o $(RELEASE_DIR)/$(TITLE) -s -lSDL2main -lSDL2 -lSDL2_image && ./$(RELEASE_DIR)/$(TITLE)

.PHONY: clean clean_release run run_release
clean:
	rm $(DEBUG_DIR)/$(TITLE)

clean_release:
	rm $(RELEASE_DIR)/$(TITLE)

run:
	./$(DEBUG_DIR)/$(TITLE)

run_release:
	./$(RELEASE_DIR)/$(TITLE)
