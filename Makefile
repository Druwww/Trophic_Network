CC = g++
ODIR = obj
PROG = main
CXXFLAG = -std=c++11

$(PROG) : $(ODIR) $(ODIR)/Node.o $(ODIR)/Graph.o $(ODIR)/Edge.o $(ODIR)/main.o $(ODIR)/utils.o $(ODIR)/algorithm.o
	$(CC) -o $@ $(ODIR)/Node.o $(ODIR)/Graph.o $(ODIR)/Edge.o $(ODIR)/main.o $(ODIR)/utils.o $(ODIR)/algorithm.o $(CXXFLAG)

$(ODIR)/Node.o : ./entities/graph/src/Node.cpp ./entities/graph/include/Node.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/Graph.o : ./entities/graph/src/Graph.cpp ./entities/graph/include/Graph.h ./entities/graph/include/Node.h ./utils/include/utils.h ./entities/graph/include/Edge.h ./entities/graph/include/Node.h ./utils/include/utils.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/Edge.o : ./entities/graph/src/Edge.cpp ./entities/graph/include/Edge.h ./entities/graph/include/Node.h ./utils/include/utils.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/main.o : ./src/main.cpp ./entities/graph/include/Graph.h ./utils/include/utils.h ./entities/animal/include/NodeAttr.h ./entities/animal/include/NodeAttr.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/utils.o : ./utils/src/utils.cpp ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/algorithm.o : ./algorithm/src/algorithm.cpp ./algorithm/include/algorithm.h ./entities/graph/include/Graph.h ./entities/animal/include/NodeAttr.h ./entities/animal/include/NodeAttr.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(PROG) ]; then rm $(PROG); fi
