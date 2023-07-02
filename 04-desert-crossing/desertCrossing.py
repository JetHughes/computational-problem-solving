import math

def checkIntervals(a):
    for i in range(2,len(a)):
        if not abs((a[i] - a[i-1]) - math.pow(math.e, function(i-1))*(a[i-1]-a[i-2])) < 0.2:
            print(str(a[i-1]) + " to " + str(a[i]) + " FAIL!")

def f(j):
    return 1/j  #THIS is the function we want to change to change distributions

def eNum(k):
    exponent = 0
    for j in range(1,n+1):
        exponent += f(j)
    
    return math.pow(math.e, exponent)   #return ln(math.e) to get rid of the e and just return the exponent (for testing out non exponential trends)

def eTerm(n):
    result = 1
    for k in range(1,n+1):
        result += eNum(k)

    return result


def checkValidSolution4(a,c):
    """
    method to check that we never run out of fuel with the standard procedure

    standard procedure being go to the drop spot, drop 2(n-k)+1*|ak - ak-1| fuel, then drive back

    can't handle stockpiling and stockpiling not needed for this distance anyway
    """
    fail=False
    n = len(a)-1
    for k in range(1,n+1):
        if((2*(n-k) + 3)*(a[k]-a[k-1]) > c):
            print(str(a) + ": FAIL ON " + str((a[k]-a[k-1])))
            fail = True
    
    if(not fail):
        print(str(a) + ": PASS")
    

def calcExpenditure4(a):
    """
    method to calculate fuel expenditure given an array of fuel drop locations for one way trip 

    assumes standard procedure being go to the drop spot, drop 2(n-k)+1*|ak - ak-1| fuel, then drive back

    :param a: integer array
        array of fuel drop positions in litres from start of the desert

    """
    n = len(a)-1
    cost = 0
    for k in range(1,n+1):
        cost += (2*(n-k)+3)*(a[k]-a[k-1])
    
    cost += 140

    return cost


def calcExpenditure5(a):
    """
    calculating the expenditure given an array of fuel drop locations for round trip.

    :params a: integer array
        the array of fuel drop positions in litres from the start of the desert
    """
    numTrips = 0

    tripcost = []   #array which holds the cost of each leg of the journey
    reqArray = []   #array which holds the amount of fuel needed at each depo for a successful run
    tripArray = []  #array which holds the number of trips needed between each depo

    n = len(a)  

    for k in range(1,n):   
        j = n-k 
        distance = a[j] - a[j-1]

        #if the distance between the points is greater than half of the fuel tank, we can't make it, so return FAIL
        if(distance*2 > 140):
            return "FAIL"

        if j == n-1:  #first case for the last drop
            required = 2*distance
        else:
            required = (numTrips*2+2)*distance  #this will be the numTrips from the prior iteration.

        
        thisTrip = math.ceil(required/min(80, (140-2*distance)))    #how many trips does it take to drop the required amount of fuel at the spot, we can drop max of 80L, hence the min function?
        numTrips += thisTrip    #we need enough fuel not only to drop the fuel at the next spot, but also for any trips beyond that from drop sites further up the chain, so need numtrips to be accumulative
        
        #building arrays to show each step of the journey. The only neccessary one is tripcost, the others are for debugging
        reqArray.append(required)
        tripArray.append(thisTrip)
        tripcost.append(thisTrip*2*distance + required)


    #print for debugging
    print(reqArray) 
    print(tripArray)
    print(tripcost)

    return sum(tripcost)





def main():
    d = 2413    #distance
    m = 12      #vehicle mileage
    c = 140     #vehicle fuel capacity

    thresh = c/3 #maybe better as c/3, or maybe better as c/2. Trying to find
    print("threshold: " + str(thresh))

    for n in range(1,10):
        lastDrop = (d-(1/1)*m*c)/m  #half of full tank for the return journey, a full tank for the one way

        a1 = lastDrop/(eTerm(n))
        maxInterval = eNum(n)*a1
        print(str(n) + ": minInterval: " + str(a1) + ", maxInterval: " + str(maxInterval))

        a = [0, a1]
        for k in range(2, n+2):
            a.append(a[k-1] + a1*eNum(k-1))

        #a = [0, 26.776465730086503, 61, 96, 131] #this is the best i've found so far, cost = 1717 NOTE 131.0833333 litres rounded down to 131 in final position

        print(a)
        print(calcExpenditure4(a))
        #print(calcExpenditure5(a))

main()
