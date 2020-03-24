import numpy
from matplotlib import pyplot
from math import pi

try :
    t = []
    result = []
    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        while True :
            line = dataFile.readline() # read one line

            if not line:
                break

            data = line.split(" ") # save data
            t.append(float(data[0])) # save in time array
            result.append(float(data[1])) # save in result array

    # plot results
    t_1= numpy.linspace(0, 0.6, 1000)
    y = 2+4*numpy.cos(2.*pi*(15)*t_1-(pi/5))+3*numpy.sin(2.*pi*(20)*t_1)+4*numpy.cos(2.*pi*(30)*t_1-(pi/3))
    pyplot.figure(dpi=100, figsize=(8, 6))
    pyplot.plot(t, result, 'r', label=rf'Smp '+"$fs = {}$".format(round((1/(t[1]-t[0])), 4)), linewidth=2)
    pyplot.plot(t_1, y, '--', label=rf'signal')
    pyplot.title("Assignment_1")
    pyplot.xlabel(r'$t$ (sec)')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Assignment_1.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)



