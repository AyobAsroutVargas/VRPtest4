CXX = g++
CXXFLAGS = -std=c++17 -g -Wall
DEPS = file-loader.h greedy-vrp.h vehicle.h grasp-vrp.h solution.h problem.h estructura-entorno.h reinsercion-intra.h intercambio-intra.h reinsercion-entre.h intercambio-entre.h gvns.h
OBJ = main.o file-loader.o greedy-vrp.o grasp-vrp.o problem.o solution.o reinsercion-intra.o intercambio-intra.o reinsercion-entre.o intercambio-entre.o gvns.o


%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm main *.o