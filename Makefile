make&run:
	g++ -shared -o TankYou.so -fPIC TankYou.cpp MoveController.cpp common.cpp -std=c++11 -DDYNAMIC
	rm -f projectx/tanks/TankYou.so
	rm -f projectx/Makefile
	rm -f projectx/config.txt
	mv TankYou.so projectx/tanks/
	cp override_make projectx/Makefile
	cp override_config projectx/config.txt