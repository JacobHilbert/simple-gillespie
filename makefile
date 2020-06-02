graph.pdf: graph.py arn.dat pr.dat
	@echo "Graphing"
	@python3 graph.py "arn.dat" "pr.dat"

arn.dat pr.dat: gillespie.out gillespie.cpp
	@echo "Running"
	@time ./gillespie.out

gillespie.out: gillespie.cpp
	@echo "Compiling"
	@g++ -fopenmp -Ofast gillespie.cpp -o gillespie.out

clean:
	@rm -f *.dat
	@rm -f *.out
	@rm -f *.pdf
	@clear
