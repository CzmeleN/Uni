from collections import deque
import random

def make_moves(labirynth, poses, move, lowering):
    new_poses = []
    dx = 0
    dy = 0
    for i in range(len(poses)):
        if move == 'U':
            dx = -1
        elif move == 'D':
            dx = 1
        elif move == 'L':
            dy = -1
        else:
            dy = 1
        old_pos = poses[i]
        new_pos = (old_pos[0] + dx, old_pos[1] + dy)
        if labirynth[new_pos[0]][new_pos[1]] == '#':
            new_pos = old_pos
        if lowering:
            if new_pos not in new_poses:
                new_poses.append(new_pos)
        else:
            new_poses.append(new_pos)
    return new_poses
    

def lower_uncertanity(labirynth, sizes):
    moves = ['U', 'D', 'L', 'R']
    min = float("inf")
    starting = []
    for i in range(sizes[0]):
            for j in range(sizes[1]):
                if labirynth[i][j] == 'S' or labirynth[i][j] == 'B':
                    starting.append((i, j))
    active = True
    while(active):
        path = ""
        poses = starting.copy()
        for j in range(110):
            path += random.choice(moves)
        for move in range(len(path)):
            poses = make_moves(labirynth, poses, path[move], True)
            if len(poses) < 2:
                path = path[:move]
                active = False
                break
    return (poses, path)

def generate_path(labirynth, sizes):
    starting = lower_uncertanity(labirynth, sizes)
    print(starting)
    moves = ['U', 'D', 'R', 'L']
    visited = set()
    visited.add(frozenset(starting[0]))
    queue = deque()
    queue.append(starting)

    while queue:
        curr = queue.popleft()
        visited.add(frozenset(curr[0]))

        if all([labirynth[pos[0]][pos[1]] == 'B' for pos in curr[0]]):
            # print(curr[0])
            return curr[1]
        cleared = False
        for move in moves:
            pos = make_moves(labirynth, curr[0], move, 0)
            if cleared == False and len(pos[0]) < len(curr[0]):
                queue.clear()
                cleared = True
            if frozenset(pos) not in visited:
                # print(curr[1] + move)
                queue.append((pos, curr[1] + move))
    return -1        

if __name__ == "__main__":
    with open("zad_input.txt") as f:
        labirynth = f.readlines()
        path = generate_path(labirynth, (len(labirynth), len(labirynth[0]) - 1))
        print(path)
        with open("zad_output.txt", 'w') as o:
            o.write(path)