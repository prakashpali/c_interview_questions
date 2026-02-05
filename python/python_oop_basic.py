# Object-Oriented Programming in Python
# This file contains basic examples of OOP concepts in Python.
# Principles of OOPs in Python:
# 1. Class
# 2. Object
# 3. Encapsulation
# 4. Inheritance
# 5. Polymorphism

# Other Topics:
# 6. Methods and Attributes
# 7. Constructors and Destructors
# 8. Access Modifiers
# 9. Method Overriding
# 10. Method Overloading
# 11. Class Variables and Instance Variables
# 12. Static Methods and Class Methods
# 13. Properties
# 14. Magic Methods
# 15. Composition
# 16. Aggregation
# 17. Interfaces
# 18. Mixins
# 19. Design Patterns
# 20. SOLID Principles
# 21. UML Diagrams
# 22. Best Practices
# 23. Common Pitfalls
# 24. Advanced Topics
# 25. Real-world Examples
# 26. Testing OOP Code
# 27. Performance Considerations
# 28. Refactoring OOP Code
# 29. Documentation
# 30. Further Reading and Resources
# Note: This file serves as a basic introduction to OOP in Python. Each topic can be expanded with examples and explanations as needed.



from abc import ABC, abstractmethod
class democlass(ABC):
   @abstractmethod
   def method1(self):
      print ("abstract method")
      return
   def method2(self):
      print ("concrete method")

class concreteclass(democlass):
   def method1(self):
      super().method1()
      return

obj = concreteclass()
obj.method1()
obj.method2()