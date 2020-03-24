import numpy
from matplotlib import pyplot
import os

print(os.getcwd())

result_x = numpy.array([])
n_x = numpy.array([])

result_y = numpy.array([])
n_y = numpy.array([])
with open("cmake-build-debug/data.txt" , 'r') as dataFile:
    while True:
        data = dataFile.readline()
        if not data :
            break

        data = data.split(" ")
        n_x = numpy.append(n_x, int(data[0])-5)
        result_x = numpy.append(result_x, float(data[1]))


with open("cmake-build-debug/data_1.txt" , 'r') as dataFile:
    while True:
        data = dataFile.readline()
        if not data :
            break

        data = data.split(" ")
        n_y = numpy.append(n_y, int(data[0])-5)
        result_y = numpy.append(result_y, float(data[1]))



pyplot.figure(figsize=(8, 6))
pyplot.scatter(n_x, result_x, marker='o',label=rf'$x(n)$',  linewidth =2)
pyplot.scatter(n_y, result_y, marker='o', label=rf'$y(n)$', linewidth =2)
pyplot.xlim(-5, 25)
pyplot.grid()
pyplot.legend()
pyplot.show()


