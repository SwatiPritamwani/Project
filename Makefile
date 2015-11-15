try: project.o 
	cc project.c -o try
project.o: project.c 
	cc -c project.c

