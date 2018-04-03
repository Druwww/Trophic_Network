CC = g++
ODIR = obj
PROG = main
CXXFLAG = -std=c++11

$(PROG) : $(ODIR) $(ODIR)/Node.o $(ODIR)/Vertex.o $(ODIR)/GraphData.o $(ODIR)/main.o $(ODIR)/utils.o 
	$(CC) -o $@ $(ODIR)/Node.o $(ODIR)/Vertex.o $(ODIR)/GraphData.o $(ODIR)/main.o $(ODIR)/utils.o $(CXXFLAG)

$(ODIR)/Node.o : ./entities/src/Node.cpp ./entities/include/Node.h ./utils/include/utils.h 
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/Vertex.o : ./entities/src/Vertex.cpp ./entities/include/Vertex.h ./entities/include/Node.h ./utils/include/utils.h 
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/GraphData.o : ./entities/src/GraphData.cpp ./entities/include/GraphData.h ./entities/include/Node.h ./utils/include/utils.h ./entities/include/Vertex.h ./entities/include/Node.h ./utils/include/utils.h 
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/main.o : ./src/main.cpp ./entities/include/GraphData.h ./utils/include/utils.h 
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/utils.o : ./utils/src/utils.cpp ./utils/include/utils.h 
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(PROG) ]; then rm $(PROG); fi

