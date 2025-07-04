all:truth_table

task1:truth_table

task2:dnf_cnf

task3:truth_table_to_formula

task4:deductive_reasoning

task5:wanghao_algorithm

truth_table:PropositionalFormula.h TruthTable.h TruthTable.cpp
	g++ -DTRUTH_TABLE TruthTable.cpp -o main -std=c++17

dnf_cnf:PropositionalFormula.h TruthTable.h TruthTable.cpp
	g++ -DDNF_CNF TruthTable.cpp -o main -std=c++17

truth_table_to_formula:PropositionalFormula.h TruthTable.h TruthTable.cpp
	g++ -DTRUTH_TABLE_TO_FORMULA TruthTable.cpp -o main -std=c++17

deductive_reasoning:PropositionalFormula.h DeductiveReasoning.h DeductiveReasoning.cpp
	g++ DeductiveReasoning.cpp -o main -std=c++17

wanghao_algorithm:PropositionalFormula.h WangHaoAlgorithm.h WangHaoAlgorithm.cpp
	g++ WangHaoAlgorithm.cpp -o main -std=c++17

clean:
	rm -f main.exe

.PHONY: all clean