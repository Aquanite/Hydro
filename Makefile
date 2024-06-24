#compile Main.c Parser.c Definitions.c for windows or linux depending on the OS

# OS detection
ifeq ($(OS),Windows_NT)
	# Windows
	EXECUTABLE = Main.exe
else
	# Linux
	EXECUTABLE = Main
endif

# Compile
all: Main.c Parser.c Definitions.c
	if [ ! -d "./HydroCompiled" ]; then mkdir HydroCompiled; fi
	gcc -o ./HydroCompiled/$(EXECUTABLE) Main.c Parser.c Definitions.c -Wno-discarded-qualifiers -Wno-incompatible-pointer-types -Wno-implicit-function-declaration

# Clean
clean:
	rm -rf HydroCompiled

# Run
run:
	make all
	./HydroCompiled/$(EXECUTABLE) $(ARGS)

noremake:
	./HydroCompiled/$(EXECUTABLE) $(ARGS)