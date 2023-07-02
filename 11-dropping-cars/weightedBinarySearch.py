import logging as lg
import csv
import sys
import math

CAR_COST = 14999
DROP_COST = 6138
BUILDING_HEIGHT = 92
NUMBER_OF_CARS = 2
WEIGHT = (DROP_COST)/((CAR_COST + DROP_COST) + DROP_COST)

handler = lg.StreamHandler(sys.stdout)
handler.setLevel(lg.DEBUG)

logger = lg.getLogger("searchLogger")
logger.setLevel(lg.DEBUG)
logger.addHandler(handler)

def linearSearch(target, bottom, top):
    floor = bottom
    total_cost = 0
    logger.debug(f"Linear search from {bottom} to {top}")
    while (True):
        if (floor == top):
            break
        total_cost += DROP_COST
        if (floor+1 > target):
            total_cost += CAR_COST
            break
        floor += 1
    return floor, total_cost

def weightedBinarySearch(target, bottom, mid, top, total_cost, trace):
    trace += f"\n{bottom} {mid} {top}"
    if (bottom == top-1):      
        trace += f" result: {bottom} ({'correct' if bottom==target else 'incorrect'})"
        return bottom, total_cost, trace
    total_cost += DROP_COST
    if (mid > target):
        total_cost += CAR_COST
        top = mid
        mid = math.ceil(bottom + ((WEIGHT) * (top - mid)))
        trace += " broke"
    elif (mid <= target):
        bottom = mid
        mid = math.ceil(mid + ((top - mid) * (WEIGHT)))
        trace += " survived"
    # clamp mid. difference should never be less than 2
    mid = max(bottom+1, min(mid, top))
    return weightedBinarySearch(target, bottom, mid, top, total_cost, trace)


def doWeightedBinarySearch(target):
    bottom, mid, top = 1, math.ceil(BUILDING_HEIGHT * WEIGHT), BUILDING_HEIGHT +1
    total_cost, trace = 0, ""
    logger.debug(f"Binary search, target={target}")
    result, cost, trace = weightedBinarySearch(target, bottom, mid, top, total_cost, trace)
    if (result != target):
        raise RuntimeError(f"Found incorrect floor {result} when searching for {target}. \nTrace: {trace}")
    
    logger.debug(f"Trace: {trace}")
    return result, cost

def testWeightedBinarySearch(filename):
    results = []
    errors = 0
    for target in range(1, BUILDING_HEIGHT+1):
        try:
            result, cost = doWeightedBinarySearch(target)
            logger.info(f"Found floor {result} at a cost of ${cost}")
            results.append((target, cost))
        except Exception as e:
            errors += 1
            logger.error(f"{e}")

    logger.info(f"Test Finished with {errors} errors")
    with open(f'{filename}.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['Floor', 'Cost'])
        writer.writerows(results)

def main():
    logger.setLevel(lg.INFO)
    testWeightedBinarySearch("weightedBinary92")


    logger.setLevel(lg.DEBUG)
    print("Start Debug (press q to exit)")
    print("Enter the target floor... ")
    for line in sys.stdin:
        if "q" in line.strip(): return 0
        result, cost = doWeightedBinarySearch(int(line.strip()))            
        logger.info(f"Found floor {result} at a cost of ${cost}")
        print("\nEnter the target floor... ")


if (__name__ == "__main__"):
    main()