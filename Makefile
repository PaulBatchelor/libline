NAME=libline

default: $(NAME).pdf $(NAME).a

WEBFILES=$(NAME).w header.w point.w line.w mem.w

CFLAGS = -Wall -ansi

%.o: %.c
	$(CC) -c $< -o $@

$(NAME).a: $(NAME).o
	$(AR) rcs $@ $(NAME).o

#debug: $(NAME).c
#	$(CC) $(CFLAGS) $< -DBUILD_MAIN -o $@

$(NAME).pdf: $(WEBFILES)
	cweave -x $(NAME).w
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
	rm -rf debug
	rm -rf line.h
