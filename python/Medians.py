'''  Preconditions:  X and Y are sorted Python lists of integers values, and
       their lengths are both equal to 2^k+1 for some k >= 0.  
     Postcondition:  the two medians of X+Y have been returned as a 
       python List of size two.
'''
def medians(X,Y):
   lastIndex = len(X) - 1
   return mediansAux(X, 0, lastIndex, Y, 0, lastIndex)

'''
  Preconditions:  j1-i1+1 = j2-i2+1 = 2^k+1 for some k >= 0, and
        X[i1:j1+1] and Y[i2:j2+1] are sorted lists of integers.
     Postcondition:  the two medians of X[i1:j1+1] + Y[i2:j2+1]  have
        been returned as a Python list of length two.
     Fill in the recursive procedure.  To get credit, your running time must 
        be o(n) where n = j1-i1+1
'''
def mediansAux(X, i1, j1, Y, i2, j2):
    # base cases are lists of size 1 or 2
    # as len(X) == len(Y) we only consider i1 and j1 in checking sizes
    print(i1,j1,i2,j2)
    print(X,Y)
    if (i1 == j1):
        return (X[i1],Y[i2])
    if (j1-i1 == 2):
        print("here")
        return ( max(X[ int((i1+j1)/2) ], Y[ int((i2+j2)/2)] ) , min(X[ int((i1+j1)/2) ], Y[ int((i2+j2)/2)] ) )
    # find medians of the lists using helper function
    m1 = median(X) 
    m2 = median(Y) 
    print(m1,m2)

    # if the returned medians are equal then return both of them
    if (m1 == m2):
        return (m1,m2)
 
    # if m1 < m2 then median must exist in X[m1:] and Y[:m2] 
    if (m1 < m2):
        if ((j1-i1) % 2 == 0):
            return mediansAux(X, int(j1/2) - 1, j1, Y, i2, int(j2/2) +1)
        return mediansAux(X, int(j1/2), j1, Y, i2, int(j2/2)+1)
 
    # if m1 > m2 then median must exist in X[:m1] and Y[m2:]
    if ((j1-i1) % 2 == 0):
        return mediansAux(Y, int(j2/2) - 1, j2, X, i1, int(j1/2) +1)
    return mediansAux(Y, int(j2/2), j2, X, i1, int(j1/2)+1)
 

# helper function to find median of a sorted array
def median(X):
    if (len(X)%2 == 0):
        return (X[int(len(X)/2)], X[int(len(X)/2-1)])
    else:
        return X[int(len(X)/2)]
