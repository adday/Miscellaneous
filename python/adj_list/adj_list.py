'''
This is an implementation of the adjacency-list representation of a graph
where the vertices are numbered from 0 through n-1.

The class has integer variables recording the number n of vertices
and number m of edges.  It has a list self.verts of length n of lists of integers.
The list that appears in position i of this list is the list of neighbors
of vertex i.  For example, if self.verts is [[1,2], [], [0]], then
there are three vertices, since there are three lists in it.  Vertex 0
has neighbors 1 and 2, vertex 1 has no neighbors, and vertex has 0 as
its only neighbor.
'''
White = 0
Red = 1
Blue = 2
'''  Read a graph in from a file.  The format of the file is as follows:
     The first line gives the number of vertices.
     Each subsequent line gives an ordered pair of vertices, separated by
     a comma, indicating a directed edge.

     Example:
     ----
     3
     0,1
     1,2
     0,2
     2,0
     ----

     This gives a graph with three vertices and four directed edges,
     (0,1), (1,2), (0,2), (2,0)
'''
def readGraph(filename):
  edgeList = []
  fp = open(filename, 'r')
  n = int(fp.readline())
  for line in fp:
     u,v  = [int(x) for x in line.split(',')]
     edgeList.append((u,v))
  return Graph(n, edgeList)
    
class Graph(object):

  # return number of vertices
  def getn(self):
     return len(self.verts)

  # return number of edges
  def getm(self):
     return self.m

  def neighbors(self, i):
    return self.verts[i]

  # return a list of ordered pairs giving the edges of the graph
  def getEdges(self):
    return [(i,j) for i in range(self.getn()) for j in self.neighbors(i)]

        
  ''' constructor.  __init__ is a reserved keyword identifying it
      as a constructor.  numVerts tells how many vertices it should have.  
      edgeList is a list of ordered pairs, one for each edge, in any order.
      Example: numVerts = 3 and edgeList = [(0,1), (1,2), (0,2), (2,0)]'''

  def __init__ (self, numVerts, edgeList):
    self.m = len(edgeList)
    self.verts = [[] for i in range(numVerts)]
    self.parentOf = [None for i in range(self.getn())]
    for u, v in edgeList:
	self.neighbors(u).append(v)  # works because neighbors returns a reference
                                     # to the neighbor list

  # add an edge from tail to head.  No checking for errors, such as multi-edges
  def addEdge(self, tail, head):
    self.neighbors(tail).append(head)
    self.m += 1
  
  ''' String representation of the graph.  If G is an instance of the class,
      this is called with str(G).  It is called implicitly when a string
      is expected, e.g. in a call to print(G) '''
  def __str__(self):
    return '\n        n:  ' + str(self.getn()) + '\n        m:  ' + str(self.getm()) + '\n' + 'Adj lists:  ' + str(self.verts) + '\n' + '  parents:  ' + str(self.parentOf) + '\n'


  ''' DFS.  *colored* is a list of length self.getn().
      colored[j] = True if vertex j is colored, and it's False if j is 
      white.  The parameter i is the vertex number of the vertex to start 
      at, and it must be white.  The call must color all vertices
      reachable from i in the white subgraph. 
      Labels vertices in parentOf with their parents produced by DFS'''
  def dfs(self, i, colored):
    colored[i] = True
    for j in self.neighbors(i):
	if not colored[j]: 
		self.parentOf[j] = i	
		self.dfs(j,colored)

  ''' Return the transpose of the graph, that is, the result of reversing
      all the edges, represented in the format specified by the Graph class  '''
  def transpose (self):
    other = Graph(self.getn(), [])
    for i in range(self.getn()):
	for v in self.neighbors(i):
		other.verts[v].append(i)
    other.m = self.m
    return other

  ''' BFS starting at i.  Label each node with its parent in the resulting
      BFS tree.  Return a list D of length n, where D[j] tells the distance
      of vertex j from vertex i, and a list L that gives the order in which
      vertex were extracted from the queue.  '''
  def bfs(self, i):
    D = [None for j in range(self.getn())] 
    L = [] 
    q = []
    q.append(i)
    front = 0
    D[i] = 0
    for i in q:
	for j in self.neighbors(i):
		if D[j] != None: continue
		self.parentOf[j] = i			
		q.append(j)
		D[j] = D[i] + 1
	L.append(q[front])
	front = front + 1
    return D, L

  ''' Return the vertices on a shortest path from i to j.  The precondition
      is that the parent pointers in the graph give a BFS tree rooted at i. '''
  def shortestPath(self, i, j):
    sp = [j]
    while j != i:
	sp.append(self.parentOf[j])
	j = self.parentOf[j]
    return sp


  '''  Determine whether the graph is strongly connected.  It should
       return False if it is not, True if it is.  '''
  def isStronglyConnected(self):
    D,L = self.bfs(0)
    if len(L) != self.getn(): 
    	return False
    t = self.transpose()
    D,L = t.bfs(0)
    if len(L) != self.getn():
	return False
    return True
   
  ''' Return (True, None)  if the graph is bipartite.  If it is not
      bipartite, have it return (False, L), where L is the list of
      vertices on an odd cycle, in order. '''
  def isBipartite(self):
    colorOf = [White for i in range(self.getn())]
    self.parentOf = [None for i in range(self.getn())]
    self.isBipartiteAux(0, Red, colorOf)
    if not 3 in colorOf:
	return True, None
    a = colorOf.index(3) #a guaranteed to be < b
    colorOf.pop(a)
    b = colorOf.index(3) + 1 #add one for pop(a)
    L = [a]
    while a != b:
	L.append(b)
	b = self.parentOf[b] if self.parentOf[b] != None else a
    return False, L

  ''' Preconditions are that 'i' is a white vertex, 'color' is either Red or 
      Blue, and colorOf[k] gives the current color of each vertex k.  
      Do one of the following:
 
        1.  Color all vertices reachable from i on a white path with Red and 
        Blue, starting by giving 'i' the color given by 'color', so that none 
        of these vertices is a neighbor of a vertex of the same color.  Return
        (True, None).

        2.  Return (False, L), where L is the list of vertices on an odd cycle,
        in the order in which they appear on the cycle.
  '''
  def isBipartiteAux(self, i, color, colorOf):
    colorOf[i] = color
    for j in self.neighbors(i):
	if colorOf[j] == colorOf[i]:
		colorOf[j], colorOf[i] = 3, 3 #3 used to flag matching neighbors
		return
	if colorOf[j] == White: 
		colorOf[j] = Red if colorOf[i] == Blue else Blue
		self.parentOf[j] = i
		self.isBipartiteAux(j,colorOf[j],colorOf)
		

  ''' This is a variant on DFS that returns a list of vertices that
      were blackened during the call, in the order in which they finished. 
      'colored' is a list of n False's.  'finished' is a list of vertices
      on which a recursive call has finished, in the order in which
      they finished.  When a vertex finishes, append it to this list.  '''
  def finishOrder(self, i, colored, finished):
    colored[i] = True
    for j in self.neighbors(i):
	if not colored[j]:
		self.finishOrder(j,colored,finished)
    finished.append(i)	
    return finished

  ''' Return the strongly-connected components, as a list L of lists of 
      integers.  Each list in L has the vertices in one strongly-connected
      components. '''
  def scc(self):
    L = []
    for i in self.blacken():
	L.extend(self.blacken(i))
    return L

  ''' Go through each vertex in the graph in the order given by vertOrder,
      calling DFS on the vertex if it's still white.  If no vertOrder
      parameter is given, then go through them in ascending order of
      vertex number.   Return a list L of lists, where each list in L
      is the vertices blackened by one of the calls to DFS generated
      from blacken.

      Being able to specify the order in which you go through them is
      useful for the strongly-connected components algorithm. '''
  def blacken(self, vertOrder = None):
    finished = []
    if vertOrder == None:
       vertOrder = range(self.getn())
    colored = [False]*self.getn()
    for i in vertOrder:
       if not colored[i]:
          finished.append(self.finishOrder(i, colored, []))
    return finished

if __name__ == '__main__':
    print '\n\nFun with graphs'
    G1 = readGraph("G1")
    G2 = readGraph("G2")
    G3 = readGraph("G3")
    G4 = readGraph("G4")
    G5 = readGraph("G5")
