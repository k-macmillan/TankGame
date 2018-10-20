make&run:
	rm -f projectx/TankYou.cpp
	rm -f projectx/TankYou.h
	rm -f projectx/Makefile
	rm -f projectx/config.txt
	cp TankYou.cpp projectx/TankYou.cpp
	cp TankYou.h projectx/TankYou.h
	cp override_make projectx/Makefile
	cp override_config projectx/config.txt
	make --directory projectx/
	(cd projectx && exec ./platform)