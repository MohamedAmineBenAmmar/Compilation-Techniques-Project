compile: syntactic_analyzer_main_executable
	echo "Compilation done successfully"

syntactic_analyzer_main_executable: syn_main.o syn_functions.o syn_converter.o first.o follow.o
	gcc syntactic_analyzer/tmp/build/main.o syntactic_analyzer/tmp/build/first.o syntactic_analyzer/tmp/build/follow.o syntactic_analyzer/tmp/build/functions.o syntactic_analyzer/tmp/build/converter.o -o syntactic_analyzer/main

syn_main.o: syntactic_analyzer/main.c
	gcc -c syntactic_analyzer/main.c -o syntactic_analyzer/tmp/build/main.o

syn_functions.o: syntactic_analyzer/config/*
	gcc -c syntactic_analyzer/config/functions.c -o syntactic_analyzer/tmp/build/functions.o

syn_converter.o: syntactic_analyzer/converter/*
	gcc -c syntactic_analyzer/converter/converter.c -o syntactic_analyzer/tmp/build/converter.o

first.o: syntactic_analyzer/core/first/*
	gcc -c syntactic_analyzer/core/first/first.c -o syntactic_analyzer/tmp/build/first.o

follow.o: syntactic_analyzer/core/follow/*
	gcc -c syntactic_analyzer/core/follow/follow.c -o syntactic_analyzer/tmp/build/follow.o

lexical_analyzer_main_executable: lex_main.o lex_tokens.o lex_preprocessor_minifier.o lex_config_functions
	gcc lexical_analyzer/tmp/build/functions.o lexical_analyzer/tmp/build/minifier.o lexical_analyzer/tmp/build/tokens.o lexical_analyzer/tmp/build/main.o -o lexical_analyzer/main

lex_main.o: lexical_analyzer/main.c
	gcc -c lexical_analyzer/main.c -o lexical_analyzer/tmp/build/main.o

lex_preprocessor_minifier.o: lexical_analyzer/preprocessor/minifier/*
	gcc -c lexical_analyzer/preprocessor/minifier/minifier.c -o lexical_analyzer/tmp/build/minifier.o

lex_tokens.o: lexical_analyzer/tokens/*
	gcc -c lexical_analyzer/tokens/tokens.c -o lexical_analyzer/tmp/build/tokens.o

lex_config_functions: lexical_analyzer/config/*
	gcc -c lexical_analyzer/config/functions.c -o lexical_analyzer/tmp/build/functions.o