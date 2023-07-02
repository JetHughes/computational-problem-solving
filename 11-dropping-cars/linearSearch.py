import logging as lg
import csv
import sys

CAR_COST = 14999
DROP_COST = 6138
BUILDING_HEIGHT = 100
NUMBER_OF_CARS = 2

def two_step_incremental_linear_search(highest_safe_floor, initial_floor):
    """
    Args:
        highest_safe_floor (int): The target floor to find
        inital_floor (int): The amount to increment when we are using the first car

    Returns:
        int: The cost of the seach in dollars
    """
    total_cost, current_highest,  = 0, 0
    increment = initial_floor
    cars_remaining = NUMBER_OF_CARS
    lg.debug(f"Searching for: {highest_safe_floor} using initial floor {initial_floor}")
    while(True):                
        if(current_highest + increment > BUILDING_HEIGHT and increment != 1):
            lg.debug(f"Increment is too large for building, continuing with intervals of 1")  
            increment = 1
        if(current_highest == BUILDING_HEIGHT):
            lg.debug(f"Found floor {current_highest} at a cost of ${total_cost}")
            return current_highest, total_cost
        
        lg.debug(f"Drop car at floor {current_highest} + {increment}. Total cost={total_cost} + {DROP_COST}")            
        total_cost += DROP_COST
        if(current_highest + increment > highest_safe_floor):
            lg.debug(f"Car broke at floor {current_highest+increment}. Total cost={total_cost} + {CAR_COST} + {DROP_COST}")
            total_cost += CAR_COST
            cars_remaining -= 1 
            if(cars_remaining == 0 or (current_highest + increment == BUILDING_HEIGHT and increment == 1)):
                lg.debug(f"Found floor {current_highest} at a cost of ${total_cost}")
                return current_highest, total_cost
            lg.debug(f"{cars_remaining} cars remaining")
            increment = 1
        else:
            current_highest += increment
            increment -= 1 if increment > 1 else 0
            


def linear_search(highest_safe_floor, floor_increment) -> int:
    """
    Drop the first car from incrementally higher floors until it breaks. When the 
    first car breaks, we have a range in which the highest floor must lie. We then 
    use the second car to test each floor in the range, starting at the lowest floor.

    Args:
        highest_safe_floor (int): The target floor to find
        floor_increment (int): The amount to increment when we are using the first car

    Returns:
        int: The cost of the seach in dollars
    """
    total_cost, current_highest = 0, 0

    cars_remaining = NUMBER_OF_CARS
    lg.debug(f"Linearly searching for: {highest_safe_floor} using inital increment of {floor_increment}")
    while (True):
        # Check if the car will break when we increase the floor
        lg.debug(f"Drop car at floor {current_highest}. Total cost={total_cost} + {DROP_COST}")
        total_cost += DROP_COST
        if (current_highest + floor_increment > highest_safe_floor):
            lg.debug(f"Car broke at floor {current_highest+floor_increment}")
            lg.debug(f"Total cost={total_cost} + {CAR_COST}")
            total_cost += CAR_COST
            cars_remaining -= 1
            if (cars_remaining == 0):
                lg.debug(f"Found floor {current_highest} at a cost of ${total_cost}")
                return total_cost
            lg.debug(f"{cars_remaining} cars remaining")
            floor_increment = 1
        else:
            # If the car wont break move up to the next floor
            current_highest += floor_increment

def testLinearSearch():
    results = []
    for increment in range(1, BUILDING_HEIGHT):  # (1, 2, 4, 10, 20, 25, 50):
        for highest_safe_floor in range(1, BUILDING_HEIGHT+1):
            cost = linear_search(highest_safe_floor, increment)
            results.append((highest_safe_floor, cost, increment))

    with open('fineincrement2.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['Floor', 'Cost', 'Increment'])  # Write column headers
        writer.writerows(results)  # Write the results row by row
    
def testLinearSearchTwo():
    results = []
    for increment in (10, 11, 12, 13, 14, 15, 16, 17, 20, 25, 30, 35, 40, 45, 50):
        for highest_safe_floor in range(1, BUILDING_HEIGHT+1):
            result, cost = two_step_incremental_linear_search(highest_safe_floor, increment)
            if result != highest_safe_floor:
                lg.error(f"When searching for {highest_safe_floor}, found {result} at cost of {cost} using initial floor {increment}")
            results.append((highest_safe_floor, cost, increment))

    lg.info(f"Test Finished")
    with open('linearTwoCoarse.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['Floor', 'Cost', 'Increment'])
        writer.writerows(results)

def main():
    lg.basicConfig(level=lg.INFO)
    testLinearSearchTwo()
    testLinearSearch()

    for line in sys.stdin:
        if line.strip() == "q": return 0
        safe, inital_floor =  line.split()
        result, cost = two_step_incremental_linear_search(int(safe), int(inital_floor))
        lg.info(f"Found floor {result} at a cost of ${cost}")

if (__name__ == "__main__"):
    main()