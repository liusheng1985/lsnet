SRC    = $(wildcard ./src/*.cc)
HDR    = $(wildcard ./src/*.h)
LIBDIR = ./lib
INDIR1 = ./src
INDIR2 = ./lib/include
TGT    = ./bin/lsnet

lsnet: $(SRC) $(HDR)
	mkdir -p bin
	g++ -g -o $(TGT) $(SRC) $(HDR) -I$(INDIR1) -I$(INDIR2) -L$(LIBDIR) -lpcap
	chmod a+x $(TGT)


clean :
	rm -f $(TGT)


