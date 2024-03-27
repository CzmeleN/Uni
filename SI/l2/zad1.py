import random

"""part_dist dziala analogicznie do opt_dist z zad4 do
analizowania korzysci pojedynczego bloku z opisu i ustawienia
go zachlannie w rzedzie ktoremu najblizej do opisu
oraz z algorytmu opisanego w tresci zadania
z limitem ruchow na jedno ustawienie poczatkowe"""

def part_dist(nrs, d, start, end):
    res_start = start
    curr = 0
    
    for i in range(start, start + d):
        if(nrs[i] == 0):
            curr += 1

    for i in range(start + d, end):
        curr += nrs[i]

    max = curr

    for i in range(start, end - d):
        if nrs[i] == 0:
            curr -= 1
        else:
            curr += 1

        if nrs[i + d] == 0:
            curr += 1
        else:
            curr -= 1

        if curr < max:
            res_start = i + 1
            max = curr
            if curr == 0:
                break

    return res_start

def opt_dist(row, desc):
    start = 0
    end = len(row)
    left = sum(desc) + len(desc)
    res = 0
    blocks = [0 for i in range(end)]

    for d in desc:
        left -= d + 1
        start = part_dist(row, d, start, end - left)
        for i in range(start, start + d):
            blocks[i] = 1
        start += d + 1
    
    for i in range(end):
        if row[i] != blocks[i]:
            res += 1

    return res

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
    limit = 750
    while(True):
        bad_col = []
        bad_row = []
        img = []
        for i in range(sizes[0]):
            img.append([])
            for j in range(sizes[1]):
                img[i].append(random.randint(0, 1))
        for i in range(sizes[1]):
            if opt_dist(get_col(img, i), col_desc[i]) > 0:
                bad_col.append(i)
        for i in range(sizes[0]):
            if opt_dist(img[i], row_desc[i]) > 0:
                bad_row.append(i)

        for it in range(limit):
            high_diff = float("-inf")
            high_id = []
            filtered_id = []
            check_row, check_col = 0, 0
            choice = random.randint(0 if bad_col else 1, 1 if bad_row else 0)
            
            if choice == 0:
                col = random.choice(bad_col)
                col_diff = col_opt_dist(img, col_desc, col)
                for row in range(sizes[0]):
                    row_diff = opt_dist(img[row], row_desc[row])
                    diff = col_diff + row_diff
                    flip(img, row, col)
                    diff -= col_opt_dist(img, col_desc, col) + opt_dist(img[row], row_desc[row])
                    flip(img, row, col)
                    if diff >= high_diff:
                        high_diff = diff
                        high_id.append((row, diff))
                for id in high_id:
                    if id[1] == high_diff:
                        filtered_id.append(id[0])
                check_row = random.choice(filtered_id)
                check_col = col
                flip(img, check_row, col)
            else:
                row = random.choice(bad_row)
                row_diff = opt_dist(img[row], row_desc[row])
                for col in range(sizes[1]):
                    col_diff = col_opt_dist(img, col_desc, col)
                    diff = col_diff + row_diff
                    flip(img, row, col)
                    diff -= col_opt_dist(img, col_desc, col) + opt_dist(img[row], row_desc[row])
                    flip(img, row, col)
                    if diff >= high_diff:
                        high_diff = diff
                        high_id.append((col, diff))
                for id in high_id:
                    if id[1] == high_diff:
                        filtered_id.append(id[0])
                check_row = row
                check_col = random.choice(filtered_id)
                flip(img, row, check_col)

            res = opt_dist(img[check_row], row_desc[check_row])
            if check_row in bad_row: 
                if res == 0:
                    bad_row.remove(check_row)
            elif res != 0:
                bad_row.append(check_row)

            res = col_opt_dist(img, col_desc, check_col)
            if check_col in bad_col: 
                if res == 0:
                    bad_col.remove(check_col)
            elif res != 0:
                bad_col.append(check_col)

            if len(bad_row) == 0 and len(bad_col) == 0:
                return img
            # print_img(img, row_desc, col_desc)

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
