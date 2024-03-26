from random import choice

def identical_splits(words, line, sample, iterations):
    identical_its = 0
    n = len(line)
    dp = [[] for i in range(n)]
    dp[0] = [""]

    for i in range(1, n):
        for j in range(i):
            word = line[j:i]
            if len(dp[j]) != 0 and word in words:
                dp[i].append(word)

    for i in range(iterations):
        new_line = choice(dp[len(line) - 1]) + '\n'
        i = n - len(new_line)

        while i > 0:
            chosen = choice(dp[i])
            new_line = chosen + ' ' + new_line
            i -= len(chosen)

        if len(new_line) == len(sample):
            identical_its += 1

    return identical_its

if __name__ == "__main__":
    with open("polish_words.txt", "r") as f:
        words = {word[:-1] for word in f}

    iterations = 500
    identical_its = 0
    max_its = 0

    with open("zad2_input.txt") as f:
        with open("zad2_sample.txt") as s:
            for line in f:
                identical_its += identical_splits(words, line, s.readline(), iterations)
                max_its += iterations

    print(f"{identical_its / max_its:.5%}")
                