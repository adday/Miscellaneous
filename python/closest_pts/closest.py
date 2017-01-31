from time import time
import math
import random

'''
FORMATTING CONVENTION

The convention for formatting a list of points in this program is to use
a list of lists of pairs of floating-point values.  The first
element in each pair is the x coordinate of a point and the second
is its y coordinate.  There must be at least two points in a list.

Example:  [[3.2,5.8],[4.7,1.2]]
'''

'''
Read a set of points from a file.  
Prconditions:  The file consists of two floating-point values per 
  line, where the first gives the x coordinate of a point and the 
  second gives its y coordinate.
Postconditions:  the returned list is a list of the points, adhering
  to the formatting convention (above)
'''
def readPts(filename):
    fp = open(filename)
    Lines = [line for line in fp]
    L = [[float(i) for i in line.split()] for line in Lines]
    return L

'''
Merge of mergesort, for sorted lists of points.  
Preconditions:  S1 and S2 are two lists of lists of size two, adhering
  to the formatting convention (above).  In addition, coord is either 0 or 1.
  If it is 0, then the two lists must be sorted by x coordinate
  and if it is 1, they must be sorted by y coordinate.
Postconditions:  The returned list is the union of the two lists.
  If coord == 0, it is sorted by x coordinate and if coord == 1, it
  is sorted by y coordinate.
'''  
def mergePts(S1, S2, coord):
   i = 0
   j = 0
   result = []
   while i < len(S1) and j < len(S2):
	if S1[i][coord] < S2[j][coord]:
		result.append(S1[i])
		i += 1
	else:
		result.append(S2[j])
		j +=1
   result = result + S1[i:] + S2[j:]
   return result

'''
Mergesort for a list of points.
preconditions:  S is a set of points adhering to the formatting convention 
  (above), and coord is 0 or 1
postconditions:  if coord == 0, the returned list is the elements of S
  sorted by x coordinate, and if coord == 1, the returned list is the
  elements of S sorted by y coordinate.
'''
def msPts(S, coord):
    if len(S) < 2:
	return S
    else:
	mid = (len(S)-1)/2
	return mergePts(msPts(S[:mid+1],coord), msPts(S[mid+1:],coord),coord)

'''
This is an O(n^2) closest-pair algorithm.  (Using this as the base case
 prevents us from having to consider what answer to return if there
 is only one point in the list).  It should examine all pairwise 
 squared distances and pick the minimum squared distance found, as well 
 as a pair of points whose square of distance has this value.

 You can also apply it to large sets of points, to compare its running 
 time to what you wrote.  If your solution does not get dramatically 
 faster as the number of points gets large, you have messed up something
 in your analysis of your time bound.

 preconditions:  S is a set of points in two-space.
 postconditions:  S is sorted by y coordinate.
 The returned values are the square of the distance
 between the closest pair of points, and a list of two points
 adhering to the formatting convention (above), giving the closest
 pair, and a list of points in S sorted by y coordinate 

'''
def brute(S):
   min_dist = float('inf')
   for i in range(len(S)):
	for j in range(len(S)):
		if i == j: continue
		dist = distsq(S[i],S[j])
		if dist < min_dist:
			min_dist = dist 
			pts = [S[i],S[j]]	
   return min_dist, pts, msPts(S,1)


'''
Find the closest pair in S

Precondition:  S conforms to the formatting convention, and no two points
  have the same x coordinate
Postcondition:  A tuple has been returned whose first element is the min 
  distance squared, and whose second element is a list of two points.
'''
def closest(S):
    closest = closestAux(msPts(S,0))
    return closest[0],closest[1]
    

'''
preconditions:  X is the set of points in the plane, no
  two of which share the same x coordinate.  X is sorted by X coordinate.
postconditions:  
  The returned tuple is the square of the distance of 
  the closest pair, and a list of size two giving a closest pair,
  and a list of the points of X, sorted by y coordinate
'''
def closestAux(X):
   if len(X)<= 3:
	min_dist = float('inf')
   	for i in range(len(X)):
		for j in range(len(X)):
			if i == j: continue
			dist = distsq(X[i],X[j])
			if dist < min_dist:
				min_dist = dist 
				pts = [X[i],X[j]]	
   	return min_dist, pts, msPts(X,1)

   mid = (len(X)-1)/2
   #print X[mid]
   minL = closestAux(X[:mid+1]) 
   minR = closestAux(X[mid:])
  
   delta = min(math.sqrt(minL[0]), math.sqrt(minR[0]))
   S = [X[mid]]
   for i in range(len(X)):
	if i == mid:continue
	if math.fabs(X[i][0]-X[mid][0]) < delta:
		S.append(X[i])
   S = msPts(S,1) #S is now a set of points in delta range of X[mid] sorted by y-coordinate
   #print S, delta**2
   
   min_dist = float('inf')
   for i in range(len(S)):
	for j in range(1,8):
		if i+j >= len(S): break
		dist = distsq(S[i],S[i+j])
		if dist < min_dist:
			min_dist = dist 
			pts = [S[i],S[i+j]]	
   
   if min_dist < delta**2:
	return min_dist, pts, msPts(X,1)
   elif minL[0] < minR[0]:
	return minL
   else:
	return minR
   
      
'''
Find the square of the distance between two points.
Preconditions:  p1 and p2 are two points in the plane
  where the first element in each list is the x coordinate and the second
  is the y coordinate.
Postcondition:  the square of the distance between the two points has
  been returned
'''
def distsq(p1, p2):
   return (p1[0]-p2[0])**2+(p1[1]-p2[1])**2

'''One way to test out the correctness and efficiency of your code is
to uncomment some of the following:
'''

if __name__ == '__main__':

   ''' ************************************* '''

   ''' S = readPts('points.txt')'''

   while True:
   	size = int(input("Enter number of points:  "))
   	print size
   	S = [[random.random(), random.random()] for i in range(size)]
   	#print S
   
   	start=time();
   	Soln = closest(S)
   	end = time();
   	print '\n    Solution for closest: ', Soln[0]
   	print '\n     Elapsed for closest: ', end - start
   
   	start = time()
   	Soln = brute(S)
   	end = time()
   	print '\nSolution for brute-force: ', Soln[0]
   	print '\n Elapsed for brute-force: ', end - start
   
