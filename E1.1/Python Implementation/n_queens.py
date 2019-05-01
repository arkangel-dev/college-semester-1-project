# N-Queens Algorithim
import int_functions as inFunct
import matplotlib.pyplot as plt
import numpy as np
import time

# input_col = input("Enter the column : ")
queen_pos_list = []
temp_queen_pos_list = []


board_bound = 100
ceiling_bound = board_bound + 1

# according to the rules of the problem the
# first queen will have to set on a column of the first row...
input_coord_x = -1
while ((input_coord_x > board_bound) or (input_coord_x < 0)):
    input_coord_x = int(input("Enter the column (0 - 7) : "))
    if ((input_coord_x > board_bound) or (input_coord_x < 0)):
        print("Enter a valid input, dumbass")
input_coord_y = board_bound

initial_queen_x = input_coord_x
initial_queen_y = input_coord_y

# append the first queen's postion
# to the queen postion array... because duh...
queen_pos_list.append((input_coord_x, 7))
# netsh wlan show networks bssid

# data = inFunct.get_attack_data((input_coord_x,input_coord_y))

# # convert the output from the
# # function. Aka just splitting a
# # 2 dimensional array into 
# # 2 different arrays
# xo = []
# yo = []
# for x in data:
#     xo.append(x[0])
#     yo.append(x[1])


# # ///////// ATTEMPT 1 FAIL ///////////
# for y_test_data in range(0, 8):
#     for x_test_data in range(0,8):
#         for curr_queen in queen_pos_list:
#             queensAttackTiles = inFunct.get_attack_data(curr_queen)
#             testing_data = [x_test_data, y_test_data]
#             if testing_data in queensAttackTiles:
#                 print(str(testing_data) + " << Queen:" + str(curr_queen) + ": Attackable position")
#             else:
#                 temp_queen_pos_list.append((x_test_data, y_test_data))
#                 print(str(testing_data) + " !< Queen:" + str(curr_queen) + ": Valid Position Found")
#             # time.sleep(0.25)


# # /////// ATTEMPT 2 FAIL //////////
# for queen in queen_pos_list:
#     x = None
#     for x_test_tile in range(0,8):
#         for y_test_tile in range(0,8):
#             current_tile = [x_test_tile, y_test_tile]
#             attackable_tile_list = inFunct.get_attack_data(queen)
#             if current_tile in attackable_tile_list:
#                 queen_pos_list.append(current_tile)
#                 print("Tile Found : " + str(current_tile))
#             else:
#                 print("Attackable Tile")

# this parsing system works...
# not perfectly... but pretty good
# the outputs are all the for each run
# but the output is still valid
attackable_tile_list = []
attackable_tile_list_raw = []
for y_test_tile in range(0,board_bound):
    for x_test_tile in range(0,board_bound):
        current_tile = [x_test_tile, y_test_tile]
        attackable_tile_list_raw = inFunct.get_listed_attack_data(queen_pos_list)
        attackable_tile_list = []
        for queen in attackable_tile_list_raw:
            for tile in queen:
                attackable_tile_list.append(tile)
        if current_tile in attackable_tile_list:
            print(str(current_tile) + " << : Vulnurable Position")
            x = None
        else:
            print(str(current_tile) + " !< : Safe Position")
            queen_pos_list.append(current_tile)

# set the graph axis scales
# of the scatter plot. Because
# the default scales are a bit
# rectangular
fig_size = plt.rcParams["figure.figsize"]
fig_size[0] = 5.25
fig_size[1] = 5
plt.rcParams["figure.figsize"] = fig_size

# create a list of all the attack
# tiles...
attackable_tile_list = inFunct.get_listed_attack_data(queen_pos_list)

attackable_tile_list_x = []
attackable_tile_list_y = []
# create a list for the matploitlib
# to print (attackable tiles)
for queen in attackable_tile_list:
    for tiles in queen:
        attackable_tile_list_x.append(tiles[0])
        attackable_tile_list_y.append(tiles[1])

# create a list for the matplotlib
# to control (queen positions)
queen_pos_list_x = []
queen_pos_list_y = []
for x in queen_pos_list:
    queen_pos_list_x.append(x[0])
    queen_pos_list_y.append(x[1])

# for x in temp_queen_pos_list:
#     queen_pos_list_x.append(x[0])
#     queen_pos_list_y.append(x[1])

# print the count
# of queens placed safely
# on the chessboard
print("Number of placed safe queens : " + str(len(queen_pos_list)))

# define the input scatter data
# The black scatters for the Queen Positions
# and the red scatters for the attackable positions
plt.scatter(attackable_tile_list_x, attackable_tile_list_y, s=(np.pi * 3), c=(1,0,0), alpha=0.1)
plt.scatter(queen_pos_list_x, queen_pos_list_y, s=(np.pi * 3), c=(0,0,0), alpha=1)
plt.scatter(initial_queen_x, initial_queen_y, s=(np.pi * 5), c=(0,1,0), alpha=1)


# define the parameters
# of the scatter plot diagram...
plt.title('Chess Board (N-Queens Problem)')
plt.xlabel('x')
plt.ylabel('y')

# plt.grid()
# print(inFunct.get_listed_attack_data(queen_pos_list))
# show the catter plot
plt.show()

