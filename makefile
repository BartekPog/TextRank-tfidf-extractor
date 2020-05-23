kompilator=gcc
standard=-std=gnu11 # -std=c11
optymalizacja=-O3
errors=-pedantic-errors
profilowanie=-pg

.PHONY: clean

__ : main
	./main   
	            
	            
main : main.o handle_input.o hashmap.o token.o reading_utils.o count_import.o rewrite.o tf_idf.o textrank.o textrank_graph.o textrank_score.o 
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^ 	-lm            
	            
main.o : main.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 

handle_input.o : handle_input.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 
 
hashmap.o : hashmap.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 
 
token.o : token.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 

reading_utils.o : reading_utils.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 

count_import.o : count_import.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 

rewrite.o : rewrite.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 

tf_idf.o : tf_idf.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^  -lm

textrank.o : textrank.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^  -lm

textrank_graph.o : textrank_graph.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^  -lm

textrank_score.o : textrank_score.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^  -lm



test: test.o hashmap.o token.o reading_utils.o count_import.o rewrite.o tf_idf.o textrank.o textrank_graph.o textrank_score.o 
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^  -lm && ./$@  

test.o: test.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ -lm


# libs/stmr.o : 
# 	echo "cool"
	# $(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^

profil : main.c
	if [ -f main ]; then rm main ; fi ;
	$(kompilator) $(standard)  $(profilowanie) -o main main.c
	# 
	./main
	gprof main > profil.txt
	
	
clean : 	
	for f in `ls *.o` ; do  if [ -f $$f ] ; then rm $$f  ; fi;   done;
	if [ -f main ] ; then rm main ; fi ;
