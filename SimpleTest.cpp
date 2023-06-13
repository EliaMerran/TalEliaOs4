#include "VirtualMemory.h"

#include <cstdio>
#include <cassert>

#include <vector>
#include <iostream>
#include "PhysicalMemory.h"
void print_tree (uint64_t frame, int depth)
{
  std::vector<word_t> values;
  word_t val = 0;
  std::cout << "***FRAME " << frame << " is leaf: " << ((depth == TABLES_DEPTH)?"yes":"no") << "***\n";
  for (int i = 0; i < PAGE_SIZE; ++i)
    {
      PMread ((PAGE_SIZE * frame) + i, &val);
      std::cout << " " << val << " ";
      values.push_back (val);
    }
  std::cout << std::endl;
  for (const auto &value : values)
    {
      if (value != 0 && depth != TABLES_DEPTH)
        {
          print_tree (value, depth + 1);
        }
    }
}

int main(int argc, char **argv) {
    VMinitialize();
    // print NUM_FRAMES constant
    printf("NUM_FRAMES: %d\n", NUM_FRAMES);

  printf ("%d\n",TABLES_DEPTH);
  VMwrite(1 , 2);
  VMwrite(6, 12);
  VMwrite(6, 12);
  word_t value;
  VMread(1, &value);
  printf ("Value: %d\n",value);
//
//  for (uint64_t i = 0; i < (2 * NUM_FRAMES); ++i) {
//        printf("writing to %llu\n", (long long int) i);
//        VMwrite(5 * i * PAGE_SIZE, i);
//    }

//    for (uint64_t i = 0; i < (2 * NUM_FRAMES); ++i) {
//        word_t value;
//        VMread(5 * i * PAGE_SIZE, &value);
//        printf("reading from %llu %d\n", (long long int) i, value);
//        assert(uint64_t(value) == i);
//    }
    printf("success\n");

    return 0;
}
