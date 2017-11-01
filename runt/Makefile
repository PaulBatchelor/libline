default: all

NAME=ll
OBJ=runt_ll.o ../libline.o

CFLAGS += -DLL_SPORTH_STANDALONE
CFLAGS += -I$(HOME)/.runt/include
CFLAGS += -I../ -g
LDFLAGS += -lsporth -ldl
LDFLAGS += -L$(HOME)/.runt/lib -lrunt -lrunt_patchwerk -lsoundpipe -lm -lsndfile

all: librunt_$(NAME).a rnt$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rnt$(NAME): parse.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ) $(LDFLAGS)

librunt_$(NAME).a: $(OBJ)
	$(AR) rcs $@ $(OBJ)

install: librunt_$(NAME).a rnt$(NAME)
	mkdir -p ~/.runt/lib
	mkdir -p ~/.runt/bin
	mkdir -p ~/.runt/include
	mkdir -p ~/.runt/plugins
	cp librunt_$(NAME).a ~/.runt/lib
	cp rnt$(NAME) ~/.runt/bin

clean: 
	rm -rf $(OBJ) rnt$(NAME) librunt_$(NAME).a
