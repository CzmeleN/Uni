from collections import deque
import random

def make_moves(labirynth, poses, move):
    new_poses = []
    dx = 0
    dy = 0

    if move == 'U':
        dx = -1
    elif move == 'D':
        dx = 1
    elif move == 'L':
        dy = -1
    else:
        dy = 1

    for i in range(len(poses)):
        old_pos = poses[i]
        new_pos = (old_pos[0] + dx, old_pos[1] + dy)
        if labirynth[new_pos[0]][new_pos[1]] == '#':
            new_pos = old_pos
        if new_pos not in new_poses:
            new_poses.append(new_pos)

    return new_poses

def get_move(dx, dy):
    if dx == -1:
        return 'U'
    if dx == 1:
        return 'D'
    if dy == -1:
        return 'L'
    return 'R'

def lower_uncertanity(labirynth, sizes):
    # moves = ['U', 'D', 'L', 'R']
    # min = float("inf")
    starting = []
    for i in range(sizes[0]):
            for j in range(sizes[1]):
                if labirynth[i][j] == 'S' or labirynth[i][j] == 'B':
                    starting.append((i, j))
    # active = True
    # while(active):
    #     path = ""
    #     poses = starting.copy()
    #     for j in range(80):
    #         path += random.choice(moves)
    #     for move in range(len(path)):
    #         poses = make_moves(labirynth, poses, path[move])
    #         if len(poses) == 3:
    #             path = path[:move]
    #             active = False
    #             break
    # print("done")
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    tuple_start = tuple(starting)
    queue = deque([(tuple_start, "")])
    visited = {tuple_start}

    while(queue):
        pos, path = queue.popleft()
        lowest = len(pos)
        
        if lowest == 1:
            break

        for dx, dy in directions:
            new_pos = []
            for (x, y) in pos:
                new_x, new_y = x + dx, y + dy
                if labirynth[new_x][new_y] != '#':    
                    if (new_x, new_y) not in new_pos:
                        new_pos.append((new_x, new_y))
                elif (x, y) not in new_pos:
                    new_pos.append((x, y))
            tuple_pos = tuple(new_pos)
            if tuple_pos in visited:
                continue
            new_len = len(new_pos)
            if new_len < lowest:
                lowest = new_len
                queue.clear()
            queue.append((tuple_pos, path + get_move(dx, dy)))
            visited.add(tuple_pos)

    return (pos[0], path)

def generate_path(labirynth, sizes):
    start_pos, start_path = lower_uncertanity(labirynth, sizes)
    # print(start_path)
    # return "RL"
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    tuple_start = tuple(start_pos)
    queue = deque([(tuple_start, start_path)])
    visited = {tuple_start}

    while(queue):
        (x, y), path = queue.popleft()
        curr = labirynth[x][y]

        if curr == 'G' or curr == 'B':
            break
        
        for dx, dy in directions:
            new_x, new_y = x + dx, y + dy
            if labirynth[new_x][new_y] != '#':
                if (new_x, new_y) not in visited:
                    queue.append(((new_x, new_y), path + get_move(dx, dy)))
                    visited.add((new_x, new_y))

    return path

if __name__ == "__main__":
    with open("zad_input.txt") as f:
        labirynth = f.readlines()
        path = generate_path(labirynth, (len(labirynth), len(labirynth[0]) - 1))
        print(path)
        with open("zad_output.txt", 'w') as o:
            o.write(path)