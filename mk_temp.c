#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <gnumake.h>


int plugin_is_GPL_compatible;

char *
gen_tmpfile(const char *nm, int argc, char **argv)
{
  int fd;

  /* Compute the size of the filename and allocate space for it.  */
  int len = strlen (argv[0]) + 6 + 1;
  char *buf = gmk_alloc (len);

  strcpy (buf, argv[0]);
  strcat (buf, "XXXXXX");

  fd = mkstemp(buf);
  if (fd >= 0)
    {
      /* Don't leak the file descriptor.  */
      close (fd);
      return buf;
    }

  /* Failure.  */
  fprintf (stderr, "mkstemp(%s) failed: %s\n", buf, strerror (errno));
  gmk_free (buf);
  return NULL;
}

int
mk_temp_gmk_setup ()
{
  /* Register the function with make name "mk-temp".  */
  gmk_add_function ("mk-temp", gen_tmpfile, 1, 1, 1);
  return 1;
}
