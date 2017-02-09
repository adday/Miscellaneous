# task: find 100 largest numbers in a continuous stream of numbers and
#       print them (unsorted) at the termination of the stream

# assumptions: -numbers are floating point numbers from the set of real numbers
#              -end of stream is denoted by non-numeric character

# start time 4:50PM
# end time: 5:28PM

from heapq import heappushpop
import math

def isfloat(value):
  try:
    float(value)
    return True
  except ValueError:
    return False
	
number = input() # obtain first potential number from stdin
largest = [] # list to store largest 100 numbers
minimum = float("infinity") # initialize minimum to maximum possible value
while(isfloat(number)): 
	number = float(number) # cast string to float
	if(len(largest)<100): # first 100 numbers automatically go into largest
		minimum = min(minimum, number) # track smallest number in largest
		largest.append(number)
	else:
		if(number > minimum): # then number is larger than a number in largest
			heappushpop(largest, number) # replace smallest number in largest
			minimum = largest[0] # track smallest number in largest
	number = input()  # obtain next potential number from stdin
print(largest) # print list of 100 largest numbers

# analysis: O(N), where N is the size of the stream
# explanation: - largest is kept to a fixed size so heappushpop is O(1)
#              - appends into largest are O(1)
#              - the above are performed for at most n numbers, giving O(N)