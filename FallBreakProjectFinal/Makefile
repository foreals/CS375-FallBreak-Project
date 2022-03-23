all: getstat lsl kitten readdb

getstat: getstat.c
	clang -o getstat getstat.c
lsl: lsl.c
	clang -o lsl lsl.c
kitten: kitten.c
	clang -o kitten kitten.c
readdb: readdb.c
	clang -o readdb readdb.c -lsqlite3
clean:
	rm -f lsl *~
	rm -f getstat *~
	rm -f readdb *~
