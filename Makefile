NAME=libline

default: libline.pdf debug

debug: libline.c
	$(CC) $< -DBUILD_MAIN -o $@

$(NAME).pdf: $(NAME).w
	cweave -x $<
	tex "\let\pdf+ \input libline"
	dvipdfm $(NAME).dvi

$(NAME).c: $(NAME).w
	ctangle $<

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
