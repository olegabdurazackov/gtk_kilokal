
C = gcc
LDLIBS = `pkg-config gtk+-2.0 --libs`
CFLAGS = -Wall			 	\
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED

CFLAGSMENU = -Wall			 	\
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED 

N = gtk_kilo

$N: menu.o about.o dbase.o date.o \
		edit.o -lsqlite3 
	$C $^ -o $@ $(LDLIBS)

menu.o: menu.c
	$C -c $^   $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs` 

edit.o: edit.c
	$C -c $^   $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs` 

about.o: about.c
	$C -c $^   $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs` 

date.o: date.c
	$C -c $^   $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs` 


dbase.o: dbase.c
	$C -c $^  # $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs` 

clear: 
	rm -f *.o 
