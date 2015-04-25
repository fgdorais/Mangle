/* Copyright (C) 2008, 2010 F. G. Dorais
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * file COPYING for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. 
 */

#include <config.h>
#include <stdlib.h> /* for free */
#include <stdio.h>  /* for printf */
#include <string.h> /* for strlen */
#include <unistd.h> /* for getopt */

void help () {
  printf(PACKAGE_STRING" -- USAGE\n"
	 "\n"
	 " mangle [-cdoxXzs] [-w width] [-l char_prefix] [-L word_prefix]\n"
	 "        [-r char_suffix] [-R word_suffix] string ...\n"
	 "\n"
	 "  -c : character output (default)\n"
	 "  -d : decimal output\n"
	 "  -o : octal output\n"
	 "  -x : lower case hexadecimal output\n"
	 "  -X : upper case hexadecimal output\n"
	 "  -z : pad with zeros\n"
	 "  -s : pad with spaces\n"
	 "  -w : set minimum width to \"width\"\n"
	 "  -l : prepend \"char_prefix\" to each character output\n"
	 "  -L : prepend \"word_prefix\" to each string output\n"
	 "  -r : append \"char_suffix\" to each character output\n"
	 "  -R : append \"word_suffix\" to each string output\n");
  exit(EXIT_SUCCESS);
}


#define CHAR_FORMAT_LEN 64
#define FLAG_ZERO 1
#define FLAG_LINE 2
char char_format[CHAR_FORMAT_LEN] = {'\0', };
char *char_prefix = NULL;
char *char_suffix = NULL;
char *word_prefix = NULL;
char *word_suffix = NULL;
char base = 'c';
unsigned int prec = 1;
unsigned int flag = FLAG_LINE;

int main (int argc, char **argv) {
  int opt;
  int ind;
  
  while ((opt = getopt(argc, argv, "cdoxXnpszw:l:r:L:R:hv")) != -1) {
    switch (opt) {
    case 'c':
    case 'd':
    case 'o':
    case 'x':
    case 'X':
      base = opt;
      break;
    case 'w':
      prec = atoi(optarg) ? atoi(optarg) : prec;
    break;
    case 'n':
      flag |= FLAG_LINE;
      break;
    case 'p':
      flag &= ~FLAG_LINE;
      break;
    case 's':
      flag &= ~FLAG_ZERO;
      break;
    case 'z':
      flag |= FLAG_ZERO;
      break;
    case 'l':
      if (char_prefix != NULL) {
	free(char_prefix);
      }
      char_prefix = strdup(optarg);
      break;
    case 'r':
      if (char_suffix != NULL) {
	free(char_suffix);
      }
      char_suffix = strdup(optarg);
      break;
    case 'L':
      if (word_prefix != NULL) {
	free(word_prefix);
      }
      word_prefix = strdup(optarg);
      break;
    case 'R':
      if (word_suffix != NULL) {
	free(word_suffix);
      }
      word_suffix = strdup(optarg);
      break;
    case ':':
      fprintf(stderr, "Missing option argument!\n");
    case 'h':
      help();
    default:
      break;
    }
  }
  
  if (word_prefix == NULL) {
    word_prefix = "";
  }
  if (word_suffix == NULL) {
    word_suffix = "";
  }
  if (char_prefix == NULL) {
    char_prefix = "";
  }
  if (char_suffix == NULL) {
    char_suffix = "";
  }
  
  if (flag & FLAG_ZERO) {
    snprintf(char_format, CHAR_FORMAT_LEN, "%%s%%0%u%c%%s", prec, base);
  } else {
    snprintf(char_format, CHAR_FORMAT_LEN, "%%s%%%u%c%%s", prec, base);
  }
  
  for (ind=optind; ind<argc; ind++) {
    int len = strlen(argv[ind]);
    int i;
    
    printf("%s", word_prefix);
    
    for (i=0; i<len; i++) {
      printf(char_format, char_prefix, (unsigned int)(argv[ind][i]), char_suffix);
    }
    
    if (flag & FLAG_LINE) {
      printf("%s\n", word_suffix);
    }
  }
  
  return 0;
}
