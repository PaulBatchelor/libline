NAME=libline

default: $(NAME).pdf $(NAME).a debug

WEBFILES=$(NAME).w header.w point.w line.w mem.w linpoint.w lines.w sporth.w

LDFLAGS=-lsporth -lsoundpipe -lsndfile -lm -ldl

CFLAGS = -Wall -ansi -g -DLL_SPORTH

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME).a: $(NAME).o
	$(AR) rcs $@ $(NAME).o

debug: debug.c $(NAME).o 
	$(CC) $(CFLAGS) debug.c -o $@ $(NAME).o $(LDFLAGS)

$(NAME).pdf: $(WEBFILES)
	cweave $(NAME).w
	tex "\let\pdf+ \input $(NAME)"
	dvipdfm $(NAME).dvi

$(NAME).c: $(WEBFILES)
	ctangle $(NAME).w

clean:
	rm -rf $(NAME).pdf
	rm -rf $(NAME).c
	rm -rf $(NAME).scn
	rm -rf $(NAME).idx
	rm -rf $(NAME).log
	rm -rf $(NAME).dvi
	rm -rf $(NAME).toc
	rm -rf $(NAME).tex
	rm -rf $(NAME).a
	rm -rf $(NAME).o
	rm -rf debug
	rm -rf line.h
