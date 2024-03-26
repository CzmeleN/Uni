from zad4 import opt_dist
import random

"""program korzysta z funkcji opt_dist z zad4 do
analizowania korzysci z ruchu wzgledem wiersza i kolumny
oraz z algorytmu opisanego w tresci zadania
z limitem 40 ruchow na jedno ustawienie poczatkowe"""

def get_col(img, col):
    return [row[col] for row in img]

def flip(img, row, col):
    img[row][col] = abs(img[row][col] - 1)

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

def col_opt_dist(img, col_desc, col):
    return opt_dist(get_col(img, col), col_desc[col])

def almost_walk_sat(sizes, row_desc, col_desc):
    limit = 40

    while(True):
        bad_col = []
        bad_row = []
        img = []
        for i in range(sizes[1]):
            img.append([])
            for j in range(sizes[0]):
                img[i].append(random.randint(0, 1))
        for i in range(sizes[0]):
            if opt_dist(get_col(img, i), col_desc[i]) > 0:
                bad_col.append(i)
        for i in range(sizes[1]):
            if opt_dist(img[i], row_desc[i]) > 0:
                bad_row.append(i)

        for it in range(limit):
            high_diff, high_id = float("-inf"), 0
            check_row, check_col = 0, 0
            if bad_col:
                col = random.choice(bad_col)
                # print(f"selected col: {col + 1}")
                col_diff = col_opt_dist(img, col_desc, col)
                for row in range(sizes[1]):
                    row_diff = opt_dist(img[row], row_desc[row])
                    diff = col_diff + row_diff
                    prev_diff = diff
                    # print(diff, end="  ")
                    flip(img, row, col)
                    diff -= col_opt_dist(img, col_desc, col) + opt_dist(img[row], row_desc[row])
                    flip(img, row, col)
                    if diff > high_diff:
                        high_diff = diff
                        high_id = row 
                        if diff == 2:
                            break
                    # print(diff)
                flip(img, high_id, col)
                check_row = high_id
                check_col = col
            else:
                row = random.choice(bad_row)
                # print(f"selected col: {col + 1}")
                row_diff = opt_dist(img[row], row_desc[row])
                for col in range(sizes[0]):
                    col_diff = col_opt_dist(img, col_desc, col)
                    diff = col_diff + row_diff
                    # print(diff, end="  ")
                    flip(img, row, col)
                    diff -= col_opt_dist(img, col_desc, col) + opt_dist(img[row], row_desc[row])
                    flip(img, row, col)
                    if diff > high_diff:
                        high_diff = diff
                        high_id = col
                        if diff == 2:
                            break
                    # print(diff)
                flip(img, row, high_id)
                check_row = row
                check_col = high_id

            res = opt_dist(img[check_row], row_desc[check_row])
            if check_row in bad_row: 
                if res == 0:
                    bad_row.remove(check_row)
            elif res != 0:
                bad_row.append(res)

            res = col_opt_dist(img, col_desc, check_col)
            if check_col in bad_col: 
                if res == 0:
                    bad_col.remove(check_col)
            elif res != 0:
                bad_col.append(res)

            if len(bad_row) == 0 and len(bad_col) == 0:
                return img

if __name__ == "__main__":
    with open("zad5_input.txt") as f:
        row_desc = []
        col_desc = []
        sizes = f.readline()
        sizes = [int(size) for size in sizes.split()]
        row_desc = [int(f.readline()) for i in range(sizes[0])]
        col_desc = [int(f.readline()) for i in range(sizes[1])]
        painted = almost_walk_sat(sizes, row_desc, col_desc)
        with open("zad5_output.txt", 'w') as o:
            for row in painted:
                row_str = ""
                for val in row:
                    if val == 1:
                        row_str += '#'
                    else:
                        row_str += '.'
                row_str += '\n'
                o.write(row_str)
