
def universal_decorator(func):
    def wrapper(*args, **kwargs):
        print("Executing...")
        res = func(*args, **kwargs)
        print(f"Return value: {res}")
        print("Executed...")
        return res
    return wrapper

@universal_decorator
def add(a, b):
    return a+b

add(2, 3)