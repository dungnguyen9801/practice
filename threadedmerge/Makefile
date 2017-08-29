exec = threadedmerge
source = $(exec).cpp
$(exec): $(source)
	g++ -std=gnu++11 $(source) -pthread -o $(exec)
clean:
	rm $(exec)    
run:
	./$(exec)
