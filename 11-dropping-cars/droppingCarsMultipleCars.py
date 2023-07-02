import math
import numpy as np
import matplotlib.pyplot as plt
import logging as lg
lg.basicConfig(level=lg.CRITICAL)

def constructTree(gapSize, maxSafe, building_height, dropCost, carCost):
    found = False
    firstLeft = False
    tested = []

    current = math.ceil(gapSize)
    prior = 0

    width = current

    leftTurn = 0
    rightTurn = 0


    while not (width <= 3):
        lg.debug(current)
        tested.append(current)
        prior = current
        if current <= maxSafe:
            if (not firstLeft and building_height-current > gapSize):
                current = min(building_height, math.ceil(current + gapSize))
            else:
                current = min(building_height, math.ceil(current + width/2.0)) #NOTE THIS IS THE WIDTH FROM THE PREVIOUS ITERATION
            rightTurn += 1

        else:
            current = max(1, math.floor(current - width/2.0)) #NOTE THIS IS THE WIDTH FROM THE PREVIOUS ITERATION
            firstLeft = True
            leftTurn += 1

        width = abs((prior - current)) #updating width


    currentCond = True  #excludes stopping on the first execution
    while(currentCond and not current < 1 and not current > building_height):
        lg.debug(current) #LAST FLOOR TO BE TESTED
        tested.append(current)
        if current <= maxSafe:
            current += 1
            rightTurn += 1
        else:
            current -= 1
            leftTurn += 1

        currentCond = not current in tested
    
    return leftTurn*(dropCost + carCost) + rightTurn*(dropCost), leftTurn

def main():
    building_height = 92
    gapSize = building_height/7.0
    dropCost = 6138
    carCost = 14999

    costs = []
    cars = []
    maxSafe = 1
    while maxSafe < building_height:
        cost, used_cars = constructTree(gapSize, maxSafe, building_height, dropCost, carCost)
        costs.append(cost)
        cars.append(used_cars)
        maxSafe += 1

    # print("TEST EXECUTION")
    # print(constructTree(gapSize, 65, n, dropCost, carCost))
    max_index = costs.index(max(costs))
    print(f"max cost: {max(costs)} at floor {max_index+1} with {cars[max_index]} cars")
    print(np.mean(costs))
    # print(costs.index(max(costs)))

    # results = []
    # for gap in range(1, building_height):
    #     for floor in range(1, building_height):
    #       results.append(constructTree(gap, floor, n, dropCost, carCost))

    x = list(range(1,building_height))
    plt.plot(x, costs)
    plt.show()



main()