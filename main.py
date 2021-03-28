from random import randint

# A short program to very unoptimally solve a maths problem
# https://www.youtube.com/watch?v=NzhXipwiz_E

"""
In a barn, 100 chicks sit peacefully in a circle. Suddenly, each chick
randomly pecks the chick immediately to its left or right. What is the
expected number of unpecked chicks?
"""

def initialise_chickens(length = 100):
    chickens = []
    for i in range(length):
        chickens.append(False)
    return chickens

def simulate_pecking(chicken_count = 100):
    chickens = initialise_chickens(length=chicken_count)
    for i in range(len(chickens)):
        if randint(1,2) == 1:
            if (i == 0):
                chickens[-1] = True
            else:
                chickens[i-1] = True
        else:
            if (i == chicken_count - 1):
                chickens[0] = True
            else:
                chickens[i+1] = True
    return chickens

def calculate_pecking_rate(chickens : list):
    return float(chickens.count(True) / len(chickens))

def run_many_times(trials=100000):
    total = float(0)
    iterations = int(0)
    for i in range(trials):
        iterations = iterations + 1
        if (i % 1000 == 0):
            print("Iteration %i" % i)
            print("Pecking rate is %f" % (total / float(iterations)))
        chickens = simulate_pecking()
        total = total + calculate_pecking_rate(chickens)
    
    print("Pecking rate is %f" % (total / float(trials)))

def main():
    run_many_times()

if __name__ == "__main__":
    main()