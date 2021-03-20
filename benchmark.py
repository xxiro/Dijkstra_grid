import os
import datetime
import matplotlib.pyplot as plt
from typing import *


slow_values = list(map(lambda x: x*100,range(1,11)))
fast_values = list(map(lambda x: x*10,range(1,11)))

values = fast_values


if __name__ == "__main__":

    data : List[float] = []


    for v in values:
        os.system("./cmake-build-debug/makeGrid %i %i testGraph.txt testSource.txt"%(v,v/10))
        start = datetime.datetime.now()
        os.system("./cmake-build-debug/dijkstraX -e testGraph.txt -s testSource.txt -w testOut.txt")
        finish = datetime.datetime.now()
        tdiff = finish-start
        print(v, tdiff, tdiff.total_seconds())
        data.append(tdiff.total_seconds())

    plt.plot(values, data)
    plt.show()