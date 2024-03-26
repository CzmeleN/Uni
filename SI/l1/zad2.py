"""program korzysta z programowania dynamicznego aby znalezc
kombinacje nadluzszych mozliwych slow oraz z wyszukiwania
binarnego w celu znalezenia slowa w slowniku"""

def in_words(words, word):
    start = 0
    end = len(words) - 1

    while start <= end:
        mid = (start + end) // 2
        if words[mid] == word:
            return True
        elif words[mid] < word:
            start = mid + 1
        else:
            end = mid - 1
    return False

def split_line(words, line):
    dp = [{"sum": -1, "word": ""}] * len(line)
    dp[0] = {"sum": 0, "word": ""}

    for i in range(1, len(line)):
        for j in range(i):
            if dp[j]["sum"] != -1:
                new_sum = (i - j) ** 2 + dp[j]["sum"]
                if new_sum > dp[i]["sum"] and in_words(words, line[j:i]):
                    dp[i] = {"sum": new_sum, "word": line[j:i]}

    new_line = dp[len(line) - 1]["word"] + '\n'
    i = len(dp) - len(new_line)

    while i > 0:
        new_line = dp[i]["word"] + ' ' + new_line
        i -= len(dp[i]["word"])

    return new_line

if __name__ == "__main__":
    with open("polish_words.txt", "r") as f:
        words = f.readlines()

    words.sort()
    words = [word[:-1] for word in words]

    with open("zad2_input.txt") as f:
        with open("zad2_output.txt", "w") as o:
            for line in f:
                o.write(split_line(words, line))
