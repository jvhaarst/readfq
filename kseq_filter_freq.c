#include <stdbool.h>
#include <unistd.h>
#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(void)
{
    gzFile fp;
    kseq_t *seq;  
    bool verbose = false;
    double cutoff_low = 0.15;
    double cutoff_high = 0.40;
    int minimal_length = 1000;
    int width = 60;
    
    fp = gzdopen(fileno(stdin), "r");
    seq = kseq_init(fp);
    while (kseq_read(seq) >= 0){
        if (seq->seq.l > minimal_length ){
            unsigned long long a=0, c=0, g=0, t=0, n = 0, slen = 0, k = 0;
            double a_frac, c_frac, g_frac, t_frac, n_frac;
            int count[255] = {0};
            // Loop over sequence, and count bases
            // http://stackoverflow.com/questions/29845805/i-want-to-count-frequency-or-occurrence-of-a-every-letter-in-a-string-c-program
            for(k = 0;k < seq->seq.l;++k){ 
                char seqchar = seq->seq.s[k];
                count[seqchar] = count[seqchar] + 1;
            };
            slen = seq->seq.l;

            a = count['a'] + count['A'];
            c = count['c'] + count['C'];
            g = count['g'] + count['G'];
            t = count['t'] + count['T'];
            n = count['n'] + count['N'];

            a_frac = (double) a / slen;
            c_frac = (double) c / slen;
            g_frac = (double) g / slen;
            t_frac = (double) t / slen;
            n_frac = (double) n / slen;

            // Print info to stderr
            if (verbose){
                fprintf( stderr, "%llu\t", slen);
                fprintf( stderr, "%llu\t(%4.3f%%)\t", a, a_frac);
                fprintf( stderr, "%llu\t(%4.3f%%)\t", c, c_frac);
                fprintf( stderr, "%llu\t(%4.3f%%)\t", g, g_frac);
                fprintf( stderr, "%llu\t(%4.3f%%)\t", t, t_frac);
                fprintf( stderr, "%llu\t(%4.3f%%)\t", n, n_frac);
                fprintf( stderr, "\n");
            }
            // Check for skewed distribution
            if (
                a_frac > cutoff_low && a_frac < cutoff_high &&
                c_frac > cutoff_low && c_frac < cutoff_high &&
                g_frac > cutoff_low && g_frac < cutoff_high &&
                t_frac > cutoff_low && t_frac < cutoff_high 
            ){
                // Print FASTA formatted
                printf(">%s", seq->name.s);
                for (k = 0; k < seq->seq.l; k++){
                    if (k%width == 0) printf("\n");
                    printf("%c", seq->seq.s[k]);
                }
                printf("\n");
            }else{
                if (verbose) fprintf( stderr, ">%s\n", seq->name.s);
            }
        }else{
            if (verbose) fprintf( stderr, ">%s\n", seq->name.s);
        }
    }
    kseq_destroy(seq);
    gzclose(fp);
    return 0;
}
