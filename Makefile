.PHONY: pdf

NAME=libline

DEFAULT = $(NAME).a 

WEBFILES=$(NAME).w\
		 header.w\
		 point.w\
		 line.w\
		 mem.w\
		 linpoint.w\
		 lines.w\
		 sporth.w\
		 exppoint.w\
		 tick.w\
		 bezier.w

LDFLAGS=-lsporth -lsoundpipe -lsndfile -lm -ldl

CFLAGS = -Wall -ansi -g -pedantic

default: $(DEFAULT) 

pdf: $(NAME).pdf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME).a: $(NAME).o
	$(AR) rcs $@ $(NAME).o

debug: debug.c $(NAME).o 
	$(CC) $(CFLAGS) debug.c -o $@ $(NAME).o $(LDFLAGS)

mkplots: mkplots.c $(NAME).o
	$(CC) $(CFLAGS) mkplots.c -o $@ $(NAME).o $(LDFLAGS)

plot: 
	sh render_plots.sh

$(NAME).pdf: $(WEBFILES)
	cweave $(NAME).w
	tex "\let\pdf+ \input $(NAME)"
	dvipdfm $(NAME).dvi

$(NAME).c: $(WEBFILES)
	$(CTANGLE) $(NAME).w

clean:
	rm -rf $(NAME).pdf
	rm -rf $(NAME).scn
	rm -rf $(NAME).idx
	rm -rf $(NAME).log
	rm -rf $(NAME).dvi
	rm -rf $(NAME).toc
	rm -rf $(NAME).tex
	rm -rf $(NAME).a
	rm -rf $(NAME).o
	rm -rf mkplots 
	rm -rf debug
	rm -rf line_1.rnt line_1.png
	rm -rf line_2.rnt line_2.png
	rm -rf line_3.rnt line_3.png
	rm -rf line_4.rnt line_4.png
	rm -rf line_5.rnt line_5.png
	rm -rf line_6.rnt line_6.png
	rm -rf line_7.rnt line_7.png
	rm -rf line_8.rnt line_8.png
	rm -rf line_9.rnt line_9.png
