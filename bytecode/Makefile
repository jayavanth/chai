include ../Makefile.common

LIBRARY_OBJECT_CODE = \
	BC.o \
	ByteCodes.o \
	EditStak.o \
	HashBC.o \
	HashJIT.o \
	PrintBC.o \
	RefCnt.o

LIBRARY_HEADER_FILES = \
	$(LIBRARY_OBJECT_CODE:.o=.hpp) \
	Stak.hpp \
	Visit.hpp

all : $(LIBRARY_OBJECT_CODE)

install : all
	install --mode=644 $(LIBRARY_HEADER_FILES) $(INTERNAL_HEADER_DIR)
	install $(LIBRARY_OBJECT_CODE) $(INTERNAL_OBJECT_DIR)

clean :
	rm -f *.o