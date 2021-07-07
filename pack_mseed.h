#ifndef PACK_MSEED_H
#define PACK_MSEED_H

int pack_miniseed (void *data, const char *station_id,
                   int recore_length, uint8_t encoding,
                   int byteorder, uint8_t pubversion,
                   const char *starttime, double samplig_rate,
                   int num_samples,
                   const char *outfile);

#endif
