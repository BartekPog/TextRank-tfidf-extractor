kompilator=gcc
standard=-std=c11
optymalizacja=-O3
errors=-pedantic-errors
profilowanie=-pg

.PHONY: clean

__ : main
	./main   
	            
	            
main : main.o hashmap.o token.o reading_utils.o count_import.o rewrite.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^ 		            
	            
main.o : main.c
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

test: test.o hashmap.o token.o reading_utils.o count_import.o rewrite.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^ && ./$@

test.o: test.c
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^ 


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
