all:kseq.h kseq_test.c
		$(CC) -g -O2 kseq_test.c -o kseq_test -lz
		$(CC) -g -O2 kseq_count.c -o kseq_count -lz

clean:
		rm -f *.o kseq_test kseq_count

