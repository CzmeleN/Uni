def back_track(row, blocks, desc):


def opt_dist(row, desc):
    blocks = []
    i = 0
    for d in desc:
        blocks.append((i, i + d - 1))
        i += d + 1

    return back_track(row, blocks, desc)

    

print(opt_dist([1, 0, 1, 1, 1, 0], [2, 2]))