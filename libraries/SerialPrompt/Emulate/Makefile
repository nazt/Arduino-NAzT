CC=g++
PDE=SerialPrompt
CFLAGS=-Wall -O -I.
LIBS=
OBJDIR=obj
SOURCES=$(wildcard ../*.cpp)
EMSOURCES=$(wildcard *.cpp)
OBJS=$(SOURCES:../%.cpp=$(OBJDIR)/%.o)
EMOBJS=$(EMSOURCES:%.cpp=$(OBJDIR)/%.o) $(OBJDIR)/$(PDE).o
TARGET=$(PDE).exe

.INTERMEDIATE: $(PDE).cpp

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $@

#$(OBJDIR)/%.o: %.c
#	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/$(PDE).o: $(PDE).cpp
	$(CC) $(CFLAGS) -I.. -c -o $@ $<

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: ../%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(PDE).cpp: ../$(PDE).pde
	cp $< $(@:../%=%)

clean:
	-rm $(TARGET) $(OBJS) $(EMOBJS)

$(TARGET): $(OBJS) $(EMOBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(EMOBJS) $(LIBS)
