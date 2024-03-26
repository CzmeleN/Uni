import random

"""program losuje karty dla figuranta oraz blotkarza
ustalona liczbe razy oraz sprawdza punktacje
poprzez tworzenie setow w celu wykrycia par etc
a nastepnie porownuje pojedyczne rozdania
i to powtorzone dana liczbe razy"""

face_cards = ["Ace", "King", "Queen", "Jack"]
number_cards = range(2, 11)
colors = ["Hearts", "Diamonds", "Spades", "Clubs"]

figurant_cards = [(card, color) for card in face_cards
                  for color in colors]

blotkarz_cards = [(card, color) for card in number_cards
                  for color in colors]
# blotkarz_cards.append((5, "Hearts"))

hands = ["Straight Flush",
         "Four of a kind",
         "Full House",
         "Flush",
         "Straight",
         "Three of a kind",
         "Two pair",
         "Pair",
         "High card"]

def straight(values):
    if values[0] in face_cards:
        return False
    else:
        values.sort()
        for i in range(4):
            if values[i + 1] - values[i] != 1:
                return False
    return True
    


def evaluate_hand(hand):
    colors_set = set([card[1] for card in hand])
    values = [card[0] for card in hand]
    values_set = set(values)
    if len(colors_set) == 1 and len(values_set) == 5 and straight(values):
        return "Straight Flush"
    if len(values_set) == 2:
        if any([values.count(value) == 4 for value in values_set]):
            return "Four of a kind"
        else:
            return "Full House"
    if len(colors_set) == 1:
        return "Flush"
    if len(values_set) == 5 and straight(values):
        return "Straight"
    if len(values_set) == 3:
        if any([values.count(value) == 3 for value in values_set]):
            return "Three of a kind"
        else:
            return "Two pair"
    if len(values_set) == 4:
        if any([values.count(value) == 2 for value in values_set]):
            return "Pair"
    return "High card"

def draw_once():
    figurant_hand = random.sample(figurant_cards, k=5)
    blotkarz_hand = random.sample(blotkarz_cards, k=5)
    if hands.index(evaluate_hand(figurant_hand)) <= hands.index(evaluate_hand(blotkarz_hand)):
        return "Figurant"
    else:
        return "Blotkarz"

def draw_many():
    iterations = 10000
    figurant_wins = 0
    blotkarz_wins = 0
    for i in range(iterations):
        if draw_once() == "Figurant":
            figurant_wins += 1
        else:
            blotkarz_wins += 1
    print(f"Figurant winrate: {figurant_wins / iterations:.2%}")
    print(f"Blotkarz winrate: {blotkarz_wins / iterations:.2%}")

if __name__ == "__main__":
    draw_many()