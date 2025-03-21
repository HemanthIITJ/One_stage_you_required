# Linear_search:int=0
# Binary_search:int=1
# Bubble_sort:int=2
# selection_sort:int=3
# insertion_sort:int=4
# quick_sort:int=5
#


def quick_sort(arr):

    def _quick_sort(low, high):
        if low < high:
            pi=partition(low, high)
            _quick_sort(low,pi-1)
            _quick_sort(pi+1,high)
    
    def partition(low, high):
        pivot=arr[high]
        i=low-1
        for j in range(low, high):
            if arr[j]<=pivot:
                i+=1
                arr[i],arr[j]=arr[j],arr[i]
        arr[i+1], arr[high]=arr[high], arr[i+1]
        return i+1
    _quick_sort(0,len(arr)-1)
    return arr

def test_quick_sort():
    import random
    
    list_of_elements=[random.randint(1,10) for i in range(10)]   
    print("Quick sort:", quick_sort(list_of_elements))



if __name__=="__main__":
    for i in range(10):

        test_quick_sort()