"""prosty moving window, najpierw zlicza jedynki wewnatrz
i na zewnatrz okna, a potem odejmuje/dodaje w ramach przesuwania"""

def opt_dist(nrs, d):
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

if __name__ == "__main__":
    with open("zad4_input.txt") as f:
        with open("zad4_output.txt", 'w') as o:
            for line in f:
                parts = line.split()
                nrs = [int(nr) for nr in parts[0]]
                d = int(parts[1])
                o.write(str(opt_dist(nrs, d)) + '\n')