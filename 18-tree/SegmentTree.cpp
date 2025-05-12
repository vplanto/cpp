#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 1e6;      // Maximum size of array
int segmentTree[2 * MAX_SIZE]; // Segment tree array

// Function to build the segment tree
void buildTree(int inputArray[], int arraySize) {
  // Copy array elements to the second half of segment tree array
  for (int i = 0; i < arraySize; i++)
    segmentTree[arraySize + i] = inputArray[i];

  // Build the segment tree by calculating minimum of children for each parent
  // node
  for (int i = arraySize - 1; i > 0; --i)
    segmentTree[i] = min(segmentTree[i << 1], segmentTree[i << 1 | 1]);
}

// Function to update a node of segment tree
void updateNode(int index, int value, int arraySize) {
  // Update the leaf node
  segmentTree[index + arraySize] = value;
  index = index + arraySize;

  // Traverse upwards to update parent nodes
  for (int i = index; i > 1; i >>= 1)
    segmentTree[i >> 1] = min(segmentTree[i], segmentTree[i ^ 1]);
}

// Function to get minimum value in a given range
int rangeMinimumQuery(int left, int right, int arraySize) {
  int minimumValue = INT_MAX;
  // Traverse the segment tree from left and right towards center
  for (left += arraySize, right += arraySize; left < right;
      left=left/2,right=right/2) {         
    if (left & 1)
      minimumValue = min(minimumValue, segmentTree[left++]);
        
    if (right & 1)
      minimumValue = min(minimumValue, segmentTree[--right]);
  }
  return minimumValue;
}

int main() {
  int inputArray[] = {1, 3, 2, 7, 9, 11};
  int arraySize = sizeof(inputArray) / sizeof(inputArray[0]);

  // Build segment tree from given array
  buildTree(inputArray, arraySize);

  // Print minimum value in inputArray[1..3]
  cout << rangeMinimumQuery(1, 3, arraySize) << endl;

  // Update: set inputArray[1] = 10 and update corresponding segment tree nodes
  updateNode(1, 10, arraySize);

  // Find minimum after the value is updated
  cout << rangeMinimumQuery(1, 3, arraySize) << endl;

  return 0;
}
