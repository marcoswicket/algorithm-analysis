CC=g++

INCDIR = ./include
OBJDIR = ./obj
SRCDIR = ./src
LDIR = ./lib
BFOLDER = ./build

CFLAGS=-I$(INCDIR) -lSDL2 -lSDL2_image

DEPS = $(patsubst %,$(INCDIR)/%,$(wildcard $(INCDIR)/*.h))
OBJ = $(patsubst $(wildcard $(SRCDIR)/*.cpp)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

$(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEPS)

main: $(OBJ)
	$(CC) -o $(BFOLDER)/app $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCDIR)/*~
