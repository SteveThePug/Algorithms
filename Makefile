CC = gcc
CFLAGS =  -g
SOURCES = main.c list.c graph.c array.c display.c
TARGET = main
BUILDDIR = .build

$(TARGET): $(SOURCES)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILDDIR)/$(TARGET)

.PHONY: clean debug

clean:
	rm -rf $(BUILDDIR)

debug: $(TARGET)
	gdb $(BUILDDIR)/$(TARGET)

run: $(TARGET)
	$(BUILDDIR)/$(TARGET)
