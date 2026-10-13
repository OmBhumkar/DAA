user_input = input("Enter characters separated by spaces (e.g., y z m v): ")
arr = user_input.split()
print("Your array is ", arr)

freq = {}
order = []
final_arr = []

for char in arr:
    if char in freq:
        freq[char] += 1
    else:
        freq[char] = 1
        order.append(char)

    current_non_repeating = '$'
    for c in order:
        if freq[c] == 1:
            current_non_repeating = c
            break  

    final_arr.append(current_non_repeating)

print("Final arr: ", final_arr)
