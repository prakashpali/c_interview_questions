

'''
Class & Object
==================
A class is an user-defined prototype for an object that defines a set of attributes
that characterize any object of the class. The attributes are data members
(class variables and instance variables) and methods, accessed via dot notation.

An object refers to an instance of a certain class. For example, an object named
obj that belongs to a class Circle is an instance of that class. A unique instance
of a data structure that is defined by its class. An object comprises both data
members (class variables and instance variables) and methods.
'''


# Defining class
class Employee:
    "Common base class for all employees"

    # Class variable
    empCount = 0
    # Private class variable
    __secret_empCount = 2

    def __init__(self, name, salary):
        self.name = name
        self.salary = salary
        Employee.empCount += 1

    def __del__(self):
      class_name = self.__class__.__name__
      print(class_name, "destroyed")

    def getCount(self):
       return Employee.empCount

    @classmethod
    def getCount1(cls):
       return cls.empCount

    def getSecretCount(self):
       return Employee.__secret_empCount

    def displayEmployee(self):
        print("Name : ", self.name,  ", Salary: ", self.salary)


# This would create first object of Employee class
e1 = Employee("Bhavana", 24)
e2 = Employee("Rajesh", 26)
e3 = Employee("John", 27)

# Accessing class attributes and methods
print("======= Accessing class attributes and methods =======")
e1.displayEmployee()
e2.displayEmployee()
e3.displayEmployee()

# Accessing class variable
print("Total Employee %d" % Employee.empCount)
print("Total Employee %d" % Employee.getCount(e1))
print("Total Employee %d" % Employee.getCount1())

# Accessing private class variable
# print("Total Secret Employee %d" % Employee.__secret_empCount)
print("Total Secret Employee %d" % Employee.getSecretCount(e1))
print("Total Secret Employee %d" % Employee._Employee__secret_empCount)
print("======================================================\n\n")


print("======= Adding class attributes and methods ==========")
# Add an 'age' attribute
e1.age = 7
# Modify 'age' attribute
e2.age = 8
# Delete 'age' attribute
# del e1.age

# Returns true if 'age' attribute exists
hasattr(e1, 'age')
# Returns value of 'age' attribute
print("Employee e1 age: ", getattr(e1, 'age'))
# Set attribute 'age' at 8
setattr(e1, 'age', 8)
# Returns value of 'age' attribute
print("Employee e1 age: ", getattr(e1, 'age'))
# Delete attribute 'age'
delattr(e1, 'age')

# class method
@classmethod
def companyName(cls):
    print("Name of the company is Raymond")

# adding dynamically
setattr(Employee, "company_name", companyName)
newObj = Employee("John", 27)
newObj.company_name()
print("======================================================\n\n")


print("======= Build-in class attributes and methods ========")
# Class documentation string or none, if undefined
print("Employee.__doc__:", Employee.__doc__)

# Class name
print("Employee.__name__:", Employee.__name__)

# Module name in which the class is defined. This attribute is "__main__" in interactive mode
print("Employee.__module__:", Employee.__module__)

# A possibly empty tuple containing the base classes, in the order of their occurrence in the base class list
print("Employee.__bases__:", Employee.__bases__)

# Dictionary containing the class's namespace.
print("Employee.__dict__:", Employee.__dict__)
print("======================================================\n\n")


print("======= Deleting class objects =======================")
del e1
del e2
del e3
print("======================================================\n\n")