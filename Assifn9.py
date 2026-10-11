user_input = input("Enter characters separated by spaces (e.g., y z m v): ")
arr = user_input.split() 
print("Your array is ", arr)

non = None

for i in range(len(arr)):
    if arr.count(arr[i]) == 1:
        non = arr[i]    
        break
     
print("First non repeating char ", non)

original_arr = list(arr)
for i in range(1, len(arr)):
    if original_arr[i] == original_arr[i-1]:
       arr[i] = '$'
    else:
        arr[i] = non
        
print("Final arr: ", arr)

