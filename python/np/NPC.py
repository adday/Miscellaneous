import random
from Graph2 import Graph

''' is an undirected special case of Graph class.  It demonstrates
    some algorithms optimization problems on graphs, and illustrates
    how to show that problems are NP-complete and NP-hard '''
class UndirectedGraph(Graph):

  # return a list of undirected edges
  def getEdges(self):
     edgeList = []
     for i in range(self.getn()):
        for j in self.neighbors(i):
           if j > i:
              edgeList.append((i,j))
     return edgeList
        
  ''' constructor.  numVerts tells how many vertices it should have.  
      edgeList is a list of ordered pairs, one for each edge, in any order.
      Example: numVerts = 3 and edgeList = [(0,1), (1,2), (0,2), (2,0)]'''
  def __init__ (self, numVerts, edgeList):
    Graph.__init__(self, numVerts, [])
    for x,y in edgeList:
        self.addEdge(x,y)

  # add an undirected edge (two directed edges, opposite directions)
  def addEdge(self, i, j):
    self.neighbors(i).append(j)
    self.neighbors(j).append(i)
    self._m += 1


  ''' ---------------------------------------------------------------
  Exponential algorithms for some NP-hard optimization problems
    --------------------------------------------------------------- '''
  
  '''  Find a maximum independent set in the graph '''
  def maxIndSet(self):
    selected = [False]*self.getn()
    return self.maxIndSet_Aux(self.getn(), selected)

  def maxIndSet_Aux(self, i, selected):
    if i == 0:  
       return []
    else:
       s1 = self.maxIndSet_Aux(i-1, selected)
       if True not in [selected[j] for j in self.neighbors(i-1)]:
          selected[i-1] = True
          s2 = self.maxIndSet_Aux(i-1, selected)
          s2.append(i-1)
          selected[i-1] = False
       else:
          s2 = []
       if len(s1) > len(s2): return s1
       else:  return s2
  
  ''' A maximum-weight independent set in a graph where Weights[i]
      is the weight of vertex i. '''

  # Find the weight of a maximum-weight independent set
  def maxWeightIndSet(self, Weights):
    selected = [False]*self.getn()
    return self.maxWeightIndSet_Aux(self.getn(), selected, Weights)

  def maxWeightIndSet_Aux(self, i, selected, Weights):
    if i == 0:  
       return [0, []]
    else:
       s1 = self.maxWeightIndSet_Aux(i-1, selected, Weights)
       if True not in [selected[j] for j in self.neighbors(i-1)]:
          selected[i-1] = True
          s2 = self.maxWeightIndSet_Aux(i-1, selected, Weights)
          s2[0] += Weights[i-1]
          s2[1].append(i-1)
          selected[i-1] = False
       else:
          s2 = [0,[]]
       if s1[0] >= s2[0]:
          return s1
       else:
          return s2
  
  # Find a minimum number of vertices in a vertex cover
  def minVertCover(self):
     selected = []
     return self.minCoverAux(self.getn(), selected)

  def minCoverAux(self, i, selected):
     if self.isVertexCover(selected):
        return selected
     elif i == 0:
        return range(self.getn())
     else:
        selectCopy = selected[:]
        s1 =self.minCoverAux(i-1, selectCopy)
        selectCopy = selected[:]
        selectCopy.append(i-1)
        s2 = self.minCoverAux(i-1, selectCopy)
        if len(s1) <= len(s2):
           return s1
        else:
           return s2

  # Find the weight of a minimum-weight vertex cover
  def minWeightVertCover(self, Weights):
     selected = []
     return self.minWeightCoverAux(self.getn(), selected,Weights)

  def minWeightCoverAux(self, i, selected,Weights):
     if self.isVertexCover(selected):
	weight = 0
	for j in selected: 
		weight += Weights[j]
        return [weight,selected]
     elif i == 0:
	weight = 0
	for j in range(self.getn()): 
		weight += Weights[j]
        return [weight,range(self.getn())]
     else:
        selectCopy = selected[:]
        s1 =self.minWeightCoverAux(i-1, selectCopy,Weights) 
	selectCopy = selected[:]
        selectCopy.append(i-1)
        s2 = self.minWeightCoverAux(i-1, selectCopy,Weights)
        if s1[0] <= s2[0]:
           return s1
        else:
           return s2

  def minWeightVertCover2(self,Weights):
     maxIndSet = self.maxWeightIndSet(Weights)
     minWeightCover = []
     for i in range(self.getn()):
	if i not in maxIndSet[1]:
		minWeightCover.append(i)
     weight = 0
     for j in minWeightCover:
	weight += Weights[j]
     return [weight,minWeightCover]           

  ''' ---------------------------------------------------------------- 
  Reductions of decision problems to optimization problems
  ---------------------------------------------------------------- '''

  # Check whether the graph has an independent set of size k
  def INDEPENDENT_SET(self, k):
     return len(self.maxIndSet()) >= k  

  # Check whether a weights graph has an independent set of weight w.
  #  Weights[i] is the weight of vertex i
  def WEIGHTED_INDEPENDENT_SET(self, w, Weights):
     return self.maxWeightIndSet(Weights)[0] >= w  

  # Check whether the graph has a vertex cover of size k ...
  def VERTEX_COVER(self, k):
     if len(self.minVertCover()) <= k: return True
     else:  return False


  ''' ---------------------------------------------------------------- 
  Checkers of certificates of yes answers ...
  ---------------------------------------------------------------- '''

  #  Test whether an alleged independent set of size k really is one ...
  #  Hint is a frozenset of integers allegedly giving vertex numbers of
  #  an independent set
  def INDEPENDENT_SET_HINT(self, k, Hint):
     if len(Hint) < k: return False    # O(1) (polynomial) time
     return self.isIndSet(Hint)  # we know this takes polynomial time 
     
  # Hint is a frozenset of vertex numbers;  return true if it is an
  #  independent set
  def isIndSet(self, Hint):
    n = self.getn()
    V = frozenset(range(n))
    if not Hint <= V:  return False
    for i in Hint:
       for j in self.neighbors(i):
           if j in Hint:
              return False
    return True

  #  Test whether an alleged weighted independent set of weight w really
  #  is an independent set and has weight w.  Hint is a frozenset of
  #  alleged vertex numbers of an independent set of weight w.  Weights[i]
  #  is the weight of vertex i
  def WEIGHTED_INDEPENDENT_SET_HINT(self, w, Weights, Hint):
     if max(Hint) >= self.getn(): return False
     if sum([Weights[i] for i in Hint]) < w:
         return False
     else:
         return self.isIndSet(frozenset(Hint))

  #  Test whether an alleged vertex cover of size k really is a vertex
  #  cover of size k.    Hint is a frozenset of integers, allegedly the
  #  vertex numbers of a vertex cover of size at most k.
  def VERT_COVER_HINT(self, k, Hint):
     if len(Hint) > k: return False          
     else:  return self.isVertexCover(Hint)  

  # Supplementary method for testing an alleged vertex cover.
  #  Return True if X is a vertex cover
  #  This obviously takes O(n+m), which is polynomial.
  def isVertexCover(self, Hint): 
     marked = [False] * self.getn()
     for i in Hint: marked[i] = True
     for i,j in self.getEdges():
        if not marked[i] and not marked[j]:  # if some edge is uncovered
           return False
     return True

  ''' ---------------------------------------------------------------- 
  Reductions of INDEPENDENT_SET to WEIGHTED_INDEPENDENT SET
  and VERTEX_COVER
  ---------------------------------------------------------------- '''

   
  def INDEPENDENT_SET2(self, k):
     Weights = [1] * self.getn() # set all weights set to 1.  A max-weight
                                 # independent set is now a max independent set
     return self.WEIGHTED_INDEPENDENT_SET(k, Weights) 

  def INDEPENDENT_SET3(self, k):
     return self.VERTEX_COVER(self.getn()-k)

  def INDEPENDENT_SET4(self,k):
    GC = self.Complement()
    return GC.CLIQUE(k)

  def Complement(self):
     edgeList = []
     for i in range(self.getn()):
	for j in range(self.getn()):
		if i < j:
			edgeList.append((i,j))
     for k in self.getEdges():
	edgeList.remove(k)
     return UndirectedGraph(self.getn(),edgeList)

   # Check whether the graph has a clique of size k ...
  def CLIQUE (self, k):
     return len(self.maxClique()) >= k

  '''  Find a maximum clique in the graph '''
  def maxClique (self):
    selected = [False]*self.getn()
    return self.maxClique_Aux(self.getn(), selected)

  def maxClique_Aux(self, i, selected):
    if i == 0:  
       return []
    else:
       s1 = self.maxClique_Aux(i-1, selected)
       NonNeighbors = frozenset(range(self.getn())) - frozenset(self.neighbors(i-1))
       if True not in [selected[j] for j in NonNeighbors]:
          selected[i-1] = True
          s2 = self.maxClique_Aux(i-1, selected)
          s2.append(i-1)
          selected[i-1] = False
       else:
          s2 = []
       if len(s1) > len(s2): return s1
       else:  return s2
''' ---------------------------------------------------------------- 
How to use ASAT to solve any problem in NP
---------------------------------------------------------------- '''

def ASAT(Method, k, maxValue):
    Input = [0]*k
    for i in xrange((maxValue+1)**k):
       if Method(Input):
          return True
       for j in range(k):
           if Input[j] < maxValue:
               Input[j] += 1
               break
           else:
               Input[j] = 0
    return False

'''
   Here's an example of how to use it to solve INDEPENDENT_SET.  Create
   the following program, hardcoding the instance of the problem you
   want to know about.  Hint is a Python frozenset of vertices that
   allegedly make up an independent set in the hard-coded graph
'''
def IndSetGadget(Hint):
    # Hard code the instance of the problem into the code
    NumVertices = 7
    Edges = [(0, 5), (0, 2), (0, 6), (1, 2), (1, 5), (2, 3), (4, 5), (5, 6)]
    IndSetSize = 5
    G = UndirectedGraph(NumVertices, Edges) 

    RemoveIrrelevantBits(Hint, NumVertices-1)
    if G.INDEPENDENT_SET_HINT(IndSetSize, frozenset(Hint)):  return True
    else:  return False

'''
    Here's an example of how to use it to solve WEIGHTED_INDEPENDENT_SET.
    Hint is a Python frozenset of integers.  If it makes up a weighted
    independent set of TargetWeight in the hard-coded graph, it returns
    True, otherwise it returns False
'''
def WeightedIndSetGadget (Hint):
    # Hard code the instance of the problem into the code
    NumVertices = 7
    Edges = [(0, 5), (0, 2), (0, 6), (1, 2), (1, 5), (2, 3), (4, 5), (5, 6)]
    G = UndirectedGraph(NumVertices, Edges) 
    Weights = [1,1,2,2,1,6,3]
    TargetWeight = 8

    RemoveIrrelevantBits(Hint, NumVertices-1)
    if G.WEIGHTED_INDEPENDENT_SET_HINT(TargetWeight, Weights, frozenset(Hint)): 
       return True
    else:  
       return False


'''  
    Hint is a frozenset containing one integer other than 1 or n.  If it is a 
    factor of n, it returns True; otherwise it returns false.
'''
def CompositeGadget(Hint):
    n = 998353

    RemoveIrrelevantBits(Hint, 1023)
    i = Hint[0]
    if i <= 1 or i == n:  
        return False
    elif n % i == 0:
        return True
    else:
        return False

def SATGadget(Hint):
    RemoveIrrelevantBits(Hint, 1)
    X = [False] * 4
    for i in range(4):
       if Hint[i] == 1:
           X[i] = True
    return (not X[0] or X[1]) and (not X[1] or X[2]) and (not X[2] or X[3]) and (not X[3] or not X[0]) and X[0] 


#Hint is a list of length 8 where each element is 0 or 1 indicating whether that item should be selected
def SubsetSumGadget(Hint):
    Items = [35295649, 3183127, 8264528, 3292534, 2842252, 4414449, 6553326, 2821438]
    Target = 4798376

    sum = 0   
    for i in range(8):
	if Hint[i] == 1:
		sum += Items[i]
    if sum == Target:
	return True
    return False

#Hint is a 7 element list of the integers 0-7 (each element is unique)
def HamTourGadget(Hint):
    edgeList = [(0, 5), (0, 2), (0, 6), (1, 2), (1, 5), (2, 3), (4, 5), (5, 6)]
    Graph = UndirectedGraph(7, edgeList)
  
    #Ensure no duplicates in the list
    Hint2 = list(set(Hint))
    if len(Hint2) != len(Hint): return False

    for i in Hint:
	if Hint[(i+1)%7] in Graph.neighbors(Hint[i]):continue
	else: return False
    print Hint
    return True	 


# Next power of two greater than n
def nextPowerTwo(n):
  i = 1
  while i <= n:
     i *= 2
  return i
  
# A is a list of integers.
# Zero out all bits of each element oF A except for those needed to
#  store an integer as large as maxValue
def RemoveIrrelevantBits(A, maxValue):
  p = nextPowerTwo(maxValue)
  for i in range(len(A)):
     A[i] = A[i] % p
   
def readUndirectedGraph(filename):
  edgeList = []
  fp = open(filename, 'r')
  n = int(fp.readline())
  for line in fp:
     u,v  = [int(x) for x in line.split(',')]
     edgeList.append((u,v))
  return UndirectedGraph(n, edgeList)

'''  *************************************************************
     That's all for the lesson; rest is utility functions.
     *************************************************************
'''

'''  Read a graph in from a file.  The format of the file is as follows:
     The first line gives the number of vertices.
     Each subsequent line gives a pair of vertices, separated by
     a comma, indicating an undirected edge.

     Example:
     ----
     3
     0,1
     1,2
     0,2
     ----

     This gives a graph with three vertices and four undirected edges,
     {0,1}, {1,2}, {0,2}
'''


# generate a random graph on n vertices    
def randGraph(n):
  E = [(i,j) for i in range(n) for j in range(i+1,n) if random.randrange(0,30) == 0]
  return UndirectedGraph(n, E)
    
if __name__ == '__main__':
   E = [(0, 5), (0, 2), (0, 6), (1, 2), (1, 5), (2, 3), (4, 5), (5, 6)]

   G = UndirectedGraph(7, E) 

   print ('Graph:   ' + str(G))

   print('\nList of edges: ' + str(G.getEdges()))
   Weights = [1,1,2,2,1,6,3]
   print 'Weights ', Weights

