import numpy
from matplotlib import pyplot

try :
    t = []
    result = []
    with open("cmake-build-debug/data.txt", 'r') as dataFile:
        while True :
            line = dataFile.readline() # read one line

            if not line:
                break

            data = line.split(" ") # save data
            t.append(float(data[0]))
            result.append(float(data[1]))

    # plot results
    pyplot.figure(dpi=100, figsize=(8, 6))
    pyplot.plot(t, result, label=rf'Sampling')
    pyplot.title("Lab01_1")
    pyplot.xlabel(r'$t$ (sec)')
    pyplot.ylabel(r'$y$')
    pyplot.legend()
    pyplot.grid()
    pyplot.savefig("Lab01_1.png")
    pyplot.show()

except FileNotFoundError as e:
    print(e)



