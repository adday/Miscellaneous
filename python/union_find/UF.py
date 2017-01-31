
class UF:

  # Return number of elements
  def getn(self):
     return len(self._id)
        
  ''' constructor.  
      Parameter n is the number of elements'''
  def __init__ (self, n):
    self._id = [i for i in range(n)] 		#_id[i] tells id number of union-find class that element i is in
    self._l = [[i] for i in range(n)] 		# _l[j] is a reference to list giving the elements for class j.
    

  # look up the class j containing i in _id[i]. Look up the class containing i, in _l[j]
  def find(self, i):
    return self._id[i]
  

  # Perform each union by appending references to the elements of the 
  # smaller class to the end of the larger class, as described in the text.
  def union(self, i, j):
    if self.find(i)  ==  self.find(j):
	return False
    if len(self._l[self.find(i)]) >= len(self._l[self.find(j)]):
	self._l[self.find(i)].extend(self._l[self.find(j)])
	for k in self._l[self.find(j)]: self._id[k] = self._id[i]
	self._l[j] = None
    else:
	self._l[self.find(j)].extend(self._l[self.find(i)])
	for k in self._l[self.find(i)]: self._id[k] = self._id[j]
	self._l[i] = None
    return True
	


  #print str method
  def __str__(self):
    return 'id: ' + str(self._id) + '\nl:  ' + str(self._l)




