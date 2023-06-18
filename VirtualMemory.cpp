
#pragma once

#include "VirtualMemory.h"
#include "PhysicalMemory.h"


void initFrame (uint64_t FrameIndex)
{
    for (int i = 0; i < PAGE_SIZE; ++i) {
        PMwrite(FrameIndex * PAGE_SIZE + i,0);
    }
}
uint64_t min (uint64_t  a, uint64_t  b);
uint64_t abs_diff (uint64_t a,  uint64_t b);
/**
 * Finds a new frame index to use, with priorities specified in pdf
 * @param virtualAddress virtual address to find a frame for
 * @param farthestPage return value for the farthest page
 * @param dontUseFrameIndex the frame index to not use
 * @return
 */
uint64_t findNewFrameIndex (uint64_t virtualAddress, uint64_t *farthestPage,
                            uint64_t dontUseFrameIndex);

/**
 * this function finds with DFS the current max frame index
 * @param frameIndex the current frame index
 * @param curDepth the current depth in the tree
 * @param maxFrameUsed the current max frame used
 * @param emptyFrameIndex the current empty frame index
 * @param dontUseFrameIndex the frame index to not use
 */
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
          if ((uint64_t) value > *maxFrameUsed)
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

/**
 * this function finds the farthest page from the given virtual address
 * @param frameIndex the current frame index
 * @param currentAddress the current address
 * @param virtualAddress  the virtual address to find the farthest page from
 * @param farthestPageAddress return value for the farthest page addresse
 * @param farthestFrameIndex return value for the farthest frame index
 * @param maxDistance pointer of max distance
 * @param curDepth the current depth in the tree
 */
void
findFarthestPage (uint64_t frameIndex, uint64_t currentAddress, uint64_t virtualAddress,
                  uint64_t *farthestPageAddress, uint64_t *farthestFrameIndex,
                  uint64_t *maxDistance, uint64_t curDepth)
{
  if (curDepth == TABLES_DEPTH)
    {
      uint64_t distance = min (
          NUM_PAGES - abs_diff ( virtualAddress ,currentAddress),
          abs_diff (virtualAddress,currentAddress));

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

/**
 * this function removes the parent pointer of the farthest page
 * @param farthestPage the farthest page
 */
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
/**
 * this function removes the parent pointer of the given frame
 * @param frameIndex frame index to remove the parent pointer of
 * @param curDepth the current depth in the tree
 * @param deletedFrame the frame to delete
 */
void removeParentOfFrame(uint64_t frameIndex,uint64_t curDepth, uint64_t
deletedFrame)
{
  if (curDepth == TABLES_DEPTH)
    return;
  word_t value;
  for (int j = 0; j < PAGE_SIZE; j++)
    {
      PMread (frameIndex * PAGE_SIZE + j, &value);
      if (value != 0)
        {
          if((uint64_t) value == deletedFrame)
            {
              PMwrite (frameIndex * PAGE_SIZE + j,0);
              return;
            }
          removeParentOfFrame (value, curDepth + 1,deletedFrame);
        }
    }
}

/**
 * this function checks if the given virtual address is valid
 * @param virtualAddress the virtual address to check
 * @return true if the address is valid, false otherwise
 */
bool firstCheck(uint64_t virtualAddress)
{
  if (virtualAddress >= VIRTUAL_MEMORY_SIZE)
    {
      return true;
    }
  return false;
}
/**
 * this function handles the page fault
 * @param virtualAddress the virtual address that caused the page fault
 * @param tableFromData 1 if the frame to fine is for a data page,
 * otherwise the frame is for a table
 * @param dontUseFrameIndex the frame index to not use, recently chosen frame
 * @return the frame index of the new frame
 */
uint64_t handlePageFault (uint64_t virtualAddress, int tableFromData,uint64_t dontUseFrameIndex)
{
  uint64_t farthestPage = 0;
  uint64_t FrameIndex = findNewFrameIndex (virtualAddress, &farthestPage,dontUseFrameIndex);
  if (tableFromData == 1)
    {
      PMrestore (FrameIndex, virtualAddress/PAGE_SIZE);
    } else
  {
      initFrame (FrameIndex);
  }

  return FrameIndex;
}

uint64_t min (uint64_t  a, uint64_t  b)
{
  if (a < b)
    return a;
  return b;
}

uint64_t abs_diff (uint64_t a,  uint64_t b)
{
    if (a > b)
    {
        return a-b;
    }
    return b-a;
}

/**
 * calculates the physical address of the given virtual address
 * @param virtualAddress the virtual address to calculate its physical address
 * @param physicalAddress return value for the physical address
 */
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
          auto newFrameIndex = (word_t) handlePageFault (virtualAddressCopy, i,
                                                  frame_base/PAGE_SIZE);
          PMwrite (address, newFrameIndex);
          value = newFrameIndex;
        }
      frame_base = value * PAGE_SIZE;
    }
  // get the physical address of the page
  *physicalAddress = frame_base + partitions[0];
}

void VMinitialize ()
{
  initFrame (0);
}


int VMread (uint64_t virtualAddress, word_t *value)
{
    if (firstCheck(virtualAddress))
    {
        return 0;
    }
    uint64_t physicalAddress;
  getPhysicalAddress (virtualAddress, &physicalAddress);
  // read the value from the physical address
  PMread (physicalAddress, value);
  return 1;
}

int VMwrite (uint64_t virtualAddress, word_t value)
{
   if (firstCheck(virtualAddress))
   {
       return 0;
   }
  uint64_t physicalAddress = 0;
  getPhysicalAddress (virtualAddress, &physicalAddress);
  // read the value from the physical address
  PMwrite (physicalAddress, value);
  return 1;
}

uint64_t findNewFrameIndex (uint64_t virtualAddress, uint64_t *farthestPage,
                            uint64_t dontUseFrameIndex)
{
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
    PMevict (farthestFrameIndex, ((*farthestPage)<<OFFSET_WIDTH)/PAGE_SIZE);
    return farthestFrameIndex;
}

