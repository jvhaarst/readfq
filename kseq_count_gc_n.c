#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(void)
{
    gzFile fp;
    kseq_t *seq;
    unsigned long long n = 0, slen = 0, gc = 0, ns = 0, k = 0;
    double average, gc_perc, n_perc;
    int offset = 33, qual = 0;
    fp = gzdopen(fileno(stdin), "r");
    seq = kseq_init(fp);
    while (kseq_read(seq) >= 0){
        for(k = 0;k < seq->seq.l;++k){ 
            char seqchar = seq->seq.s[k];
            if (seqchar == 'C' || 
                seqchar == 'c' || 
                seqchar == 'G' || 
                seqchar == 'g' || 
                seqchar == 'S' || 
                seqchar == 's')
            {
                ++gc;
            }
            if (seqchar == 'N' || 
                seqchar == 'n')
            {
                ++ns;
            }
            
        };
        ++n, slen += seq->seq.l;
    }

    average = (double) slen / n;
    gc_perc = (double) gc * 100 / slen;
    n_perc = (double) ns * 100 / slen;

    printf("%llu\t%4.3f\t%llu\t%llu\t(%4.3f%%)\t%llu\t(%4.3f%%)\n", n, average, slen, gc, gc_perc, ns, n_perc);

    kseq_destroy(seq);
    gzclose(fp);
    return 0;
}
