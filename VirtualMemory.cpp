//
// Created by suchetzky on 6/11/23.
//
#pragma once
#include "VirtualMemory.h"
#include "PhysicalMemory.h"

// TODO : Remove io stream !

void initFrame (word_t FrameIndex);
word_t findFrameToEvict (uint64_t virtualAddress, uint64_t *farthestPage);
void findMaxDepthAndEmptyFrame (uint64_t frameIndex, uint64_t *depth, uint64_t *emptyFrameIndex);
void findFarthestPage(uint64_t frameIndex, uint64_t currentAddress, uint64_t virtualAddress,
                      uint64_t *farthestPageAddress, uint64_t * farthestFrameIndex,
                      uint64_t *maxDistance);

void removeParentPointer (uint64_t farthestPage);
word_t handlePageFault(uint64_t virtualAddress)
{
  uint64_t farthestPage;
  word_t FrameIndex = findFrameToEvict(virtualAddress, &farthestPage);
  if (farthestPage != 0)
    {
      PMevict(FrameIndex, farthestPage);
    }
  PMrestore (FrameIndex, virtualAddress >> OFFSET_WIDTH);
}
word_t findFrameToEvict (uint64_t virtualAddress, uint64_t *farthestPage)
{
  // step 1, 2 : find the max depth of the tree
  uint64_t maxDepth = 0;
  uint64_t maxDistance = 0;
  uint64_t emptyFrameIndex = 0;
  uint64_t farthestFrameIndex = 0;
  *farthestPage = 0;
  findMaxDepthAndEmptyFrame (0, &maxDepth, &emptyFrameIndex);
  // step 1: if there is an empty frame, return it
  if (emptyFrameIndex != 0)
    {
      return emptyFrameIndex;
    }
  // step 2: return the max depth + 1
  if (maxDepth + 1 < NUM_FRAMES)
    {
      return maxDepth + 1;
    }
  // step 3 : find the farthest page
  findFarthestPage(0, 0, virtualAddress >> OFFSET_WIDTH, farthestPage,
                   &farthestFrameIndex, &maxDistance);
  removeParentPointer(*farthestPage);
  return farthestFrameIndex;
}
void removeParentPointer (uint64_t farthestPage)
{
  int num_partitions = TABLES_DEPTH + 1;
  uint64_t partitions[num_partitions];
  // split the virtual address into partitions of OFFSET_WIDTH bits
  uint64_t mask = (1 << OFFSET_WIDTH) - 1; // ..00001111
  for (int i = 0; i < num_partitions; i++)
    {
      partitions[i] = farthestPage & mask;
      farthestPage >>= OFFSET_WIDTH;
    }
  // get the physical address of the page table
  uint64_t frame_base = 0;
  for (int i = num_partitions - 1; i > 1; i--)
    {
      // cast frame_base to word_t* to use PMread
      PMread(frame_base + partitions[i], (word_t*) &frame_base);
      frame_base *= PAGE_SIZE;
    }

  // remove the parent pointer
  PMwrite(frame_base + partitions[1], 0);
}

void findMaxDepthAndEmptyFrame (uint64_t frameIndex, uint64_t *depth,
                                uint64_t *emptyFrameIndex)
{
  if (frameIndex == TABLES_DEPTH)
    return;
  word_t value;
  bool emptyFrame = true;
  for (int j = 0; j < PAGE_SIZE; ++j)
    {
      PMread (frameIndex * PAGE_SIZE + j, &value);
      if (value != 0)
        {
          emptyFrame = false;
          if (value > *depth)
            {
              *depth = value;
            }
          findMaxDepthAndEmptyFrame (value, depth, emptyFrameIndex);
        }
    }
  if (emptyFrame && frameIndex != 0)
    {
      *emptyFrameIndex = frameIndex;
    }
}

uint64_t min(uint64_t a, uint64_t b)
{
  if (a < b)
    return a;
  return b;
}
uint64_t abs(uint64_t a)
{
  if (a < 0)
    return -a;
  return a;
}

void findFarthestPage(uint64_t frameIndex, uint64_t currentAddress, uint64_t virtualAddress,
                      uint64_t *farthestPageAddress, uint64_t * farthestFrameIndex,
                      uint64_t *maxDistance)
{
  if (frameIndex == TABLES_DEPTH)
    {
      uint64_t distance = min (NUM_PAGES - abs (virtualAddress - currentAddress),
                      abs (virtualAddress - currentAddress));
     if (distance > *maxDistance)
       {
         *maxDistance = distance;
         *farthestPageAddress = currentAddress;
         *farthestFrameIndex = frameIndex;
       }
      return;
    }

  word_t value;
  for (int j = 0; j < PAGE_SIZE; ++j)
    {
      PMread (frameIndex * PAGE_SIZE + j, &value);
      if (value != 0)
        {
          currentAddress <<= OFFSET_WIDTH;
          currentAddress += j;
          findFarthestPage(value, currentAddress, virtualAddress, farthestPageAddress,
                           farthestFrameIndex, maxDistance);
        }
    }
}

void getPhysicalAddress(uint64_t virtualAddress, uint64_t *physicalAddress)
{
  uint64_t virtualAddressCopy = virtualAddress;
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
      word_t value;
      PMread(address, (word_t*) &value);
      if (value == 0)
        {
          // page not found
          //Handle bring page from disk
          word_t newFrameIndex = handlePageFault (virtualAddressCopy);
          PMwrite (address, newFrameIndex);
          value = newFrameIndex;
          initFrame (newFrameIndex);

        }
      frame_base = value * PAGE_SIZE;
    }
  // get the physical address of the page
  *physicalAddress = frame_base + partitions[0];
}


//void getPhysicalAddress(uint64_t virtualAddress, uint64_t *physicalAddress)
//{
//  int num_partitions = TABLES_DEPTH + 1;
//  uint64_t partitions[num_partitions];
//  // split the virtual address into partitions of OFFSET_WIDTH bits
//  uint64_t mask = (1 << OFFSET_WIDTH) - 1; // ..00001111
//  for (int i = 0; i < num_partitions; i++)
//    {
//      partitions[i] = virtualAddress & mask;
//      virtualAddress >>= OFFSET_WIDTH;
//    }
//  // get the physical address of the page table
//  uint64_t frame_base = 0;
//  for (int i = num_partitions - 1; i > 0; i--)
//    {
//      // cast frame_base to word_t* to use PMread
//      uint64_t address = frame_base + partitions[i];
//      PMread(address, (word_t*) &frame_base);
//      if (frame_base == 0)
//        {
//          // page not found
//          //Handle bring page from disk
//          word_t newFrameIndex = handlePageFault (virtualAddress);
//          PMwrite (address, newFrameIndex);
//          frame_base = newFrameIndex;
//          initFrame (newFrameIndex);
//
//        }
//      frame_base *= PAGE_SIZE;
//    }
//  // get the physical address of the page
//  *physicalAddress = frame_base + partitions[0];
//}
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
  uint64_t physicalAddress = 0;
  getPhysicalAddress (virtualAddress, &physicalAddress);
  // read the value from the physical address
  PMwrite(physicalAddress, value);
  return 1;
}
