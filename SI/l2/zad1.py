import random

"""program korzysta z funkcji opt_dist z zad4 do
analizowania korzysci z ruchu wzgledem wiersza i kolumny
oraz z algorytmu opisanego w tresci zadania
z limitem 40 ruchow na jedno ustawienie poczatkowe"""

# zamiana na listę bloków, na początku startujemy z blokami od lewej z przerwami jeden i dosuwamy je do końca od prawego
# na podobnej zasadzie, odejmujemy/dodajemy wchodzace w pojedynczy blok, aby bylo szybciej mozemy policzyc o ile mozemy
# do konca do prawej dosunac i zrobic petle na range tej wartosci zamiast sprawdzac czy zachaczamy o nastepny blok
# wowczas powinna dzialac w miare spoko na tych testach, i musimy tez zwiekszyc liczbe dopuszczalnych ruchow
# (wykonac testy ile 5% max w znalezionych przypadkach wychodzi)
def opt_dist(row, desc):
    # Inicjalizujemy licznik okienek do zmiany
    okienka_do_zmiany = 0
    
    # Tworzymy listę grup komórek w wierszu
    grupy_wiersza = []
    current_group = 0
    for cell in row:
        if cell == 1:
            current_group += 1
        else:
            if current_group > 0:
                grupy_wiersza.append(current_group)
                current_group = 0
    if current_group > 0:
        grupy_wiersza.append(current_group)

    # Sprawdzamy, czy ilość grup wiersza jest zgodna z opisem
        # Sprawdzamy, czy długości poszczególnych grup są zgodne z opisem
    diff = len(desc) - len(grupy_wiersza)
    if diff > 0:
        for i in range(len(grupy_wiersza)):
            if grupy_wiersza[i] != desc[i]:
                okienka_do_zmiany += abs(desc[i] - grupy_wiersza[i])
        okienka_do_zmiany += sum(desc[:diff])
    elif diff < 0:
        for i in range(len(desc)):
            if grupy_wiersza[i] != desc[i]:
                okienka_do_zmiany += abs(desc[i] - grupy_wiersza[i])
        okienka_do_zmiany += sum(grupy_wiersza[:abs(diff)])
    else:
        for i in range(len(grupy_wiersza)):
            if grupy_wiersza[i] != desc[i]:
                okienka_do_zmiany += abs(desc[i] - grupy_wiersza[i])

    return okienka_do_zmiany

def old_dist(nrs, d):
    curr = 0

    for i in range(d):
        if(nrs[i] == 0):
            curr += 1

    for i in range(d, len(nrs)):
        curr += nrs[i]

    max = curr

    for i in range(len(nrs) - d):
        if nrs[i] == 0:
            curr -= 1
        else:
            curr += 1

        if nrs[i + d] == 0:
            curr += 1
        else:
            curr -= 1

        if curr < max:
            max = curr
    
    return max

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
    limit = 1500

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
            bad_start = 0 if bad_col else 1
            bad_end = 1 if bad_row else 0
            choice = random.randint(bad_start, bad_end)
            if choice == 0:
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
        print_img(img, row_desc, col_desc)

if __name__ == "__main__":
    with open("zad1_input.txt") as f:
        row_desc = []
        col_desc = []
        sizes = f.readline()
        sizes = [int(size) for size in sizes.split()]
        row_desc = [[int(size) for size in f.readline().split()] for i in range(sizes[0])]
        col_desc = [[int(size) for size in f.readline().split()] for i in range(sizes[1])]
        painted = almost_walk_sat(sizes, row_desc, col_desc)
        with open("zad1_output.txt", 'w') as o:
            for row in painted:
                row_str = ""
                for val in row:
                    if val == 1:
                        row_str += '#'
                    else:
                        row_str += '.'
                row_str += '\n'
                o.write(row_str)
