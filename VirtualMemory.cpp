//
// Created by suchetzky on 6/11/23.
//
#pragma once
#include "VirtualMemory.h"
#include "PhysicalMemory.h"

// TODO : Remove io stream !

void getTablesIndex(uint64_t virtualAddress, uint64_t** partitions, int num_partitions)
{

}

/*
 * Initialize the virtual memory.
 */
void VMinitialize()
{

}

/* Reads a word from the given virtual address
 * and puts its content in *value.
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMread(uint64_t virtualAddress, word_t* value)
{
  int num_partitions = TABLES_DEPTH + 1;
  uint64_t partitions[num_partitions];
  // split the virtual address into partitions of OFFSET_WIDTH bits
  uint64_t mask = (1 << OFFSET_WIDTH) - 1;
  for (int i = 0; i < num_partitions; i++)
    {
      partitions[i] = virtualAddress & mask;
      virtualAddress >>= OFFSET_WIDTH;
    }
    // get the physical address of the page table
    uint64_t frame_base = 0;
    for (int i = 0; i < num_partitions - 1; ++i)
    {
      // cast frame_base to word_t* to use PMread
      PMread(frame_base + partitions[i], (word_t*) &frame_base);
    }
    // get the physical address of the page
    uint64_t physical_address = frame_base + partitions[num_partitions - 1];
    // read the value from the physical address
    PMread(physical_address, value);
    return 1;
}




/* Writes a word to the given virtual address.
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMwrite(uint64_t virtualAddress, word_t value)
{

}
