# Linear_search:int=0
# Binary_search:int=1
# Bubble_sort:int=2
# selection_sort:int=3
# insertion_sort:int=4

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key=arr[i]
        j=i-1
        while j>=0 and arr[j]>key:
            arr[j+1]=arr[j]
            j-=1
        arr[j+1]=key
    return arr


import random
list_arr=[random.randint(1,100) for i in range(10)]
print("Original array:",list_arr)
print("Sorted array:",insertion_sort(list_arr))


