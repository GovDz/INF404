import random
import os

def generate_arithmetic_expression(valid=True):
    operators = ['+', '-', '*', '/']
    
    if not valid:
        return "This is an invalid expression"
    
    expression = ''
    for _ in range(random.randint(1, 10)):
        expression += str(random.randint(1, 100))
        expression += random.choice(operators)
    expression += str(random.randint(1, 100))
    return expression

def generate_test_file(num_tests):
    for i in range(1, num_tests + 1):
        is_valid = random.random() < 0.5
        expression = generate_arithmetic_expression(is_valid)
        file_name = f'Test_{i}.test'
        with open(file_name, 'w') as file:
            file.write(expression)

if __name__ == "__main__":
    num_tests = int(input("Enter the number of tests to generate: "))
    generate_test_file(num_tests)
    print(f"{num_tests} tests generated successfully.")
