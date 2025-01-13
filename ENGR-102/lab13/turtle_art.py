import math
import turtle as t

def parta(angle):
    t.reset()
    t.speed(0)
    t.dot(10, 'red')
    iters, theta = 0, 0
    while True:
        iters += 1
        theta = (theta + angle) % 360

        t.left(angle)
        t.forward(300)

        if abs(theta) < 1e-6:
            break

    return iters


def partb(sequence):
    t.reset()
    t.speed(0)
    t.dot(10, 'red')
    iters, theta = 0, 0
    for char in sequence:
        angle = 30 if char == '0' else -114
        theta = (angle + theta) % 360

        t.left(angle)
        t.forward(100)
    return iters

#print(partb("01001"))

def partc(sequence, angle0, angle1, dist=5):
    t.reset()
    t.speed(0)
    t.dot(10, 'red')

    for char in sequence:
        if char == '0':
            t.left(angle0)
        elif char == '1':
            t.left(angle1)
        t.forward(dist)

if __name__ == "__main__":



    print(parta(160))
    input()

    print(parta(141))
    input()

    partb("01001")
    input()
    partb("01001011")
    input()

    s1 = "".join(['1' + '0' * i for i in range(20)])
    partc(s1, 0, 90)
    input()

    partc(s1, 0, 30)
    input()
    s2 = "".join(['1' + '0' * i for i in range(50)])
    partc(s2, 0, 150)
    input()

    partc(s2, 5, 108)
    input()



    t.done()

