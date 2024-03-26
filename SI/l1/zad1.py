from collections import deque
import argparse

"""program wykorzystuje algorytm bfs, w liscie (secie) odwiedzonych
stanow przechowuje takze informacje o dlugosci trasy do tego stanu
oraz o jego poprzedniku co pozwala w latwy sposob sprawdzic trase"""

def in_bounds(move):
    if move[0] >= 0 and move[0] <= 7 and move[1] >= 0 and move[1] <= 7:
        return True
    else:
        return False

def new_pos(src, color, figure, move):
    res = src.copy()
    res[0] = color
    res[figure] = move
    return res 

def generate_moves(position):
    # wykluczamy bicie z ruchow
    taken = [position[1], position[2], position[3]]
    possible = []
    possible_wk = []
    possible_bk = []
    kdx = [-1, 0, 1]
    kdy = [-1, 0, 1]

    for dx in kdx:
        for dy in kdy:
            move = (position[1][0] + dx, position[1][1] + dy)
            if in_bounds(move) and move not in taken:
                possible_wk.append(move)

            move = (position[3][0] + dx, position[3][1] + dy)
            if in_bounds(move) and move not in taken:
                possible_bk.append(move)

    if position[0] == "white":
        td = range(-7, 8)

        for x in td:
            move = (position[2][0] + x, position[2][1])
            if in_bounds(move) and move not in taken:
                possible.append(new_pos(position, "black", 2, move))

            move = (position[2][0], position[2][1] + x)
            if in_bounds(move) and move not in taken:
                possible.append(new_pos(position, "black", 2, move))

        for move in possible_wk:
            if move not in possible_bk:
                possible.append(new_pos(position, "black", 1, move))
    else:
        for move in possible_bk:
            if move[0] != position[2][0] and move[1] != position[2][1] and move not in possible_wk:
                possible.append(new_pos(position, "white", 3, move))

    return possible

def checkmate(position):
    wr = position[2]
    bk = position[3]

    if (wr[0] == bk[0] or wr[1] == bk[1]) and abs(wr[0] - bk[0]) + abs(wr[1] - bk[1]) > 1:
        return True
    else:
        return False

def print_board(position):
    for x in range(8):
        for y in range(8):
            if (x, y) == position[1]:
                sign = 'K'
            elif (x, y) == position[2]:
                sign = 'R'
            elif (x, y) == position[3]:
                sign = 'k'
            else:
                sign = '.'
            print(sign, end = ' ' * 3)
        print('\n')
    line = '-' * 3 * 10
    print(line + '\n')

def bfs(start, debug):
    visited = set()
    queue = deque([start])
    tuple_start = tuple(start)
    visited.add(tuple_start)
    depths = {tuple_start: (0, ())}

    while queue:
        curr = queue.popleft()
        tuple_curr = tuple(curr)
        adjs = generate_moves(curr)
        curr_depth = depths[tuple_curr][0]
        
        if not adjs:
            if not checkmate(curr):
                continue
            if debug:
                optimal_moves = deque([tuple_curr])
                i = curr_depth
                while i > 0:
                    tuple_curr = depths[tuple_curr][1]
                    optimal_moves.appendleft(tuple_curr)
                    i -= 1
                for position in optimal_moves:
                    print_board(position)
            return curr_depth

        for adj in adjs:
            tuple_adj = tuple(adj)
            if tuple_adj not in visited:
                visited.add(tuple_adj)
                queue.append(adj)
                depths.update({tuple_adj: (curr_depth + 1, tuple_curr)})
    return -1        

def pos_pair(txt):
    return (ord(txt[0]) - ord('a'), ord(txt[1]) - ord('0') - 1)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Program with debug option")
    parser.add_argument("-d", "--debug", action="store_true", help="Enable debug mode")
    args = parser.parse_args()
    if args.debug:
        debug = True
    else:
        debug = False

    with open("zad1_input.txt") as f:
        with open("zad1_output.txt", 'w') as o:
            for line in f:
                start = [line[:5], pos_pair(line[6:8]), pos_pair(line[9:11]), pos_pair(line[12:14])]
                if not generate_moves(start):
                    o.write("inf")
                else:
                    #o.write(str(bfs(start, debug)))
                    print(bfs(start, debug))