#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(void)
{
	gzFile fp;
	kseq_t *seq;
	int n = 0, slen = 0, qlen = 0;
	fp = gzdopen(fileno(stdin), "r");
	seq = kseq_init(fp);
	while (kseq_read(seq) >= 0)
		printf("%s\t%s\t%s\t%s\n", seq->name.s, seq->comment.s, seq->seq.s, seq->qual.s);
	kseq_destroy(seq);
	gzclose(fp);
	return 0;
}
