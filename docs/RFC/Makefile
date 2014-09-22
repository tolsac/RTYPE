##
## Makefile for trade in /home/nerevarine/Documents/Trade/rapport
## 
## Made by nerevarine
## Login   <nerevarine@epitech.net>
## 
## Started on Fri Jun  1 22:39:45 2012 nerevarine
## Last update Sat Jan 19 22:27:23 2013 Nerevarine
##

NAME	= R-TypeRFC
SRC	= $(NAME).tex
DVI	= $(SRC:.tex=.dvi)
PS	= $(DVI:.dvi=.ps)
PDF	= $(PS:.ps=.pdf)

all:	dvi ps pdf

dvi:	$(SRC)
	@echo "Compilation de $(SRC) en $(DVI)."
	@latex $(SRC)

ps:	$(DVI)
	@echo "Compilation de $(DVI) en $(PS)."
	@dvips $(DVI)

pdf:	$(PS)
	@echo "Compilation de $(PS) en $(PDF)."
	@ps2pdf $(PS)

clean:
	@echo -n "Suppression de $(DVI) et $(PS)."
	@rm -rf $(DVI) $(PS)
	@echo " Terminée."
	@echo -n "Suppression des fichiers temporaires."
	@rm -rf $(NAME).aux $(NAME).log $(NAME).toc $(NAME).out
	@echo " Terminée."

fclean:	clean
	@echo -n "Suppression de $(PDF)."
	@rm -rf $(PDF)
	@echo " Terminée."

re:	fclean all
