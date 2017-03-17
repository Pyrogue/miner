miner: miner.cpp
	g++ miner.cpp -o miner -lncurses
clean:
	rm -f miner