from itertools import combinations
import numpy as np

# def get_col(img, col):
#     return [row[col] for row in img]

# def flip(img, row, col):
#     img[row][col] = abs(img[row][col] - 1)

def print_img(img, row_desc, col_desc):
    val_str = "  "
    for val in col_desc:
        val_str += str(val) + ' '
    print(val_str)
    for row in range(len(img)):
        row_str = str(row_desc[row])
        for cell in img[row]:
            row_str += " ." if cell == 0 else " #"
        print(row_str)

def aux_create_possibs(no_empty, groups, ones):
    res_opts = []
    for p in combinations(range(groups + no_empty), groups):
        selected = [-1] * (groups + no_empty)
        ones_idx = 0
        for val in p:
            selected[val] = ones_idx
            ones_idx += 1
        res_opt = [ones[val] + [-1] if val > -1 else [-1] for val in selected]
        res_opt = [item for sublist in res_opt for item in sublist][:-1]
        res_opts.append(res_opt)
    return res_opts

def create_possibs(values, others_count):
    possibs = []

    for v in values:
        groups = len(v)
        no_empty = others_count - sum(v) - groups + 1
        ones = [[1] * x for x in v]
        res = aux_create_possibs(no_empty, groups, ones)
        possibs.append(res)

    return possibs

def resolution(sizes, row_desc, col_desc):
    img = [[0 for _ in range(sizes[1])] for r in range(sizes[0])]
    rows_possibs = create_possibs(row_desc, sizes[0])
    cols_possibs = create_possibs(col_desc, sizes[1])
    rows_done = [0] * sizes[1]
    cols_done = [0] * sizes[0]

    ds = 0
    while True:
        ds += 1
        lowest_rows = [(i, n, id) for i, n in enumerate([len(i) for i in rows_possibs]) if rows_done[i] == 0]
        lowest_cols = [(i, n, id) for i, n in enumerate([len(i) for i in cols_possibs]) if cols_done[i] == 0]
        lowest = sorted(lowest_rows + lowest_cols, key = lambda element: element[1])

        for id1, _, row_id in lowest:
            if not (rows_done[id1] if row_id else cols_done[id1]):
                if row_id:
                    values = rows_possibs[id1]
                else:
                    values = cols_possibs[id1]
                same_id = [(n, np.unique(i)[0]) for n, i in enumerate(np.array(values).T) if len(np.unique(i)) == 1]
                for id2, v in same_id:
                    if row_id:
                        ri, ci = id1, id2
                    else:
                        ri, ci = id2, id1
                    if img[ri][ci] == 0:
                        img[ri][ci] = v
                        if row_id:
                            cols_possibs[ci] = [p for p in cols_possibs[ci] if p[ri] == v]
                        else:
                            rows_possibs[ri] = [p for p in rows_possibs[ri] if p[ci] == v]
                if row_id:
                    if 0 not in img[id1]:
                        rows_done[id1] = 1
                else:
                    if 0 not in [row[id1] for row in img]:
                        cols_done[id1] = 1
        if 0 not in rows_done and 0 not in cols_done:
            return img
        print_img(img, row_desc, col_desc)
        if ds == 5:
            break

def backtrack(sizes, row_desc, col_desc):
    return

if __name__ == "__main__":
    with open("zad_input.txt") as f:
        r_desc = []
        c_desc = []
        size = f.readline()
        size = [int(s) for s in size.split()]
        r_desc = [[int(s) for s in f.readline().split()] for i in range(size[0])]
        c_desc = [[int(s) for s in f.readline().split()] for i in range(size[1])]
        painted = resolution(size, r_desc, c_desc)
        with open("zad_output.txt", 'w') as o:
            for row in painted:
                row_str = ""
                for val in row:
                    if val == 1:
                        row_str += '#'
                    else:
                        row_str += '.'
                row_str += '\n'
                o.write(row_str)
