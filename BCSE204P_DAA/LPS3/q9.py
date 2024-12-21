def merge_sort(arr, comparator):
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    
    left_half = merge_sort(left_half, comparator)
    right_half = merge_sort(right_half, comparator)
    

    return merge(left_half, right_half, comparator)
    
def merge(left, right, comparator):
    result = [] 
    i = j = 0 
    
    while i < len(left) and j < len(right):
        if comparator(left[i], right[j]):
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    while i < len(left):
        result.append(left[i])
        i += 1
    
    while j < len(right):
        result.append(right[j])
        j += 1
    
    return result

def main():
    points = [
        (1, 2),
        (2, 1),
        (1, 1),
        (2, 2),
        (3, 1),
        (3, 2),
        (1, 3),
        (2, 3),
        (3, 3)
    ]
    comparators = [
        lambda x, y: x[0] <= y[0],
        lambda x, y: x[1] <= y[1],
        lambda x, y: (x[0] + x[1]) >= (y[0] + y[1]),
    ]
    print("Points:")
    print(points)
    for comparator in comparators:
        points_copy = points.copy()
        print(f"Comparator: {comparator}")
        print(merge_sort(points_copy, comparator))

main()