from collections import deque

def make_moves(labirynth, poses, move):
    for i in range(len(poses)):
        if move == 'U':
            new_pos = (poses[i][0] - 1, poses[i][1])
        elif move == 'D':
            new_pos = (poses[i][0] + 1, poses[i][1])
        elif move == 'L':
            new_pos = (poses[i][0], poses[i][1]  - 1)
        elif move == 'R':
            new_pos = (poses[i][0], poses[i][1] + 1)
        if labirynth[new_pos[0]][new_pos[1]] != '#':
            poses[i] = new_pos
    return poses

def lower_uncertanity(labirynth, sizes):
    path = "ULURRULLLURRRRULLLLLULULULULULULU"
    poses = []
    res = []
    for i in range(sizes[0]):
        for j in range(sizes[1]):
            if labirynth[i][j] == 'S' or labirynth[i][j] == 'B':
                poses.append((i, j))
    for move in path:
        make_moves(labirynth, poses, move)
    for pose in poses:
        if pose not in res:
            res.append(pose)
    return (res, path)

def generate_path(labirynth, sizes):
    starting = lower_uncertanity(labirynth, sizes)
    moves = ['U', 'D', 'R', 'L']
    visited = set()
    visited.add(tuple(starting[0]))
    queue = deque()
    queue.append(starting)

    while queue:
        curr = queue.popleft()
        visited.add(tuple(curr[0]))

        if all([labirynth[pos[0]][pos[1]] == 'G' or labirynth[pos[0]][pos[1]] == 'B' for pos in curr[0]]):
            return curr[1]

        for move in moves:
            new = (make_moves(labirynth, curr[0], move), curr[1] + move)
            if tuple(new[0]) not in visited:
                queue.append(new)
    return -1        

if __name__ == "__main__":
    with open("zad_input.txt") as f:
        labirynth = f.readlines()
        path = generate_path(labirynth, (len(labirynth), len(labirynth[0])))
        print(path)
        with open("zad_output.txt", 'w') as o:
            o.write(path)