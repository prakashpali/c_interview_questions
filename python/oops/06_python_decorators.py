



def universal_decorator(func):
    def wrapper(*args, **kwargs):
        print("Executing...")
        result = func(*args, **kwargs)
        print("Finished executing...")
        return result
    return wrapper

@universal_decorator
def add(a, b):
    return a + b

print(add(3, 5))



import time

def timer_decorator(func):
    def wrapper(*args, **kwargs):
        start_time = time.perf_counter() # Start the clock

        result = func(*args, **kwargs)   # Run the actual function

        end_time = time.perf_counter()   # Stop the clock
        duration = end_time - start_time
        print(f"Function '{func.__name__}()' took {duration:.4f} seconds.")

        return result # Return what the original function would have returned
    return wrapper

@timer_decorator
def heavy_computation():
    # Simulating a heavy task (summing 10 million numbers)
    return sum(range(10000000))

# Run the decorated function
print(heavy_computation())