CXX=g++
CXXFLAGS= -std=c++17 -Wall -Wextra -Werror
EXEC=game
SRCDIR=./src/cpp/
OBJDIR=./src/ofiles/
SRC=$(wildcard $(SRCDIR)*.cpp)
OBJ=$(SRC:$(SRCDIR)%.cpp=$(OBJDIR)%.o)

all: clean $(OBJDIR) $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p ${OBJDIR}

clean:
	rm -rf $(OBJDIR) $(EXEC)
