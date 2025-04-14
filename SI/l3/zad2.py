from itertools import combinations
from copy import deepcopy
    
def make_line_poss(empty_no, blocks_no, ones):
    line_poss = []
    for p in combinations(range(empty_no + blocks_no), blocks_no):
        selected = [-1] * (empty_no + blocks_no)
        idx = 0
        for val in p:
            selected[val] = idx
            idx += 1
        
        res = [ones[val] + [-1] if val > -1 else [-1] for val in selected]
        res = [item for sublist in res for item in sublist][:-1]
        line_poss.append(res)
    return line_poss

def make_poss(lines, n):
    """
    tworzy mozliwosci dla wszystkich wierszy/kolumn
    """
    lines_poss = []
    for line in lines:
        blocks_no = len(line)
        empty_no = n - sum(line) - blocks_no + 1
        ones = [[1] * pixel for pixel in line]
        line_poss = make_line_poss(empty_no, blocks_no, ones)
        lines_poss.append(line_poss)
    return lines_poss

def select_not_solved(poss, done, is_row):
    s = [len(i) for i in poss]
    return [(liczba_mozliwosci, i, is_row) for i, liczba_mozliwosci in enumerate(s) if done[i] == 0]

def get_same_pixels(poss, line):
    """
    zwraca powtarzajace sie (pewne okienka)
    """
    poss_no = len(poss)
    if poss_no == 0:
        return []
    
    line_len = len(poss[0])
    sums = [0] * line_len
    for p in poss:
        for i in range(line_len):
            sums[i] += 1 if p[i] == 1 else 0
    
    same_pixels = []
    for i in range(line_len):
        if sums[i] == 0 and line[i] != -1:
            same_pixels.append([i, -1])
        elif sums[i] == poss_no and line[i] != 1:
            same_pixels.append([i, 1])
    
    return same_pixels

def check_done(i, is_row, cols_done, rows_done):
    if is_row:
        return rows_done[i]
    return cols_done[i]

def check_solved(rows_done, cols_done):
    return True if 0 not in rows_done and 0 not in cols_done else False

def get_col(img, j):
    return [img[i][j] for i in range(len(img))]

def update_done(is_row, i, img, rows_done, cols_done):
    line = img[i] if is_row else get_col(img, i)
    if 0 not in line:
        if is_row:
            rows_done[i] = 1
        else:
            cols_done[i] = 1

def update_poss(poss, i, val):
    return [p for p in poss if p[i] == val]

def removed_poss(poss, i, val):
    return [p for p in poss if p[i] != val]

def valid(img, rows, cols):
    """
    sprawdza czy rozwiazany nono jest dobry
    """
    def get_segments(line):
        segments = []
        count = 0
        for value in line:
            if value == 1:
                count += 1
            elif count > 0:
                segments.append(count)
                count = 0
        if count > 0:
            segments.append(count)
        return segments

    for i, row in enumerate(img):
        if get_segments(row) != rows[i]:
            return False

    num_cols = len(img[0])
    for j in range(num_cols):
        col = [img[i][j] for i in range(len(img))]
        if get_segments(col) != cols[j]:
            return False

    return True

def print_img(img):
    for i, _ in enumerate(img):
        for j, _ in enumerate(img[0]):
            print(img[i][j], end=' ')
            if img[i][j] != -1:
                print(' ', end='')
        print()
    print()
    

def get_coll(img, j):
    return [img[i][j] for i in range(len(img))]

def give_back_removed_poss(n, m, removed_poss_rows, removed_poss_cols, rows_poss, cols_poss):
    for g in range(n):
        rows_poss[g] += removed_poss_rows[g]
        removed_poss_rows[g] = []
    for g in range(m):
        cols_poss[g] += removed_poss_cols[g]
        removed_poss_cols[g] = []
    return

def find_ans(img, rows_poss, cols_poss, rows_done, cols_done, rows, cols):
    # print_img(img)
    not_solved_rows = []
    not_solved_cols = []
    lines_todo = []
    
    removed_poss_rows = [[] for _ in range(len(img))]
    removed_poss_cols = [[] for _ in range(len(img[0]))]
    
    #sprawdzenie wstepne
    for j, _ in enumerate(rows_poss):
        if len(rows_poss[j]) == 0 and not rows_done[j]:
            return []
        
    for j, _ in enumerate(cols_done):
        if len(cols_poss[j]) == 0 and not cols_done[j]:
            return []
    
    # rezolucja
    solved, change = False, True
    while not solved and change: 
        change = False
        not_solved_rows = select_not_solved(rows_poss, rows_done, True)
        not_solved_cols = select_not_solved(cols_poss, cols_done, False)
        lines_todo = sorted(not_solved_cols + not_solved_rows) # sortuje je po najmniejszej ilości możliwości
        
        # ustawia pixele o których wiemy jak będą wyglądały
        for amount, i, is_row in lines_todo:
            if amount == 0:
                give_back_removed_poss(len(img), len(img[0]), removed_poss_rows, removed_poss_cols, rows_poss, cols_poss)
                return []
            
            if not check_done(i, is_row, cols_done, rows_done):
                poss = rows_poss[i] if is_row else cols_poss[i]
                line = img[i] if is_row else get_coll(img, i)
                same_pixels = get_same_pixels(poss, line)
                
                for j, val in same_pixels:
                    r_idx, c_idx = (i, j) if is_row else (j, i)
                    if img[r_idx][c_idx] == 0:
                        if img[r_idx][c_idx] != val:
                            img[r_idx][c_idx] = val
                            change = True

                            if is_row:
                                removed_poss_cols[c_idx] += removed_poss(cols_poss[c_idx], r_idx, val)
                                cols_poss[c_idx] = update_poss(cols_poss[c_idx], r_idx, val)
                            else:
                                removed_poss_rows[r_idx] += removed_poss(rows_poss[r_idx], c_idx, val)
                                rows_poss[r_idx] = update_poss(rows_poss[r_idx], c_idx, val)
                                
                update_done(is_row, i, img, rows_done, cols_done)
        solved = check_solved(rows_done, cols_done)

    # sprawdzenie i ew zwrot po wnioskowaniu
    for j, _ in enumerate(rows_poss):
        if len(rows_poss[j]) == 0 and not rows_done[j]:
            give_back_removed_poss(len(img), len(img[0]), removed_poss_rows, removed_poss_cols, rows_poss, cols_poss)
            return []
        
    for j, _ in enumerate(cols_done):
        if len(cols_poss[j]) == 0 and not cols_done[j]:
            give_back_removed_poss(len(img), len(img[0]), removed_poss_rows, removed_poss_cols, rows_poss, cols_poss)
            return []
        
    if solved:
        if valid(img, rows, cols):
            give_back_removed_poss(len(img), len(img[0]), removed_poss_rows, removed_poss_cols, rows_poss, cols_poss)
            return img
        give_back_removed_poss(len(img), len(img[0]), removed_poss_rows, removed_poss_cols, rows_poss, cols_poss)
        return []
    
    # backtrack na kopii po pozycjach z najmniejsza iloscia mozliwosci
    not_solved_rows = select_not_solved(rows_poss, rows_done, True)
    not_solved_cols = select_not_solved(cols_poss, cols_done, False)
    lines_todo = sorted(not_solved_cols + not_solved_rows) # sortuje je po najmniejszej ilości możliwości
    
    _, i, is_row = lines_todo[0]
    to_check = deepcopy(rows_poss[i] if is_row else cols_poss[i])
    for u in to_check:
        _img = deepcopy(img)
        removed_poss_rows2 = [[] for _ in range(len(img))]
        removed_poss_cols2 = [[] for _ in range(len(img[0]))]
        _rows_done = deepcopy(rows_done)
        _cols_done = deepcopy(cols_done)
        
        for j, _ in enumerate(u):
            val = u[j]
            r_idx, c_idx = (i, j) if is_row else (j, i)
            if _img[r_idx][c_idx] == 0:
                _img[r_idx][c_idx] = val

                if is_row:
                    removed_poss_cols2[c_idx] += removed_poss(cols_poss[c_idx], r_idx, val)
                    cols_poss[c_idx] = update_poss(cols_poss[c_idx], r_idx, val)
                else:
                    removed_poss_rows2[r_idx] += removed_poss(rows_poss[r_idx], c_idx, val)
                    rows_poss[r_idx] = update_poss(rows_poss[r_idx], c_idx, val)
                
        update_done(is_row, i, _img, _rows_done, _cols_done)
        
        if check_solved(_rows_done, _cols_done):
            if valid(_img, rows, cols):
                return _img
            give_back_removed_poss(len(img), len(img[0]), removed_poss_rows2, removed_poss_cols2, rows_poss, cols_poss)
            continue
        
        # wszystko już jest ustawione
        ans = find_ans(_img, rows_poss, cols_poss, _rows_done, _cols_done, rows, cols)
        if ans != []:
            return ans
        give_back_removed_poss(len(img), len(img[0]), removed_poss_rows2, removed_poss_cols2, rows_poss, cols_poss)
    give_back_removed_poss(len(img), len(img[0]), removed_poss_rows, removed_poss_cols, rows_poss, cols_poss)
    return []
        
def solve(rows_no, cols_no, rows, cols):
    img = [[0 for _ in range(cols_no)] for _ in range(rows_no)]
    
    rows_done = [0] * rows_no
    cols_done = [0] * cols_no
    
    rows_poss = make_poss(rows, cols_no)
    cols_poss = make_poss(cols, rows_no)
    
    return find_ans(img, rows_poss, cols_poss, rows_done, cols_done, rows, cols)
 
if __name__ == "__main__":
    with open('zad_input.txt') as input:
        n, m = map(int, input.readline().split())
        rows = [list(map(int, input.readline().split())) for _ in range(n)]
        cols = [list(map(int, input.readline().split())) for _ in range(m)]
    img = solve(n, m, rows, cols)
    
    with open('zad_output.txt', 'w') as output:
        for i in range(n):
            for j in range(m):
                output.write('#' if img[i][j] == 1 else '.')
            output.write('\n')
