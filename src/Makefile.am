## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(libusb_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = comsport

comsport_SOURCES = \
	main.cc   \
	DeviceCom.cxx   \
	DeviceCom.h   \
	BufferControl.h   \
	BufferControl.cxx   \
	Controller.cxx   \
	Controller.h   \
	Profile.cxx   \
	Profile.h   \
	ConvertControl.cxx   \
	ConvertControl.h

comsport_LDFLAGS = 

comsport_LDADD = \
	-lusb \
	$(libusb_LIBS)

