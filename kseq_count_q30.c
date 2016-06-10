#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(void)
{
    gzFile fp;
    kseq_t *seq;
    unsigned long long n = 0, slen = 0, q30 = 0, k=0;
    double average, percentage_q30;
    int offset = 33, qual = 0;
    fp = gzdopen(fileno(stdin), "r");
    seq = kseq_init(fp);
    while (kseq_read(seq) >= 0){
        for(k = 0;k < seq->seq.l;++k){ 
            char qualchar = seq->qual.s[k];
            qual = (int) qualchar - offset;
            if (qual >= 30){
                ++q30;
            }
        };
        ++n, slen += seq->seq.l;
    }
    average = (double) slen / n;
    percentage_q30= ((double) q30 / slen)*100;

    printf("Number of sequences: %llu\tAverage length: %4.3f\tTotal number of bases: %llu\tNumber of bases >= Q30: %llu (%4.3f%%)\n", n, average, slen, q30, percentage_q30);

    kseq_destroy(seq);
    gzclose(fp);
    return 0;
}
