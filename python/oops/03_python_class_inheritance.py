
'''
Docstring for python.03_python_class_inheritance

Inheritance
==================
A software modelling approach of OOP enables extending capability of an existing
class to build new class instead of building from scratch. In OOP terminology,
existing class is called base or parent class, while new class is called child
or sub class.

Child class inherits data definitions and methods from parent class. This
facilitates reuse of features already available. Child class can add few more
definitions or redefine a base class function.
'''

# Define parent class
class Parent:
    parentAttr = 100

    def __init__(self):
        print("Calling parent constructor")

    def parentMethod(self):
        print("Calling parent method")

    def setAttr(self, attr):
        Parent.parentAttr = attr

    def getAttr(self):
        print("Parent attribute :", Parent.parentAttr)

# Define child class
class Child(Parent):
    def __init__(self):
        print("Calling child constructor")

    def childMethod(self):
        print("Calling child method")


# instance of child
c = Child()

# boolean function returns true if the given subclass sub is indeed a subclass of the superclass sup.
print("Is Child class a subclass of Parent class? ", issubclass(Child, Parent))

# boolean function returns true if obj is an instance of class Class or is an instance of a subclass of Class
print("Is c instance of Child class? ", isinstance(c, Child))
print("Is c instance of Parent class? ", isinstance(c, Parent))

# child calls its method
c.childMethod()
# calls parent's method
c.parentMethod()
# again call parent's method
c.setAttr(200)
# again call parent's method
c.getAttr()
