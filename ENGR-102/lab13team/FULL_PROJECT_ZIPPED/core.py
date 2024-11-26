# # By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Alvaro Medina Fundora
# Section:      201
# Assignment:   Lab 12-2
# Date:         18 11 2024
#

import copy
import random

# Setup for before the game starts
coordsFile = open("gameCoordinates.txt", 'r')
linesList = coordsFile.readlines()
for i in range(len(linesList)):
    linesList[i] = linesList[i].replace("\n", "")

colorCoords = {}  # "Green":"", "Yellow":"", "Blue":"", "Red":""}
colorCodesList = ["GA", "YA", "BA", "RA"]
winningCodes = ["GW", "YW", "BW", "RW"]
colors = ["green", "yellow", "blue", "red"]
winningCoords = {}  # Dictionary of coordinates where each color ends up
regularCoords = []  # Coordinates on the board through which the pieces move
startingSpot_perColor = {'green': ["58", "345"], 'yellow': [
    "86", "59"], 'blue': ["372", "88"], 'red': ["343", "374"]}
j = 0
i = 0
k = 0
while i < len(linesList):
    linesList[i] = linesList[i].strip()
    if ("." in linesList[i]):
        regularCoords.append(linesList[i][2:].split('x'))
    # print(i,j)
    if (j < 4 and colorCodesList[j] in linesList[i]):
        # print(linesList[i])
        colorCoords[colors[j]] = [linesList[i][3:].split('x'), linesList[i+1][3:].split(
            'x'), linesList[i+2][3:].split('x'), linesList[i+3][3:].split('x')]
        j += 1
        i += 3
    if (winningCodes[k] in linesList[i]):
        # print(linesList[i])
        winningCoords[colors[k]] = [linesList[i][3:].split('x'), linesList[i+1][3:].split(
            'x'), linesList[i+2][3:].split('x'), linesList[i+3][3:].split('x')]
        k += 1
        i += 3
    i += 1

for i in range(len(regularCoords)):
    if ("." in regularCoords[i][0]):
        regularCoords[i][0] = regularCoords[i][0].replace(".", "")

startingCoords = copy.deepcopy(colorCoords)

homePieces = {'green': 4, 'yellow': 4, 'blue': 4, 'red': 4}
winningPiecesCounter = {'green': 0, 'yellow': 0, 'blue': 0, 'red': 0}


def checkOpen(givenCoordinate):
    """Check if a given coordinate is open and return true or false based on such"""
    # print("Checking if open")
    for value in colorCoords.values():
        for coords in value:
            # print(coords, givenCoordinate)
            if (coords == givenCoordinate):
                return False
    return True


def getColor(coordinate):
    """Return the color of a piece at a given coordinate"""
    for key in colorCoords.keys():
        for eachCoordinate in colorCoords[key]:
            print(eachCoordinate, coordinate)
            if (eachCoordinate == coordinate):
                return key


def takeOutPiece(color):

    if (checkOpen(startingSpot_perColor[color])):

        homePieces[color] -= 1
        colorCoords[color][homePieces[color]] = startingSpot_perColor[color]

    elif (getColor(startingSpot_perColor[color]) == color):
        print("Cannot take out a piece right now")
    else:
        homePieces[getColor(startingSpot_perColor[color])] += 1
        for color in colorCoords:
            counter = 0
            for coord in colorCoords.values():

                if (coord == startingSpot_perColor[color]):
                    colorCoords[color][counter] = startingSpot_perColor[getColor(
                        startingSpot_perColor[color])][homePieces[getColor(startingSpot_perColor[color])]]
                counter += 1


def getRegularCoordsPositionIndex(color, piece):
    for index, coord in enumerate(regularCoords):
        if coord == colorCoords[color][4-int(piece)]:
            return index
    print("None of your pieces are in the regular spots.")


def rollDice():
    """This function returns a random interger between one and six, like a dice"""
    return random.randint(1, 6)


def move(color, jumps, piece):
    print(color)
    # piece = input(
    #     "Which of your available pieces would you like to move. Enter 1 through 4: ")
    try:
        if (checkOpen(regularCoords[(getRegularCoordsPositionIndex(color, piece) + jumps) % 27])):
            colorCoords[color][4-int(piece)] = regularCoords[(
                getRegularCoordsPositionIndex(color, piece) + jumps) % 27]
        elif (getColor(regularCoords[(getRegularCoordsPositionIndex(color, piece) + jumps) % 27]) == color):
            print(f'This piece cannot be moved {jumps} spaces forward')
        else:
            for eachColor in colorCoords.keys():
                newCounter = 0
                for coord in eachColor:
                    if (coord == regularCoords[(getRegularCoordsPositionIndex(color, piece) + jumps) % 27]):
                        homePieces[eachColor] += 1
                        colorCoords[eachColor][newCounter] = startingCoords[eachColor][newCounter]
                    newCounter += 1
            colorCoords[color][4-int(piece)] = regularCoords[(
                getRegularCoordsPositionIndex(color, piece) + jumps) % 27]

    except:
        print("Some invalid input was given to the function")
        # return move(color, jumps, )

#states
NOPLAY = 1
TAKEOUT = 2
MOVE = 3
TAKEORMOVE = 4

import time

def turn(color, dice):
    """This function will be used everytime that a player has to take a turn"""
    # dice = rollDice()
    # dice=6
    if (dice == 6 and homePieces[color] >= 0 and homePieces[color] < 4):
        print(color)
        # choice = input(
            # "If you would like to take out a piece, type \"take\", otherwise type \"move\": ")
        # if (choice == "take"):
            # takeOutPiece(color)
        # else:
            # move(color, dice)
        return TAKEORMOVE, "Choose to take out\n a piece or move", (lambda piece: takeOutPiece(color) if int(piece) == 0 else move(color, dice, piece))
    elif (dice == 6 and (homePieces[color] == 4) and checkOpen(startingSpot_perColor[color])):
        print(f'A {color} piece has been\ntaken out.')
        takeOutPiece(color)
        return TAKEOUT, f"A {color} piece has\nbeen taken out", (lambda piece: piece)
    elif (homePieces[color] < 4):
        return MOVE, "Choose a peice", ( lambda piece : move(color, dice, piece) )
    else:
        # print("Can't play right now.")
        return NOPLAY, f"{color} cant play\nright now", (lambda peice: peice)


def win(color, piece, jumps):
    colorIndex = {'green': [25, 26, 27], 'red': [
        18, 19, 20], 'blue': [11, 12, 13], 'yellow': [4, 5, 6]}
    if (colorCoords[color][4 - int(piece)] == regularCoords[colorIndex[color][0]] and jumps >= 3):
        if (checkOpen(winningCoords[color][int(jumps)-3])):
            colorCoords[color][4-int(piece)] == winningCoords[jumps-3]
            winningPiecesCounter[color] += 1
        else:
            print("This spot is not open and you must roll either higher or lower.")
    elif (colorCoords[color][4 - int(piece)] == regularCoords[colorIndex[color][0]] and jumps >= 2):
        if (checkOpen(winningCoords[color][int(jumps)-2])):
            colorCoords[color][4-int(piece)] == winningCoords[jumps-2]
            winningPiecesCounter[color] += 1
        else:
            print("This spot is not open and you must roll either higher or lower.")
    elif (colorCoords[color][4 - int(piece)] == regularCoords[colorIndex[color][0]] and jumps >= 1):
        if (checkOpen(winningCoords[color][int(jumps)-1])):
            colorCoords[color][4-int(piece)] == winningCoords[jumps-1]
            winningPiecesCounter[color] += 1
        else:
            print("This spot is not open and you must roll either higher or lower.")
    if (winningPiecesCounter[color] == 4):
        print(f'Congrats, {color} has won the game')
        return False


def main():
    win = True
    # print(homePieces['green'])
    while (win):
        turn('green')
        if (winningPiecesCounter['green'] == 4):
            win = False
        turn('yellow')
        if (winningPiecesCounter['yellow'] == 4):
            win = False
        turn('blue')
        if (winningPiecesCounter['blue'] == 4):
            win = False
        turn('red')
        if (winningPiecesCounter['red'] == 4):
            win = False
    # print("Run plz?")


if __name__ == "__main__":
    main()
