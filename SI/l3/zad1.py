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

def create_possibs(values, others_count):
    possibs = []

    for v in values:
        groups = len(v)
        no_empty = others_count - sum(v) - groups + 1
        ones = [[1] * x for x in v]
        res = create_possibs(no_empty, groups, ones)
        possibs.append(res)

    return possibs

def resolution(img, row_desc, col_desc):
    rows_possibs = create_possibs(row_desc, len(img[0]))
    cols_possibs = create_possibs(col_desc, len(img))

    while true:
        lowest_rows = [(i, n, id) for i, n in enumerate([len(i) for i in rows_possibs]) if rows_done[i] == 0]
        lowest_cols = [(i, n, id) for i, n in enumerate([len(i) for i in cols_possibs]) if cols_done[i] == 0]
        lowest = sorted(lowest_rows + lowest_cols, key = lambda element: element[1])

        for id1, _, row_id in lowest:
            if not check_done(row_id, id1):
                if row_id:
                    values = rows_possibs[id1]
                else:
                    values = cols_possibs[id1]
                same_id = [(n, np.unique(i)[0]) for n, i in enumerate(np.array(values).T) if len(np.unique(i)) == 1]
                for id2, val in same_id:
                    if row_id:
                        ri, ci = id1, id2
                    else:
                        ri, ci = id2, id1
                    if img[ri][ci] == 0:
                        img[ri][ci] = val
                        if row_id:
                            cols_possibs[ci] = [p for p in cols_possibs if p[ri] == val]
                        else:
                            rows_possibs[ri] = [p for p in rows_possibs if p[ci] == val]
        if solved:
            return img

def backtrack(sizes, row_desc, col_desc):
    return

if __name__ == "__main__":
    with open("zad_input.txt") as f:
        row_desc = []
        col_desc = []
        sizes = f.readline()
        sizes = [int(size) for size in sizes.split()]
        row_desc = [[int(size) for size in f.readline().split()] for i in range(sizes[0])]
        col_desc = [[int(size) for size in f.readline().split()] for i in range(sizes[1])]
        painted = almost_walk_sat(sizes, row_desc, col_desc)
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
