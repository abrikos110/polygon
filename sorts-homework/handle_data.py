import sys
import numpy
import matplotlib
import matplotlib.pyplot as plt

data = (sys.stdin.read()
        .replace('swaps=', '')
        .replace('cmps=', '')
        .replace('ftype=', '')
        .replace('n=', '')
        .split('\n'))

*data, = map(str.split, data)
*data, = filter(len, data)
classes = set(map(lambda x: x[0], data))
data = {cl: list(map(lambda x: x[1:],
                     filter(lambda x: x[0] == cl, data))) for cl in classes}

for cl in data:
    data[cl] = numpy.array(data[cl], dtype=numpy.int64)

for cl in data:
    print(cl)
    print('n,Параметр,Номер сгенерированного массива,,,,Среднее значение')
    print(',,1,2,3,4')
    for n in range(1, 9):
        n = 10 ** n
        row = filter(lambda x: x[3] == n, data[cl])
        row = sorted(row, key=lambda x: x[2])
        *cmps, = map(lambda x: x[1], row)
        *swaps, = map(lambda x: x[0], row)
        print('{},Сравнения,{},{}'.format(
            str(n),
            ','.join(map(str, cmps)),
            sum(cmps) / len(cmps)))
        print(',Перемещения,{},{}'.format(
            ','.join(map(str, swaps)),
            sum(swaps) / len(swaps)))
    print()

for i in range(2):
    for stype in data:
        for ftype in range(1, 5):
            d = data[stype]
            d = d[d[:,2].T == ftype].T
            x = d[3]
            y = d[i]
            lbl = [0, 'sorted', 'sorted, reversed', 'random', 'random'][ftype]
            lbl = stype + ', ' + lbl
            ftype = min(ftype, 3) - 1
            color = (stype[0] != 's', ftype & 1, (ftype & 2)/2)
            plt.plot(x, y, label=lbl, color=color)
            plt.scatter(x, y, color=color, alpha=0.3)
    plt.legend()
    plt.xscale('log')
    plt.yscale('log')
    plt.grid(True, axis='both', which='both')
    plt.title(['swaps', 'comparisons'][i])
    plt.show()
