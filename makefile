main: main.o regex_key_value.o examplewindow.o
		g++-4.9 -o logext main.o regex_key_value.o examplewindow.o `pkg-config --libs --cflags gtkmm-3.0`

main.o: include/fptree.h include/cluster.h include/HMM.h main.cpp include/Analyze.h include/examplewindow.h
		g++-4.9 -c main.cpp -std=c++11 `pkg-config --libs --cflags gtkmm-3.0`

regex_key_value.o: include/regex_key_value.h src/regex_key_value.cpp
		g++-4.9 -c src/regex_key_value.cpp -std=c++11

examplewindow.o: include/examplewindow.h src/examplewindow.cpp
		g++-4.9 -c src/examplewindow.cpp -std=c++11 `pkg-config --libs --cflags gtkmm-3.0`
		
clean:
	rm -rf *o logext
