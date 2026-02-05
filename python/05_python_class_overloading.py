
'''
Docstring for python.05_python_class_overloading

Overloading Methods
==================
Following table lists some generic functionality that you can override in your own classes
1. __init__ ( self [,args...] )
Constructor (with any optional arguments)
Sample Call : obj = className(args)
2. __del__( self )
Destructor, deletes an object
Sample Call : del obj
3. __repr__( self )
Evaluable string representation
Sample Call : repr(obj)
4. __str__( self )
Printable string representation
Sample Call : str(obj)
5. __cmp__ ( self, x )
Object comparison
Sample Call : cmp(obj, x)

Overloading Operators
==================
Suppose you have created a Vector class to represent two-dimensional vectors,
what happens when you use the plus operator to add them? Most likely Python will
yell at you.

You could, however, define the __add__ method in your class to perform vector
addition and then the plus operator would behave as per expectation

'''

class Vector:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __str__(self):
        return 'Vector (%d, %d)' % (self.a, self.b)

    def __add__(self, other):
        return Vector(self.a + other.a, self.b + other.b)

v1 = Vector(2,10)
v2 = Vector(5,-2)
print (v1 + v2)
