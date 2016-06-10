#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(void)
{
	gzFile fp;
	kseq_t *seq;
	unsigned long long n = 0, slen = 0;
	double average;
	fp = gzdopen(fileno(stdin), "r");
	seq = kseq_init(fp);
	while (kseq_read(seq) >= 0)
		++n, slen += seq->seq.l;
	average = (double) slen / n;
	printf("%llu sequences\tAverage length: %4.3f\tTotal number of bases: %llu\n", n, average, slen);
	kseq_destroy(seq);
	gzclose(fp);
	return 0;
}
