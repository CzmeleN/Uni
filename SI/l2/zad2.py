from collections import deque
import random

def get_dir(m):
    if m == 'U':
        return (-1, 0)
    if m == 'D':
        return (1, 0)
    if m == 'L':
        return (0, -1)
    return (0, 1)

def get_move(dx, dy):
    if dx == -1:
        return 'U'
    if dx == 1:
        return 'D'
    if dy == -1:
        return 'L'
    return 'R'

def lower_uncertanity(labirynth, sizes):
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    # min = float("inf")
    starting = []
    for i in range(sizes[0]):
            for j in range(sizes[1]):
                if labirynth[i][j] == 'S' or labirynth[i][j] == 'B':
                    starting.append((i, j))
    pos = starting
    path = ''
    # path = "U" * sizes[0] + "L" * sizes[1] + "D" * sizes[0]
    # for move in path:
    #     (dx, dy) = get_dir(move)
    #     new_pos = []
    #     # zamienic z formuly bfs-like na formule pod random
    #     for (x, y) in pos:
    #         new_x, new_y = x + dx, y + dy
    #         if labirynth[new_x][new_y] != '#':    
    #             if (new_x, new_y) not in new_pos:
    #                 new_pos.append((new_x, new_y))
    #         elif (x, y) not in new_pos:
    #             new_pos.append((x, y))
    #     pos = new_pos
    starting = pos
    tuple_start = tuple(starting)
    queue = deque([(tuple_start, path)])
    visited = {tuple_start}
    lowest = float("inf")
    while(queue):
        pos, path = queue.popleft()
        if len(pos) > lowest:
            continue
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
        # print(path)
        with open("zad_output.txt", 'w') as o:
            o.write(path)