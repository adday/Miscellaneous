#HW2 Heap.py
#Alexander Day
#830523317
# Heap class: The internal variables are:
#  self._H: Heap array as defined in the book
#  self._allocation: size of self._H; some elements at the end of this
#    array might be unused. This is always  a power of two.
#  self._size: Number of elements currently stored in self._H; this
#    is always at least self._allocation/4 and at most self._allocation
#  self._degree: Number of child nodes for each parent
class Heap(object):

  # constructor: create a heap with allocation 1 and size 0:
  # To call it, execture P = Heap(); this assigns a reference to an
  # empty heap to variable P. (Implements "priority queue" ADT)
  # Parameter: k: Number of child nodes for each parent
  def __init__(self, k):
    self._H = [0]
    self._size = 0
    self._allocation = 1
    self._degree = k

  # get current size
  # if P contains a reference to it,then call it with P.getSize()
  def  getSize(self):
    return self._size

  # get current allocation
  def getAllocation(self):
    return self._allocation

  #get a reference to the heap array
  def getArray(self):
    return self._H

  # Find the parent of index pos, or return None if it's the root.
  #  There is no check to see if pos >= self._size
  #  Call: P.parent(i). This assigns the reference in P to 'self'
  #  and the reference to the integer in pos to i.
  def parent(self,pos):
    if pos <= 0: return None
    else: return (pos-1)/self._degree

  # Swap the elements at pos1 and pos2 of the heap array. Leave the
  #  structure unchanged if one or more of the indices are not in
  #  {0,1,2, ..., getSize()-1}. Otherwise, swap the elements.
  def swap(self,pos1,pos2):
    s = self.getSize()
    if 0 <= pos1 and 0<= pos2 and pos1 < s and pos2 < s:
	self._H[pos1], self._H[pos2] = self._H[pos2], self._H[pos1]

  # insert integer to heap. Call: P.insert(i)
  def insert(self, item):
    # double allocation of array if it's full.
    if self._size == self._allocation:
	self._H = self._H[:] + [0] * self._allocation
	self._allocation = self._allocation * 2

    # insert the item at the end...
    self._H[self._size] = item
    pos = self._size 
    self._size += 1
    # restore the heap property by bubbling it up to a point where 
    # it's at the root or its parent's key is at least as small...
    while pos > 0 and self._H[self.parent(pos)] > self._H[pos]:
      self.swap(self.parent(pos),pos)
      pos = self.parent(pos)

  # Return the index of child number i of the node at position pos.
  #  Preconditions are that pos is a valid index. It will return
  #  the index of this child, whether or not it exists and whether
  #  or not its position is beyond the end of the heap array
  def childIndex(self,pos,i):
    return self._degree * pos + 1 + i

  # Tell the key in child number i (i in {0,k}) of the node at position
  #  'pos' of heap array. If there is no such child, return None. Precondition
  #  is that i is in {0,k}
  def child(self,pos,i):
    if self.childIndex(pos,i) >= self._size:
   	return None
    return self._H[self.childIndex(pos,i)]

  def children(self,pos):
    children = [] 
    for i in range(0,self._degree):
	children.append(self.child(pos,i))
    for i in range(self._degree-1,-1,-1):
	if children[i] == None: children.remove(None)
    return children

  # Extract the minimum element of the heap, and restore the heap property.
  def extractMin(self):
    #store return value,swap with last element and delete,decrease _H size by 1
    if self._size == 0: return
    root = self._H[0]
    self.swap(0,self._size-1)
    self._size -= 1
    #heapify and return min
    self.heapify(0)
    return root
 
  def heapify(self,pos):
    C = self.children(pos)
    if not C: return
    if min(C) > self._H[pos]:return
    self.swap(pos,self.childIndex(pos,C.index(min(C))))
    self.heapify(self.childIndex(pos,C.index(min(C))))

  
  def __str__(self):
    if self.getSize() == 0: return ""
    else: return self.strAux(0, 0, "")

  def strAux(self,pos,depth,outString):
    outString = outString + "\n" + ' ' * depth + str(self._H[pos])
    children = self.children(pos)
    for i in range(len(children)):
	outString = self.strAux(self.childIndex(pos,i), depth+1, outString)
    return outString
  

if __name__ == "__main__":
     #creates 3-ary heap
    P = Heap(3)   

    P.insert(10)
    P.insert(29)
    P.insert(11)
    P.insert(3)
    print "Heap array: " + str(P.getArray())
    print "Size: " + str(P.getSize())
    print "allocation " + str(P.getAllocation())
