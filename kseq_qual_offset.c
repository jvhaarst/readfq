#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int maxq = 0,minq = 256;

int main(void)
{
	gzFile fp;
	kseq_t *seq;
	int n = 0, slen = 0, qlen = 0;
	int k;
	int qual;
	fp = gzdopen(fileno(stdin), "r");
	seq = kseq_init(fp);
	while (kseq_read(seq) >= 0){
		for(k = 0;k < seq->seq.l;++k){ 
			char qualchar = seq->qual.s[k];
			qual = (int) qualchar;
			if (qual > maxq){
				maxq=qual;
			}

                        if (qual < minq){
                                minq=qual;
                        }
		};
	}
        printf("%d\t%d\n", minq,maxq);
        printf("%c\t%c\n", minq,maxq);
	kseq_destroy(seq);
	gzclose(fp);
	return 0;
}
