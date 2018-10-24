INCL := -Iinclude
SRC_FILES := $(wildcard src/*.cpp)
CFLAGS := -std=c++11 -fPIC -Wall
EXECUTABLE = TankYou
SO_FLAGS := -shared -o $(EXECUTABLE).so -DDYNAMIC
SUBMOD := projectx/

TankYou:
	g++ $(SO_FLAGS) $(SRC_FILES) $(INCL) $(CFLAGS)
	rm -f $(SUBMOD)tanks/$(EXECUTABLE).so
	rm -f $(SUBMOD)Makefile
	rm -f $(SUBMOD)config.txt
	mv $(EXECUTABLE).so $(SUBMOD)tanks/
	cp overrides/override_make $(SUBMOD)Makefile
	cp overrides/override_config $(SUBMOD)config.txt