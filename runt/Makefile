default: all

OBJ=runt_ll.o

CFLAGS += -I$(HOME)/.runt/include
CFLAGS += -I../ -g
LDFLAGS += -L../ -lline -lsporth -ldl
LDFLAGS += -L$(HOME)/.runt/lib -lrunt -lrunt_patchwerk -lsoundpipe -lm -lsndfile

all: librunt_ll.a rntll

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rntll: parse.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(OBJ) $(LDFLAGS)

librunt_ll.a: $(OBJ)
	$(AR) rcs $@ $(OBJ)

clean: 
	rm -rf $(OBJ) rntll librunt_ll.a
