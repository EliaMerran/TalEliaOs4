//
// Created by suchetzky on 6/11/23.
//
#pragma once
#include "VirtualMemory.h"
#include "PhysicalMemory.h"

// TODO : Remove io stream !

void initFrame (word_t FrameIndex);
word_t findFrameToEvict ();
void findMaxDepth (int i, int *p_int);
word_t handlePageFault(uint64_t virtualAddress)
{
  word_t FrameIndex = findFrameToEvict();
  // evict page from frame
  PMrestore (FrameIndex, virtualAddress >> OFFSET_WIDTH);
}
word_t findFrameToEvict ()
{
  // step 1 : check if there is an empty frame
  word_t value;
  bool isFrameEmpty;
  for (int i = 1; i < NUM_FRAMES; i++)
    {
      isFrameEmpty = true;
      for (int j = 0; j < PAGE_SIZE; ++j)
        {
          PMread (i * PAGE_SIZE + j, &value);
          if (value != 0)
            {
              isFrameEmpty = false;
              break;
            }
        }
      if (isFrameEmpty)
        {
          return i;
        }
    }

  // step 2 : find the max depth of the tree
  int maxDepth = 0;
  findMaxDepth (0, &maxDepth);
  if (maxDepth + 1 < NUM_FRAMES)
    {
      return maxDepth + 1;
    }
  // step 3 :
}
void findMaxDepth (int frameIndex, int *depth)
{
  if (frameIndex == TABLES_DEPTH)
    return;
  word_t value;
  for (int j = 0; j < PAGE_SIZE; ++j)
    {
      PMread (frameIndex * PAGE_SIZE + j, &value);
      if (value != 0)
        {
          if (value > *depth)
            {
              *depth = value;
            }
          findMaxDepth (value, depth);
        }
    }
}

void getPhysicalAddress(uint64_t virtualAddress, uint64_t *physicalAddress)
{
  int num_partitions = TABLES_DEPTH + 1;
  uint64_t partitions[num_partitions];
  // split the virtual address into partitions of OFFSET_WIDTH bits
  uint64_t mask = (1 << OFFSET_WIDTH) - 1; // ..00001111
  for (int i = 0; i < num_partitions; i++)
    {
      partitions[i] = virtualAddress & mask;
      virtualAddress >>= OFFSET_WIDTH;
    }
  // get the physical address of the page table
  uint64_t frame_base = 0;
  for (int i = num_partitions - 1; i > 0; i--)
    {
      // cast frame_base to word_t* to use PMread
      uint64_t address = frame_base + partitions[i];
      PMread(address, (word_t*) &frame_base);
      if (frame_base == 0)
        {
          // page not found
          //Handle bring page from disk
          word_t newFrameIndex = handlePageFault (virtualAddress);
          PMwrite (address, newFrameIndex);
          frame_base = newFrameIndex;
          initFrame (newFrameIndex);

        }
      frame_base *= PAGE_SIZE;
    }
  // get the physical address of the page
  *physicalAddress = frame_base + partitions[0];
}
void initFrame (word_t FrameIndex)
{
  for (int i = 0; i < PAGE_SIZE; i++)
    {
      PMwrite (FrameIndex * PAGE_SIZE + i, 0);
    }
}

/*
 * Initialize the virtual memory.
 */
void VMinitialize()
{
  initFrame (0);
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
  uint64_t physicalAddress;
  getPhysicalAddress (virtualAddress, &physicalAddress);
  // read the value from the physical address
  PMread(physicalAddress, value);
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
  uint64_t physicalAddress;
  getPhysicalAddress (virtualAddress, &physicalAddress);
  // read the value from the physical address
  PMwrite(physicalAddress, value);
  return 1;
}
