SRCDIR = src
SRCSUB = $(wildcard $(SRCDIR)/**/*.c)
SRC = $(SRCSUB) $(wildcard $(SRCDIR)/*.c)
#_OBJ = $(subst $(SRCDIR),$(DSTDIR),$(SRC))
#OBJ = $(subst .c,.o,$(_OBJ))
HPATH = -Isrc -Isrc/proto -I/usr/include -I/usr/local/include/protobuf-c
LPATH = -L/usr/local/lib
LIBS = -lpthread -lprotobuf -lprotobuf-c -lncurses -lpcap

all: 
	gcc $(HPATH) $(LPATH) -o sniffer-demo.exe $(SRC) $(LIBS)

#$(DSTDIR)/%.o: $(SRCDIR)/%.c
#	gcc -c $(HPATH) $^ -o $@

clean:
	rm -f sniffer-demo.exe
