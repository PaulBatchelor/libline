NAME=libline

default: $(NAME).pdf debug

WEBFILES=$(NAME).w header.w point.w

CFLAGS = -Wall -ansi

debug: $(NAME).c
	$(CC) $(CFLAGS) $< -DBUILD_MAIN -o $@

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
	rm -rf debug
	rm -rf line.h
