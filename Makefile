clean:
	cd build && rm -f tictactoe

build:
	cmake -S . -B build && cmake --build build

run:
	make build && ./build/tictactoe

dev:
	rm -rf build && make run

# init_new:
#  	mkdir build/
# 	cd build/
#
# build:
# 	cd build && cmake ..
# 	make
#
# run:
# 	build
# 	./tictactoe

#################################################

# INCDIR=/tmp/include
# BINDIR=/tmp
#
# SRCS_HEADERS= logic.h render.h game.h
# SRCS= main.c logic.c render.c
#
# tictactoe: $(SRCS) $(SRCS_HEADERS)
# 	echo "#define INCDIR \"$(INCDIR)\"" > incdir.hpp
# 	clang -o tictactoe -g -Wall -Werror -fdump-rtl-expand -DINCDIR=\"$(INCDIR)\" $(SRCS)
#
# incdir.hpp:
# 	echo "#define INCDIR \"$(INCDIR)\"" > incdir.hpp
#
# install: tictactoe
# 	mkdir -p $(INCDIR)
# 	rsync -a include/. $(INCDIR)
# 	cp tictactoe $(BINDIR)
# 	chmod +x $(BINDIR)/tictactoe
#
# clean:
# 	rm -f tictactoe tictactoe[0-9] *.o *.s out a.out incdir.hpp
