CC = g++
ODIR = obj
PROG = main
CXXFLAG = -std=c++11

$(PROG) : $(ODIR) $(ODIR)/Edge.o $(ODIR)/Node.o $(ODIR)/Graph.o $(ODIR)/main.o $(ODIR)/utils.o
	$(CC) -o $@ $(ODIR)/Edge.o $(ODIR)/Node.o $(ODIR)/Graph.o $(ODIR)/main.o $(ODIR)/utils.o $(CXXFLAG)

$(ODIR)/Edge.o : ./entities/graph/src/Edge.cpp ./entities/graph/include/Edge.h ./entities/graph/include/Node.h ./utils/include/utils.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/Node.o : ./entities/graph/src/Node.cpp ./entities/graph/include/Node.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/Graph.o : ./entities/graph/src/Graph.cpp ./entities/graph/include/Graph.h ./entities/graph/include/Node.h ./utils/include/utils.h ./entities/graph/include/Edge.h ./entities/graph/include/Node.h ./utils/include/utils.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/main.o : ./src/main.cpp ./entities/graph/include/Graph.h ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/utils.o : ./utils/src/utils.cpp ./utils/include/utils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(PROG) ]; then rm $(PROG); fi
