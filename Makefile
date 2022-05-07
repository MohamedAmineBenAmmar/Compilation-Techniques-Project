compile: syntactic_analyzer_main_executable
	echo "test"

lexical_analyzer_main_executable: main.o tokens.o preprocessor_minifier.o config_functions
	gcc lexical_analyzer/tmp/build/functions.o lexical_analyzer/tmp/build/minifier.o lexical_analyzer/tmp/build/tokens.o lexical_analyzer/tmp/build/main.o -o lexical_analyzer/main

main.o: lexical_analyzer/main.c
	gcc -c lexical_analyzer/main.c -o lexical_analyzer/tmp/build/main.o

preprocessor_minifier.o: lexical_analyzer/preprocessor/minifier/*
	gcc -c lexical_analyzer/preprocessor/minifier/minifier.c -o lexical_analyzer/tmp/build/minifier.o

tokens.o: lexical_analyzer/tokens/*
	gcc -c lexical_analyzer/tokens/tokens.c -o lexical_analyzer/tmp/build/tokens.o

config_functions: lexical_analyzer/config/*
	gcc -c lexical_analyzer/config/functions.c -o lexical_analyzer/tmp/build/functions.o