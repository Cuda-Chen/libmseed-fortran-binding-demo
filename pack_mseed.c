#include <stdio.h>
#include <stdlib.h>

#include "libmseed.h"

static void
print_stderr (const char *message)
{
  fprintf (stderr, "%s", message);
}

int
pack_miniseed (void *data, const char *station_id,
               int recore_length, uint8_t encoding,
               int byteorder, uint8_t pubversion,
               const char *starttime, double samplig_rate,
               int num_samples, const char *outfile)
{
  MS3Record *msr = NULL;
  char *cdata = NULL;
  float *fdata   = NULL;
  double *ddata  = NULL;
  int32_t *idata = NULL;
  uint8_t samplesize;
  uint32_t flags = 0;
  flag verbose   = 0;
  int idx;
  int rv;

  ms_loginit (print_stderr, NULL, print_stderr, NULL);

  if (!(msr = msr3_init (msr)))
  {
    fprintf (stderr, "Could not allocate MS3Record, out of memory?\n");
    return -1;
  }

  /* Set up record metadata */
  strcpy (msr->sid, station_id);
  msr->reclen     = recore_length;
  msr->pubversion = pubversion;
  msr->starttime  = ms_timestr2nstime (starttime);
  msr->samprate   = samplig_rate;
  msr->encoding   = encoding;

  if (encoding == DE_ASCII)
  {
    msr->numsamples  = strlen ((const char *)data);

    if (!(cdata = (char *)malloc (msr->numsamples * sizeof (char))))
    {
      fprintf (stderr, "Could not allocate buffer, out of memory?\n");
      return 1;
    }
    for (idx = 0; idx < msr->numsamples; idx++)
    {
      void *sptr = (char *)data + idx * samplesize;
      cdata[idx] = *(char *)sptr;
    }

    msr->datasamples = cdata;
    msr->sampletype  = 'a';
  }
  else if (encoding == DE_FLOAT32)
  {
    msr->numsamples = num_samples;

    if (!(fdata = (float *)malloc (msr->numsamples * sizeof (float))))
    {
      fprintf (stderr, "Could not allocate buffer, out of memory?\n");
      return 1;
    }
    for (idx = 0; idx < msr->numsamples; idx++)
    {
      void *sptr = (char *)data + idx * samplesize;
      fdata[idx] = *(float *)sptr;
    }
    msr->datasamples = fdata;
    msr->sampletype  = 'f';
  }
  else if (encoding == DE_FLOAT64)
  {
    msr->numsamples = num_samples;

    if (!(ddata = (double *)malloc (msr->numsamples * sizeof (double))))
    {
      fprintf (stderr, "Could not allocate buffer, out of memory?\n");
      return 1;
    }
    for (idx = 0; idx < msr->numsamples; idx++)
    {
      void *sptr = (char *)data + idx * samplesize;
      ddata[idx] = *(double *)sptr;
    }
    msr->datasamples = ddata;
    msr->sampletype  = 'd';
  }
  else if (encoding == DE_INT16)
  {
    msr->numsamples  = num_samples;

    if (!(idata = (int32_t *)malloc (msr->numsamples * sizeof (int32_t))))
    {
      fprintf (stderr, "Could not allocate buffer, out of memory?\n");
      return 1;
    }

    for (idx = 0; idx < msr->numsamples; idx++)
    {
      void *sptr = (char *)data + idx * samplesize;
      idata[idx] = *(int32_t *)sptr;
    }
    msr->datasamples = idata;
    msr->sampletype  = 'i';
  }
  else
  {
    msr->numsamples  = num_samples;

    if (!(idata = (int32_t *)malloc (msr->numsamples * sizeof (int32_t))))
    {
      fprintf (stderr, "Could not allocate buffer, out of memory?\n");
      return 1;
    }

    for (idx = 0; idx < msr->numsamples; idx++)
    {
      void *sptr = (char *)data + idx * samplesize;
      idata[idx] = *(int32_t *)sptr;
    }
    msr->datasamples = idata;
    msr->sampletype  = 'i';
  }

  msr->samplecnt = msr->numsamples;

  flags |= MSF_FLUSHDATA;

  rv = msr3_writemseed (msr, outfile, 1, flags, verbose);
  if (rv < 0)
  {
    ms_log (2, "Error (%d) writing miniSEED to %s\n", rv, outfile);
  }

  /* Clean up */
  if (msr->datasamples == data)
    msr->datasamples = NULL;
  msr3_free (&msr);
  if(cdata != NULL)
      free(cdata);
  if(fdata != NULL)
      free(fdata);
  if(ddata != NULL)
      free(ddata);
  if(idata != NULL)
      free(idata);

  return 0;
}
