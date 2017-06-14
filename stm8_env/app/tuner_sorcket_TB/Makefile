CC=sdcc
CFLAGS=-mstm8
INCLUDEPATH=../../include/stm8s/
DEFINES= stm8s103?3
SOURCE=main
OUTPUT_DIR=build/
all:	compile 
compile:	
	mkdir -p $(OUTPUT_DIR)
	#$(CC) $(CFLAGS) -I $(INCLUDEPATH) -D $(DEFINES) -o $(OUTPUT_DIR) $(SOURCE).c 
	$(CC) $(CFLAGS) -I $(INCLUDEPATH) -o $(OUTPUT_DIR) $(SOURCE).c 
flash:	
	stm8flash -c stlinkv2 -p stm8s003 -w build/main.ihx
