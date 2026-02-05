
'''
Docstring for python.02_python_class_encapsulation

Encapsulation
==================
Data members of class are available for processing to functions defined within
the class only. Functions of class on the other hand are accessible from outside
class context. So object data is hidden from environment that is external to class.
Class function (also called method) encapsulates object data so that unwarranted
access to it is prevented.
'''

class Desktop:
   def __init__(self):
        self.__max_price = 25000

   def sell(self):
        return f"Selling Price: {self.__max_price}"

   def set_max_price(self, price):
        if price > self.__max_price:
            self.__max_price = price

# Object
desktopObj = Desktop()
print(desktopObj.sell())

# modifying the price directly
desktopObj.__max_price = 35000
print(desktopObj.sell())

# modifying the price using setter function
desktopObj.set_max_price(35000)
print(desktopObj.sell())