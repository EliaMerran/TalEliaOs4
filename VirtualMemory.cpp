
#pragma once
#include "VirtualMemory.h"
#include "PhysicalMemoryOriginal.h"


void initFrame (word_t FrameIndex);
word_t findNewFrameIndex (uint64_t virtualAddress, uint64_t *farthestPage,uint64_t dontUseFrameIndex);
void findMaxDepthAndEmptyFrame (uint64_t frameIndex, uint64_t curDepth,
                                uint64_t *maxFrameUsed,
                                uint64_t *emptyFrameIndex, uint64_t dontUseFrameIndex);

void
findFarthestPage (uint64_t frameIndex, uint64_t currentAddress, uint64_t virtualAddress,
                  uint64_t *farthestPageAddress, uint64_t *farthestFrameIndex,
                  uint64_t *maxDistance, uint64_t curDepth);
void removeParentOfFarthest (uint64_t farthestPage);
void removeParentOfFrame(uint64_t frameIndex,uint64_t curDepth, uint64_t
deletedFrame);

word_t handlePageFault (uint64_t virtualAddress, int tableFromData,uint64_t dontUseFrameIndex)
{
  uint64_t farthestPage = -1;
  word_t FrameIndex = findNewFrameIndex (virtualAddress, &farthestPage,dontUseFrameIndex);

  if (farthestPage != -1)
    {
      //printf ("I AM EVICTED: %d, INDEX: %d\n",farthestPage<<OFFSET_WIDTH,
       //        FrameIndex);
      PMevict (FrameIndex, (farthestPage<<OFFSET_WIDTH)/PAGE_SIZE);
    }
  initFrame (FrameIndex);
  if (tableFromData == 1)
    {
//      printf ("I WILL RESTORE: %d, INDEX: %d\n",(virtualAddress)/PAGE_SIZE,FrameIndex);
      PMrestore (FrameIndex, (virtualAddress)/PAGE_SIZE);
    }

  return FrameIndex;
}

word_t findNewFrameIndex (uint64_t virtualAddress, uint64_t *farthestPage,
                          uint64_t dontUseFrameIndex)
{
  // step 1, 2 : find the max depth of the tree
  uint64_t maxFrameUsed = 0;
  uint64_t maxDistance = 0;
  uint64_t emptyFrameIndex = 0;
  uint64_t farthestFrameIndex = 0;
  findMaxDepthAndEmptyFrame (0, 0, &maxFrameUsed, &emptyFrameIndex,dontUseFrameIndex);
  // step 1: if there is an empty frame, return it
  if (emptyFrameIndex != 0)
    {
      removeParentOfFrame(0,0,emptyFrameIndex);
      return emptyFrameIndex;
    }
  // step 2: return the max depth + 1
  if (maxFrameUsed + 1 < NUM_FRAMES)
    {
      return maxFrameUsed + 1;
    }
  // step 3 : find the farthest page
  findFarthestPage (0, 0, virtualAddress >> OFFSET_WIDTH, farthestPage,
                    &farthestFrameIndex, &maxDistance, 0);
  removeParentOfFarthest ((*farthestPage) << OFFSET_WIDTH);
  return farthestFrameIndex;
}

void removeParentOfFrame(uint64_t frameIndex,uint64_t curDepth, uint64_t
deletedFrame)
{
  if (curDepth == TABLES_DEPTH)
    return;
  word_t value;
  bool emptyFrame = true;
  for (int j = 0; j < PAGE_SIZE; j++)
    {
      PMread (frameIndex * PAGE_SIZE + j, &value);
      if (value != 0)
        {
          if(value == deletedFrame)
            {
              PMwrite (frameIndex * PAGE_SIZE + j,0);
              return;
            }
          removeParentOfFrame (value, curDepth + 1,deletedFrame);
        }
    }
}

void removeParentOfFarthest (uint64_t farthestPage)
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
      PMread (frame_base + partitions[i], (word_t *) &frame_base);
      frame_base *= PAGE_SIZE;
    }

  // remove the parent pointer
  PMwrite (frame_base + partitions[1], 0);
}

void findMaxDepthAndEmptyFrame (uint64_t frameIndex, uint64_t curDepth,
                                uint64_t *maxFrameUsed,
                                uint64_t *emptyFrameIndex,
                                uint64_t dontUseFrameIndex)
{
  if (curDepth == TABLES_DEPTH)
    return;
  word_t value;
  bool emptyFrame = true;
  for (int j = 0; j < PAGE_SIZE; j++)
    {
      PMread (frameIndex * PAGE_SIZE + j, &value);
      if (value != 0)
        {
          emptyFrame = false;
          if (value > *maxFrameUsed)
            {
              *maxFrameUsed = value;
            }
          findMaxDepthAndEmptyFrame (value, curDepth + 1, maxFrameUsed,
                                     emptyFrameIndex, dontUseFrameIndex);
        }
    }
  if (emptyFrame && frameIndex != 0 && frameIndex != dontUseFrameIndex)
    {
      *emptyFrameIndex = frameIndex;
    }
}

uint64_t min (uint64_t  a, uint64_t  b)
{
  if (a < b)
    return a;
  return b;
}

int abs (int a)
{
  if (a < 0)
    return -a;
  return a;
}

void
findFarthestPage (uint64_t frameIndex, uint64_t currentAddress, uint64_t virtualAddress,
                  uint64_t *farthestPageAddress, uint64_t *farthestFrameIndex,
                  uint64_t *maxDistance, uint64_t curDepth)
{
  if (curDepth == TABLES_DEPTH)
    {
      uint64_t distance = min (
          NUM_PAGES - abs (virtualAddress - currentAddress),
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
  for (int j = 0; j < PAGE_SIZE; j++)
    {
      PMread (frameIndex * PAGE_SIZE + j, &value);
      if (value != 0)
        {
          uint64_t updatedAddress = currentAddress << OFFSET_WIDTH;
          updatedAddress += j;

          findFarthestPage (value, updatedAddress, virtualAddress, farthestPageAddress,
                            farthestFrameIndex, maxDistance, curDepth + 1);
        }
    }
}

void getPhysicalAddress (uint64_t virtualAddress, uint64_t *physicalAddress)
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
      PMread (address, &value);
      if (value == 0)
        {
          // page not found
          //Handle bring page from disk
          word_t newFrameIndex = handlePageFault (virtualAddressCopy, i,
                                                  frame_base/PAGE_SIZE);
          PMwrite (address, newFrameIndex);
//          printf ("virtual address: %d\n",virtualAddressCopy);
//          printf ("address: %d\n",address);
//          printf ("new Index Frame: %d\n",newFrameIndex);

          value = newFrameIndex;
        }
      frame_base = value * PAGE_SIZE;
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
void VMinitialize ()
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
int VMread (uint64_t virtualAddress, word_t *value)
{
  uint64_t physicalAddress;
  getPhysicalAddress (virtualAddress, &physicalAddress);
  // read the value from the physical address
  PMread (physicalAddress, value);
  return 1;
}

/* Writes a word to the given virtual address.
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMwrite (uint64_t virtualAddress, word_t value)
{
  uint64_t physicalAddress = 0;
  getPhysicalAddress (virtualAddress, &physicalAddress);
  // read the value from the physical address
//  printf ("WRITE data address:%d, Value: %d \n",physicalAddress,value);
  PMwrite (physicalAddress, value);
  return 1;
}
