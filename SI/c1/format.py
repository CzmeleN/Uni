if __name__ == "__main__":
    with open("zad2_sample.txt") as f:
        with open("zad2_pt_input.txt", 'w') as o:
            for line in f:
                o.write(line.lower())