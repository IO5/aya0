.PHONY: all release debug clean rebuild parser

SRC = $(wildcard *.cpp vm/*.cpp parser/*.cpp) lparser.c 

#ifeq ($(TARGET),)

#all: release

#release: obj/release/dependencies
	#make TARGET=release $(filter-out release,$(MAKECMDGOALS))

#debug: obj/debug/dependencies
	#make TARGET=debug $(filter-out debug,$(MAKECMDGOALS))


#obj/%/dependencies: $(SRC) $(wildcad *.h vm/*.h parser/*.h)
	#mkdir -p obj/$* bin/$*
	#$(foreach FILE,$(SRC), $(CXX) -MM -std=c++11 $(FILE) | \
	#sed "s%^.*:%obj/$*/$(basename $(FILE)).o:%" >> $@ ; )
##	$(CXX) -MM -std=c++11 $(SRC) > $@
##	sed -i 's/^[^ ]/obj\/$*\//' $@

#else

QUEX_PATH = /home/io/quex/

FLAGS = -std=c++11 -Wall -Wextra -Winline -DQUEX_OPTION_ASSERTS_DISABLED -I$(QUEX_PATH) -I/usr/include/boost

ifeq ($(TARGET),release)
	FLAGS += -O2
endif

ifeq ($(TARGET),debug)
	FLAGS += -O0 -g -DDEBUG
endif 

OBJDIR = obj/$(TARGET)

OBJ = $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRC)))

EXE = bin/$(TARGET)/aya 

all: $(EXE)

lparser.c: lparser.y
	./lemon -s lparser.y

$(OBJDIR)/lparser.o: lparser.c
	$(CXX) $(FLAGS) -o $@ -c $<

lexer: lexer.qx
	python2 /home/io/quex/quex-exe.py \
	--token-policy single --token-memory-management-by-user \
	--token-id-offset 256 \
	--no-include-stack \
	--token-id-prefix TK_ \
	--foreign-token-id-file lparser.h \
	-i lexer.qx \
	-o lexer

-include $(OBJDIR)/dependencies

$(EXE): $(OBJ)
	$(CXX) $(FLAGS) -lboost_system -lboost_filesystem  -o $@ $^

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

$(OBJDIR)/vm/%.o: vm/%.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

$(OBJDIR)/parser/%.o: parser/%.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

#endif

rebuild: clean all

clean: 
	rm -rf bin/*/aya obj/*/*.o obj/*/dependencies
