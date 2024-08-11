comparisons = 0
recursions = -1
direct_right = 0
direct_left = 0

def string_comp(s1, s2):
    # String comparisons already work on Python, I will implement it anyway
    global comparisons
    comparisons += 1
    for i in range(min(len(s1), len(s2))):
        if s1[i] > s2[i]:
            return False
        elif s1[i] < s2[i]:
            return True
    if len(s1) > len(s2):
        return False
    return True

def merge_sort(arr):
    global recursions
    recursions += 1
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    
    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)
    

    return merge(left_half, right_half)
    
def merge(left, right):
    result = [] 
    i = j = 0 
    
    while i < len(left) and j < len(right):
        if string_comp(left[i], right[j]):
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    global direct_right
    global direct_left
    
    if i==0:
        direct_left += 1
    
    while i < len(left):
        result.append(left[i])
        i += 1

    if j==0:
        direct_right += 1
    
    while j < len(right):
        result.append(right[j])
        j += 1
    
    return result

import pandas as pd
import time
import random
import string

df = pd.DataFrame(columns=['Array Length', 'Max String Length', 'Execution Time (x10e-7)'])

def generate_random_string(length):
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

for array_length in range(1, 10000, 1000):
    for max_string_length in range(1, 10000, 1000):
        array = [generate_random_string(max_string_length) for _ in range(array_length)]
        # Flag: There is no variation in string length
        
        start_time = time.time()
        sorted_array = merge_sort(array)
        end_time = time.time()

        execution_time = end_time - start_time

        df.loc[len(df)] = [array_length, max_string_length, execution_time * 10**7]

pd.set_option('display.max_rows', None)
pd.set_option('display.max_columns', None)
pd.set_option('display.width', None)
pd.set_option('display.max_colwidth', None)

print(df)

# Perhaps implement an ML model to interpret the time complexity from the data?