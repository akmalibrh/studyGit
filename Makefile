# Compiler
CC := gcc

# Paths
PKG_CONFIG_XLSXIO := -I./Library/xlsxio/include -L./Library/xlsxio/lib -lxlsxio_read
# PKG_CONFIG_GTK4 := -IC:/msys64/mingw64/include/gtk-4.0 -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/fribidi -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/include/webp -DLIBDEFLATE_DLL -IC:/msys64/mingw64/include/cairo -IC:/msys64/mingw64/include/freetype2 -IC:/msys64/mingw64/include/libpng16 -IC:/msys64/mingw64/include/pixman-1 -IC:/msys64/mingw64/include/graphene-1.0 -IC:/msys64/mingw64/lib/graphene-1.0/include -mfpmath=sse -msse -msse2 -IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -LC:/msys64/mingw64/lib -lgtk-4 -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lharfbuzz -lgraphene-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl

# Libraries
LIBS := 

# Source files
SRCS := main.c bianca.c excelpart.c kania.c

# Output executable
TARGET := "./main.exe"

# Compiler flags
CFLAGS := 

# Build target
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(PKG_CONFIG_XLSXIO) $(LIBS)

# Clean target
clean:
	rm $(TARGET)
