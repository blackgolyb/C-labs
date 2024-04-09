import matplotlib.pyplot as plt
import csv

FILE_NAME = "sort.csv"

def main():
    iterations: list[int] = []
    times: list[list[float]] = []
    
    with open(FILE_NAME) as csvfile:
        reader = csv.reader(csvfile, delimiter=";")
    
        reader_it= iter(reader)
        iterations = list(map(int, next(reader_it)))
        
        for row in reader_it:
            times.append(list(map(float, row)))

    plt.plot(iterations, times[0], label="bubble sort")
    plt.plot(iterations, times[1], label="quick sort")
    plt.plot(iterations, times[2], label="marge sort")
    plt.legend()
    plt.show()
    
if __name__ == "__main__":
    main()