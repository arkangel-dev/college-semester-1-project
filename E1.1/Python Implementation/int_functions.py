

def get_attack_data(coordinates):
    board_bound = 100
    ceiling_bound = board_bound + 1

    coord_x = coordinates[0] # split the tuple to two different vairables
    coord_y = coordinates[1]

    output_tiles = [] # define the output tiles array...

    # create a for loop that is slightly out of bounds just to
    # make sure that there are no empty tiles that are attackable
    # but not listed as attackable
    for x in range(0,ceiling_bound): # this is the Vertical and horizontal attack tiles
        output_tiles.append([x, coord_y])
        output_tiles.append([coord_x, x])

    for x in range(0,ceiling_bound): # this is the upper right diagonal attack tiles
        result = [x + coord_x, (x * 1) + coord_y]
        output_tiles.append(result)

    for x in range(0,ceiling_bound): # this is the lower left diagonal attack tiles
        result = [coord_x - x , coord_y - (x * 1)]
        output_tiles.append(result)

    for x in range(0,ceiling_bound): # this is the upper left diagonal attack tiles
        result = [x + coord_x, (x * -1) + coord_y]
        output_tiles.append(result)

    for x in range(0,ceiling_bound): # this is the lower right diagonal attack lines
        result = [coord_x - x, coord_y - (x * -1)]
        output_tiles.append(result)

    final_tiles = [] # define the final attack tiles

    # this will filter out all the attack tile co-ordiantes that are not within the
    # bounds of the chess board. So any attack tiles with either co-ordiantes lower
    # than 0 and/or higher than 7 will be not appened to the final tiles array...
    for x in output_tiles:
        if ((x[0] >= 0) and (x[0] <= board_bound) and (x[1] >= 0) and (x[1] <= board_bound)):
            final_tiles.append(x)

    return(final_tiles) # return the attack data...

def get_listed_attack_data(queen_postions):
    # this function will output the vulnurable
    # tiles as an array of an array. The input
    # is an array of queen's x and y position
    sum_tiles = []
    for queen in queen_postions:
        sum_tiles.append(get_attack_data(queen))
    return(sum_tiles)