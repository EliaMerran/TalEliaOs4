#include "VirtualMemory.h"

#include <cstdio>
#include <cassert>

#include <vector>
#include <iostream>
#include "PhysicalMemoryOriginal.h"
//void print_tree (uint64_t frame, int depth)
//{
//  std::vector<word_t> values;
//  word_t val = 0;
//  std::cout << "***FRAME " << frame << " is leaf: " << ((depth == TABLES_DEPTH)?"yes":"no") << "***\n";
//  for (int i = 0; i < PAGE_SIZE; ++i)
//    {
//      PMread ((PAGE_SIZE * frame) + i, &val);
//      std::cout << " " << val << " ";
//      values.push_back (val);
//    }
//  std::cout << std::endl;
//  for (const auto &value : values)
//    {
//      if (value != 0 && depth != TABLES_DEPTH)
//        {
//          print_tree (value, depth + 1);
//        }
//    }
//}
//
//int main(int argc, char **argv) {
//    VMinitialize();
//    // print NUM_FRAMES constant
//    printf("NUM_FRAMES: %d\n", NUM_FRAMES);
//
////  printf ("%d\n",TABLES_DEPTH);
////  VMwrite(1 , 2);
////  VMwrite(6, 12);
////  VMwrite(6, 12);
////  word_t value;
////  VMread(1, &value);
////  printf ("Value: %d\n",value);
//
//  for (uint64_t i = 0; i < (2 * NUM_FRAMES); ++i) {
//        printf("writing to %llu\n", (long long int) i);
//        VMwrite(5 * i * PAGE_SIZE, i);
//    }
//
//    for (uint64_t i = 0; i < (2 * NUM_FRAMES); ++i) {
//        word_t value;
//        VMread(5 * i * PAGE_SIZE, &value);
//        printf("reading from %llu %d\n", (long long int) i, value);
//        assert(uint64_t(value) == i);
//    }
//    printf("success\n");
//
//    return 0;
//}


// YARRA




word_t ram_init[16] = {0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1};
word_t ram_page_14[16] = {1, 0, 0, 2, 0, 3, 4, 0, -1, 3, -1, -1, -1, -1, -1,
                          -1};
word_t ram_page_16[16] = {1, 0, 5, 2, 0, 3, 4, 0, -1, 3, 0, 6, 0, 7, -1, -1};
word_t ram_page_27[16] = {1, 4, 5, 0, 0, 7, 0, 2, 0, 3, 0, 6, 0, 0, -1, -1};
word_t ram_a[16] = {1, 4, 5, 0, 6, 7, 0, 2, 0, 3, 0, 0, 0, 5, -1, -1};


void print_error(word_t *ram, word_t *value)
{
  printf("ERROR\nRAM should be: \n");
  for (int i = 0; i < 16; ++i)
    {
      if (ram[i] != -1){
          printf("%d, ", int(ram[i]));
        }
      else{
          printf("garbage, ");
        }

    }
  printf("\nbut your RAM is: \n");
  for (int i = 0; i < 16; ++i)
    {
      printf("%d, ", int(value[i]));
    }
  printf("\n....\n");

}

bool check_ram (word_t *ram)
{
  word_t value[16];
  for (int i = 0; i < 16; ++i)
    {
      PMread (i, value + i);
    }
  for (int i = 0; i < 16; ++i)
    {
      if (ram[i] != -1 and value[i] != ram[i])
        {
          print_error(ram, value);
          return false;
        }
    }
  return true;
}

int main (int argc, char **argv)
{
  word_t virtual_value, physical_value;

  // checks RAM after init
  printf("start init\n");
  VMinitialize ();
  assert(check_ram (ram_init));
  printf("passed init\n");
  printf("....\n");


  // finding unused frame by max_page
  // page 3-14 in Algorithm Example pdf
  printf("start first test\n");
  VMwrite (13, 3);
  VMread (13, &virtual_value);
  PMread ((uint64_t) 9, &physical_value);
  assert(check_ram (ram_page_14));
  assert(virtual_value == 3);
  assert(virtual_value == physical_value);
  printf("passed first test\n");
  printf("....\n");


  // finding frame by max_page
  // page 15-16 in Algorithm Example pdf
  printf("start second test\n");
  VMread (6, &virtual_value);
  PMread ((uint64_t) 14, &physical_value);
  assert(check_ram (ram_page_16));
  assert(virtual_value == physical_value);
  printf("passed second test\n");
  printf("....\n");

  // finding frame by evicting
  // page 17 - 27 in Algorithm Example pdf
  printf("start third test\n");
  VMread (31, &virtual_value);
  PMread ((uint64_t) 15, &physical_value);
  assert(check_ram (ram_page_27));
  assert(virtual_value == physical_value);
  printf("passed third test\n");
  printf("....\n");

  // finding empty table
  printf("start fourth test\n");
  VMwrite (29, 5);
  VMread (29, &virtual_value);
  PMread ((uint64_t) 13, &physical_value);
  assert(check_ram (ram_a));
  assert(virtual_value == 5);
  assert(virtual_value == physical_value);
  printf("passed fourth test\n");
  printf("....\n");

  printf("passed all tests!!\n");


  return 0;
}
