default: all

NAME=ll
OBJ=runt_ll.o ../libline.o

CFLAGS += -I$(HOME)/.runt/include
CFLAGS += -I../ -g
CFLAGS += -fPIC
LDFLAGS += -ldl
LDFLAGS += -L$(HOME)/.runt/lib -lrunt -lrunt_patchwerk -lsoundpipe -lm -lsndfile

all: librunt_$(NAME).a rnt$(NAME) ll.so

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rnt$(NAME): parse.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ) $(LDFLAGS)

librunt_$(NAME).a: $(OBJ)
	$(AR) rcs $@ $(OBJ)

ll.so: $(OBJ)
	$(CC) -shared $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

install: librunt_$(NAME).a rnt$(NAME) ll.so
	mkdir -p ~/.runt/lib
	mkdir -p ~/.runt/bin
	mkdir -p ~/.runt/include
	mkdir -p ~/.runt/plugins/patchwerk
	cp librunt_$(NAME).a ~/.runt/lib
	cp rnt$(NAME) ~/.runt/bin
	cp ll.so ~/.runt/plugins/patchwerk/

clean: 
	rm -rf $(OBJ) rnt$(NAME) librunt_$(NAME).a
	rm -rf ll.so
