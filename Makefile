clean:
	cd build && rm -f tictactoe

build:
	cmake -S . -B build && cmake --build build

run:
	make build && ./build/tictactoe

play:
	rm -rf build && make run
