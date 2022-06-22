compile:
	g++ -std=c++1y  main.cpp -Wall -o main

run:
	./main $(file) $(restart) > output.txt

valgrind:
	valgrind ./main 

clean: 
	rm -rf main main.exe
