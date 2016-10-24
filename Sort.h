#if !defined (SORT_H)
#define SORT_H

template < class T >
class Sort
{
   private: 
      static void _selectionSort(T** items, int numItems, int (*compare) (T* one, T* two));
      static void _mergeSort(T** items, int first, int last, int (*compare) (T* one, T* two));
      static void merge(T** items, int first, int mid, int last, int (*compare) (T* one, T* two));
      static void choosePivot(T** items, int first, int last);
      static int partition(T** items, int first, int last, int (*compare) (T* one, T* two));
      static void _quickSort(T** items, int first, int last, int (*compare) (T* one, T* two));
      static void _insertionSort(T** items, int numItems, int (*compare) (T* one, T* two));
      static int insertLocation(T** items, T* item, int last, int (*compare) (T* one, T* two));
      static void _insertionBinarySort(T** items, int numItems, int (*compare) (T* one, T* two));

      static int linearSearch(T** items, int numItems, T* item, int index, int (*compare) (T* one, T* two));
      static int binarySearch(T** items, int numItems, T* item, int first, int last, int (*compare) (T* one, T* two));

   public:
      static T** selectionSort(T** items, int numItems, int (*compare) (T* one, T* two));
      static T** insertionSort(T** items, int numItems, int (*compare) (T* one, T* two));
      static T** mergeSort(T** items, int numItems, int (*compare) (T* one, T* two));
      static T** quickSort(T** items, int numItems, int (*compare) (T* one, T* two));
      static T** insertionBinarySort(T** items, int numItems, int (*compare) (T* one, T* two));

      static int linearSearch(T** items, int numItems, T* item, int (*compare) (T* one, T* two));
      static int binarySearch(T** items, int numItems, T* item, int (*compare) (T* one, T* two));
};

template < class T >
T** Sort<T>::quickSort(T** items, int numItems, int (*compare) (T* one, T* two))
{
   //DO THIS
   //create a new array that will be sorted and returned
   //this is in case the original, unsorted array is also needed
	T** quick_array = new T*[numItems];
	
	for (int i = 0; i < numItems; i++)
	{
		quick_array[i] = items[i];
	}

	_quickSort(quick_array, 0, numItems - 1, compare);
	
	return quick_array;

}

template < class T >
void Sort<T>::_quickSort(T** items, int first, int last, int (*compare) (T* one, T* two))
{
   int pivotIndex;

   //DO THIS
   //make the necessary partition and recursive calls for quick sort
   if (first < last)
   {
		pivotIndex = partition(items, first, last, compare); //find the pivot position
		
		_quickSort(items, first, pivotIndex - 1, compare);   //quick sort left subarray
		_quickSort(items, pivotIndex + 1, last, compare);	 //quick sort right subarray

   }  
}  

template < class T >
int Sort<T>::partition(T** items, int first, int last, int (*compare) (T* one, T* two))
{
   //DO THIS
   //complete the partition method (Lomuto partition)

   //temp is used to swap elements in the array
   T* temp; 

   //initially, choosePivot does nothing           
   choosePivot(items, first, last);		//finds pivot and swaps the item at the pivot with first and item at first with the mid
	
	int piv = first;         	//the pivot index
	int _last = first;			//the _last index
	int curr_ndx = first + 1;   //the current index
	
	//goes through until the last index has been dealt with
	while(curr_ndx <= last)
	{
		int comp = (*compare) (items[curr_ndx], items[piv]);  //compares the current item with the pivot item
		
		//
		if(comp < 0)
		{
			_last++;							//increment last index
			temp = items[curr_ndx];				//temp holds item at current index
			items[curr_ndx] = items[_last];		//item at current index is the item at last index
			items[_last] = temp;				//item at last index is the item at current index
		}
		curr_ndx++;								//increment the current index
	}

	temp = items[piv];				//temp is the item at pivot index
	items[piv] = items[_last];		//item at pivot index is the item at last index
	items[_last] = temp;			//item at last index is the item at pivot index
	
	return _last;					//returns index the pivot is in
}

template < class T >
void Sort<T>::choosePivot(T** items, int first, int last)
{
   //DO THIS
   //find a better item to be the partition than simply using the item in the first index
   //you will need to swap
	int mid_ndx = ((first + (last - first)) / 2);  //calculates median
	T* temp_item = items[mid_ndx];                 //copies item to temp holder
	items[mid_ndx] = items[first];				   //middle of the array is the first item
	items[first] = temp_array;					   //first items in array is the median
}

//no work below this point
template < class T >
int Sort<T>::linearSearch(T** items, int numItems, T* item, int (*compare) (T* one, T* two))
{
   return linearSearch(items, numItems, item, 0, compare);
}

template < class T >
int Sort<T>::linearSearch(T** items, int numItems, T* item, int loc, int (*compare) (T* one, T* two))
{
   //we are using a special return type as the cases below are not exceptional
   if (loc == numItems)  //base case end of array
   {
      return -1;  //item not in array (base case #1)
   }

   int index;
   int comp = (*compare) (item, items[loc]);
   if (comp != 0)
   {
      index = linearSearch(items, numItems, item, loc + 1, compare);
   }
   else
   {
      index = loc;
   }

   return index;
}

template < class T >
int Sort<T>::binarySearch(T** items, int numItems, T* item, int (*compare) (T* one, T* two))
{
   return binarySearch(items, numItems, item, 0, numItems - 1, compare);
}

template < class T >
int Sort<T>::binarySearch(T** items, int numItems, T* item, int first, int last, int (*compare) (T* one, T* two)) 
{
   // reaches the base case much faster
   if (first > last) 
   {
      return -1;      // value not in original array (base case #1)
   } 

   int index;
   int mid = first + (last - first)/2;
   int comp = (*compare) (item, items[mid]);
   if (comp == 0) 
   { 
      index = mid;  // value found at search[mid] (base case #2)
   } 
   else if (comp < 0) 
   {
      //making these method calls is extra overhead that recursion requires
      //as it is easy and readable to write a binary search using a loop, that is the preferred implementation
      index = binarySearch(items, numItems, item, first, mid - 1, compare);
   } 
   else 
   {
      index = binarySearch(items, numItems, item, mid + 1, last, compare);
   } 
  
   return index;  //returns the index up through the chain
}

template < class T >
T** Sort<T>::selectionSort(T** items, int numItems, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[numItems];
   for (int i = 0; i < numItems; i++)
   {
      sorted[i] = items[i];
   }

   //passes the address of the function via compare
   _selectionSort(sorted, numItems, compare);
   return sorted;
}

template < class T >
void Sort<T>::_selectionSort(T** items, int numItems, int (*compare) (T* one, T* two))
{
   int min;
   T* item;

   for (int spot = 0; spot < numItems - 1; spot++)                   //n
   {
      min = spot;                                                    //n - 1
      for (int scan = spot + 1; scan < numItems; scan++)             //[n(n + 1)/2] - 1
      {
         //dereferences compare (calls the function)
         if ((*compare) (items[scan], items[min]) < 0)               //(n - 1)(n)/2
         {
            min = scan;                                              //worst case (n - 1)(n)/2
         }
      }

      // Swap the values
      item = items[min];                                             //3(n - 1)
      items[min] = items[spot];
      items[spot] = item;
   }
}

template < class T >
T** Sort<T>::mergeSort(T** items, int numItems, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[numItems];
   for (int i = 0; i < numItems; i++)
   {
      sorted[i] = items[i];
   }

   _mergeSort(sorted, 0, numItems - 1, compare);
   return sorted;
}

template < class T >
void Sort<T>::_mergeSort(T** items, int first, int last, int (*compare) (T* one, T* two))
{
   if (first < last) 
   {
      // sort each half
      int mid = first + (last - first)/2;  //(first + last)/2;   // index of midpoint

      // sort left half sort[first..mid]
      _mergeSort(items, first, mid, compare);

      // sort right half sort[mid + 1..last]   
      _mergeSort(items, mid + 1, last, compare);  
 
      // merge the two halves
      merge(items, first, mid, last, compare);
   } 
}  

template < class T >
void Sort<T>::merge(T** items, int first, int mid, int last, int (*compare) (T* one, T* two)) 
{
   //tempArray
   T** temp = new T*[last - first + 1];
    
   // initialize the local indexes to indicate the subarrays
   int first1 = first;    // beginning of first subarray
   int last1  = mid;      // end of first subarray
   int first2 = mid + 1;  // beginning of second subarray
   int last2  = last;     // end of second subarray

   // while both subarrays are not empty, copy the
   // smaller item into the temporary array
   int index = 0;                    

   while ((first1 <= last1) && (first2 <= last2)) 
   {
      if ((*compare) (items[first1], items[first2]) <= 0)  //careful here for stable sorting
      {
         temp[index] = items[first1];
         first1++;
      }
      else 
      {
         temp[index] = items[first2];
         first2++;
      }  

      index++;
   } 

   // finish off the nonempty subarray

   // finish off the first subarray, if necessary
   while (first1 <= last1) 
   {
      temp[index] = items[first1];
      first1++;
      index++;
   }  

   // finish off the second subarray, if necessary
   while (first2 <= last2)
   {
      temp[index] = items[first2];
      first2++;
      index++;
   }  

   // copy the result back into the original array
   for (index = 0; index <= last - first; index++) 
   {
      items[index + first] = temp[index];
   }

   delete[] temp;  
}  

template < class T >
T** Sort<T>::insertionSort(T** items, int numItems, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[numItems];
   for (int i = 0; i < numItems; i++)
   {
      sorted[i] = items[i];
   }

   _insertionSort(sorted, numItems, compare);
   return sorted;
}

template < class T >
void Sort<T>::_insertionSort(T** items, int numItems, int (*compare) (T* one, T* two))
{
   T* temp;
   int position;

   for (int spot = 1; spot < numItems; spot++)
   {
      temp = items[spot];
      position = spot;

      // shift larger values to the right
      while (position > 0 && (*compare) (items[position - 1], temp) > 0)
      {
         items[position] = items[position - 1];
         position--;
      }
            
      items[position] = temp;
   }
}

template < class T >
T** Sort<T>::insertionBinarySort(T** items, int numItems, int (*compare) (T* one, T* two))
{
   T** sorted = new T*[numItems];
   for (int i = 0; i < numItems; i++)
   {
      sorted[i] = items[i];
   }

   _insertionBinarySort(sorted, numItems, compare);
   return sorted;
}

template < class T >
void Sort<T>::_insertionBinarySort(T** items, int numItems, int (*compare) (T* one, T* two))
{
   T* temp;
   int position;

   for (int spot = 1; spot < numItems; spot++)
   {
      temp = items[spot];

      // shift larger values to the right
      position = insertLocation(items, temp, spot - 1, compare);  //binary search to minimize comparisons
      for(int i = spot; i > position; i--)
      {
         items[i] = items[i - 1];
      }
            
      items[position] = temp;
   }
}

template < class T >
int Sort<T>::insertLocation(T** items, T* item, int last, int (*compare) (T* one, T* two))
{
   //based on array indices
   int first = 0;
   int mid = first + (last - first)/2;

   while (first <= last)
   {
      int comp = ((*compare) (item, items[mid]));
      if (comp == 0)
      {
         break;
      }
      else if (comp < 0)
      {
         last = mid - 1;
         mid = first + (last - first)/2;
      }
      else 
      {
         first = mid + 1;
         mid = first + (last - first)/2;
      }
   }

   return mid;
}

#endif

