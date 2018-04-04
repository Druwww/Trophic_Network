CC = g++
ODIR = obj
PROG = main
CXXFLAG = -std=c++11

$(PROG) : $(ODIR) $(ODIR)/Node.o $(ODIR)/Graph.o $(ODIR)/Vertex.o $(ODIR)/main.o $(ODIR)/utils.o $(ODIR)/algorithm.o
	$(CC) -o $@ $(ODIR)/Node.o $(ODIR)/Graph.o $(ODIR)/Vertex.o $(ODIR)/main.o $(ODIR)/utils.o $(ODIR)/algorithm.o $(CXXFLAG)

$(ODIR)/Node.o : ./entities/graph/src/Node.cpp ./entities/graph/include/Node.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/Graph.o : ./entities/graph/src/Graph.cpp ./entities/graph/include/Graph.h ./entities/graph/include/Node.h ./utils/include/utils.h ./entities/graph/include/Vertex.h ./entities/graph/include/Node.h ./utils/include/utils.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/Vertex.o : ./entities/graph/src/Vertex.cpp ./entities/graph/include/Vertex.h ./entities/graph/include/Node.h ./utils/include/utils.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/main.o : ./src/main.cpp ./entities/graph/include/Graph.h ./utils/include/utils.h ./entities/animal/include/Animal.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/utils.o : ./utils/src/utils.cpp ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/algorithm.o : ./algorithm/src/algorithm.cpp ./algorithm/include/algorithm.h ./entities/graph/include/Graph.h ./entities/animal/include/Animal.h ./entities/animal/include/NaturalLaw.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(PROG) ]; then rm $(PROG); fi
