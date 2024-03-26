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

print(opt_dist([1, 1, 1, 0, 0, 0, 0, 0], [1, 1]))