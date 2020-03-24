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

    t_ori = numpy.linspace(0, 0.06, 1000)
    y_ori = 2*numpy.cos(2.*pi*50*t_ori+(pi/2))+numpy.cos(2*pi*150*t_ori)

    # plot results
    pyplot.figure(dpi=100, figsize=(8, 6))
    pyplot.plot(t, result, label=rf'Smp '+"$fs = {}$".format(1/(t[1]-t[0])), linewidth=2)
    pyplot.plot(t_ori, y_ori, '--', label=rf'original' )
    pyplot.title("Lab01_2")
    pyplot.xlabel(r'$t$ (sec)')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Lab01_2.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)



