#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("The first argument should be a file path read from");
    exit(EXIT_FAILURE);
  }

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    exit(EXIT_FAILURE);
  }

  gchar **words;
  GHashTable *hash_map = g_hash_table_new(g_str_hash, g_str_equal);
  while ((read = getline(&line, &len, fp)) != -1) {
    words = g_strsplit(line, " ", -1);
    int i = 0;
    while (*(words + i) != NULL) {
      gchar *word = *(words + i);
      gpointer val = g_hash_table_lookup(hash_map, word);
      if (val == NULL) {
        g_hash_table_insert(hash_map, word, 1);
      } else {
        g_hash_table_insert(hash_map, word, val + 1);
      }
      i += 1;
    }
  }

  fclose(fp);
  free(line);

  GHashTableIter iter;
  int *value;
  char **key;
  g_hash_table_iter_init(&iter, hash_map);
  while (g_hash_table_iter_next(&iter, (gpointer)&key, (gpointer)&value)) {
    printf("%s %d\n", key, value);
  }

  g_strfreev(words);
  g_hash_table_destroy(hash_map);

  exit(EXIT_SUCCESS);
}
