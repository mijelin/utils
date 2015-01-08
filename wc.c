/** Dupe of Unix 'wc' utility.
 *  Prints the number of lines, words, and bytes in files.
 *
 *  USAGE: ./wc [INPUTFILE] [OUTPUTFILE]
 *  where INPUTFILE and OUTPUTFILE default to stdin and stdout, if unspecified.
 */

#include <stdio.h>
#include <ctype.h>

/** Returns the number of digits in NUM. */
int
digits (int num)
{
  int digCount = 0;
  while (num != 0)
    {
      num /= 10;
      digCount++;
    }
  return digCount;
}

/** Formats and prints results to output file or standard output. */
void
results (FILE *ofile, FILE *infile, char *inname, int nlCount, int wCount, int cCount)
{
  int maxDigits;
  if (infile == stdin)
    {
      maxDigits = 7;
    }
  else
    {
      maxDigits = digits(cCount);
    }
    fprintf (ofile, "%*d %*d %*d %s\n", maxDigits, nlCount, maxDigits, wCount,
             maxDigits, cCount, inname);
    fclose (ofile);
}

/** Reports number of newlines, words, and bytes in INFILE to OFILE. */
void
wc (FILE *ofile, FILE *infile, char *inname)
{
    int nlCount = 0; int wCount = 0; int cCount = 0; int c; int prev = ' ';
    while ((c = fgetc (infile)) != EOF)
    {
      if (c == '\n')
        {
        nlCount += 1;
        if (!isspace(prev))
          wCount += 1;
        }
      else if (isspace(c) && !isspace(prev))
        {
            wCount += 1;
        }
    cCount += 1; prev = c;
    }

    if (nlCount == 0 && wCount != 0) // Correction for single-line cases
      {
        wCount += 1;
      }

    fclose (infile);
    results (ofile, infile, inname, nlCount, wCount, cCount);
}

/** Prints number of newlines characters, words, and bytes in specified file. */
int
main (int argc, char *argv[])
{
    FILE *input = stdin; FILE *output = stdout; char *inname = "";
    switch (argc)
      {
        case 1:
            break;
        case 2:
            input = fopen (argv[1], "r");
            inname = argv[1];
            break;
        case 3:
            input = fopen (argv[1], "r");
            output = fopen (argv[2], "w");
            inname = argv[1];
            break;
        default:
            fprintf (stderr, "USAGE: ./wc [INPUTFILE] [OUTPUT FILE]");
            return 1;
      }

    if (input == NULL)
      {
        fprintf (stderr, "ERROR: cannot read input file\n");
        return 1;
      }

    if (output == NULL)
      {
        fprintf (stderr, "ERROR: cannot write to output file\n");
        return 1;
      }

    wc (output, input, inname);
}
