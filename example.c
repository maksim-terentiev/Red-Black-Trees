#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"
#include "tree_print.h"

#define MAX_LEN 1000
#define CUR_LEN 100

#define input printf(">>> Input number (0, 1, 2, 3): ");
#define ID_ERROR fprintf(stderr, ">>> [ERROR]: invalid id value (%d not in [1; %d])!\n", curId, CUR_LEN);

int main() {
  int i, curId, id[CUR_LEN] = {66, 61, 70, 2, 49, 23, 97, 7, 93, 62, 43, 1, 37,
                                20, 87, 10, 31, 14, 38, 71, 4, 21, 65, 34, 22, 12,
                                91, 77, 5, 83, 26, 25, 35, 92, 90, 63, 96, 86, 74,
                                76, 30, 94, 64, 53, 72, 48, 60, 100, 55, 84, 33, 57,
                                47, 79, 67, 3, 98, 18, 59, 9, 45, 88, 95, 89, 58, 6,
                                32, 54, 51, 36, 39, 75, 29, 41, 52, 24, 73, 82, 99,
                                81, 16, 27, 50, 56, 13, 19, 40, 78, 11, 69, 42, 17,
                                80, 44, 85, 28, 8, 68, 46, 15
                              };
  long int phoneNumbers[MAX_LEN] = {79257496398, 79770197476, 79257936027, 79773006399,
                            79163460780, 79259181314, 79169803557, 79256827273,
                            79853065685, 79856082752, 79258121971, 79855859735,
                            79255866479, 79684632611, 79689314764, 79856002324,
                            79852244619, 79772295120, 79253897440, 79775625592,
                            79685706638, 79683254689, 79854431509, 79777416962,
                            79267080784, 79683153710, 79777285546, 79255283701,
                            79169645420, 79166969426, 79852746615, 79169867433,
                            79683066691, 79857469004, 79778000547, 79250675654,
                            79854092674, 79855618267, 79250354951, 79857043790,
                            79858455128, 79256994089, 79773122774, 79856366641,
                            79257538810, 79682431188, 79261786918, 79687859395,
                            79776708324, 79686513587, 79775557165, 79253281920,
                            79773920260, 79775080165, 79850580294, 79779891868,
                            79262236225, 79688290325, 79253010778, 79268720374,
                            79255830348, 79858255940, 79851994570, 79850016954,
                            79168413985, 79773308217, 79260469083, 79775686702,
                            79681950700, 79853176210, 79262204249, 79254566574,
                            79268082329, 79688618187, 79262195007, 79256653318,
                            79264173218, 79252186470, 79259524048, 79265253796,
                            79163844974, 79250228849, 79686663194, 79857856782,
                            79773155973, 79850028701, 79774407463, 79265285827,
                            79252720155, 79777759002, 79256337923, 79259557972,
                            79854601149, 79167535853, 79168235579, 79265394594,
                            79684606560, 79851577320, 79163477200, 79265594814
                          };
  node_t* node = NULL;

  for (i = 0; i < CUR_LEN; i++)
      uinsert(&node, id[i], phoneNumbers[id[i]-1]);

  printf("\n\n\t\t<<<<<{Test program v1.0}>>>>>");
  printf("\n\n>>> There are %d subscribers in this phone book", CUR_LEN);
  printf("Input subscriber id (1 - %d): ", MAX_LEN);
  scanf("%d", &curId);

  if (curId > MAX_LEN || curId < 1) {ID_ERROR exit(-1);}

  node_t *find=tree_lookup(node, curId);
  if (find == NULL) printf(">>> Subscriber with id = %d was not found. \n", curId);
  else printf(">>> Subscriber with id = %d has been found.\n\
>>> His phone number: +7 (%ld) %ld-%ld-%ld.\n\n\n", curId, \
  (find->value / 10000000) % 1000, (find->value % 10000000) / 10000,\
  (find->value % 10000) / 100, (find->value % 100));

  //print_tree(node);
  //printf("\n"); // for terminal flushing
  //show_tree(node);
  free_tree(node);
  
  return  0;
}
