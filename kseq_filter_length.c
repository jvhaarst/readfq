#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)
/*
 Compile with
 	g++ kseq_filter_length.c -Wall -O3 -o kseq_filter_length -lz
*/
int main( int argc, char *argv[] )
{
	unsigned int length;
	if (argc == 1){
		length = (int)argv[1][0];
	}else{
		length = 101;
	}
	gzFile fp;
    kseq_t *seq;
    fp = gzdopen(fileno(stdin), "r");
    seq = kseq_init(fp);
    while (kseq_read(seq) >= 0)
    	if (seq->seq.l > length){
    		/*
		puts(seq->seq);
		*/
            printf(">%s %s\n%s\n", seq->name.s, seq->comment.s, seq->seq.s);
    	}
    kseq_destroy(seq);
    gzclose(fp);
    return 0;

}
