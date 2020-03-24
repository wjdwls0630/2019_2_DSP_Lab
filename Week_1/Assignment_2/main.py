import numpy
from matplotlib import pyplot
from math import cos, pi

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

    #base = []
    #for i in t:
    #    base.append(cos(2.*pi*200.*i))
    t_1= numpy.linspace(0, 0.015, 1000)
    y=numpy.cos(2*pi*200*t_1)*numpy.sin(2*pi*1600*t_1)
    #base = 1+numpy.cos(2*pi*200*t_1)
    # plot results
    pyplot.figure(figsize=(8, 6))
    pyplot.plot(t, result, 'r', label=rf'Smp '+"$fs = {}$".format(round((1/(t[1]-t[0])), 4)), linewidth=2)
    pyplot.plot(t_1, y, '--', label=rf'signal')
    pyplot.title("Assignment_2")
    pyplot.xlabel(r'$t$ (sec)')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Assignment_2.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)



