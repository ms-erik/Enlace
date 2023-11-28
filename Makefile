all:
	g++ -o out comunicacao.cpp main.cpp

run:
	./out

clean:
	rm out
