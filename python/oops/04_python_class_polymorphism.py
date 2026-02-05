'''
Docstring for python.04_python_class_polymorphism

Polymorphism
==================
Polymorphism is a Greek word meaning having multiple forms. In OOP, polymorphism
occurs when each sub class provides its own implementation of an abstract method
in base class.

You can always override your parent class methods. One reason for overriding
parent's methods is because you may want special or different functionality in
your subclass.
'''

# define parent class
class Parent:
    def myMethod(self):
        print ("Calling parent method")

# define child class
class Child(Parent):
    def myMethod(self):
        print ("Calling child method")

# instance of child
c = Child()
# child calls overridden method
c.myMethod()