from fileReader.PythonFileReader import read_input_of_day

value_of_play = {
    "X": 1,
    "Y": 2,
    "Z": 3
}

value_of_outcome = {
    "X": 0,
    "Y": 3,
    "Z": 6
}


def value_of_round_part_1(game_round):
    total_value = 0
    opponent_play, your_play = game_round.split()
    total_value += value_of_play.get(your_play)
    total_value += value_of_match(opponent_play, your_play)
    return total_value


def value_of_round_part_2(game_round):
    total_value = 0
    opponent_play, desired_outcome = game_round.split()
    total_value += value_of_outcome.get(desired_outcome)
    your_play = play_for_outcome(opponent_play, desired_outcome)
    total_value += value_of_play.get(your_play)
    return total_value


def value_of_match(opponent_play, your_play):
    if opponent_play == "A":
        if your_play == "X":
            return 3
        elif your_play == "Y":
            return 6
        elif your_play == "Z":
            return 0
    if opponent_play == "B":
        if your_play == "X":
            return 0
        elif your_play == "Y":
            return 3
        elif your_play == "Z":
            return 6
    if opponent_play == "C":
        if your_play == "X":
            return 6
        elif your_play == "Y":
            return 0
        elif your_play == "Z":
            return 3


def play_for_outcome(opponent_play, desired_outcome):
    if opponent_play == "A":
        if desired_outcome == "X":
            return "Z"
        elif desired_outcome == "Y":
            return "X"
        elif desired_outcome == "Z":
            return "Y"
    if opponent_play == "B":
        if desired_outcome == "X":
            return "X"
        elif desired_outcome == "Y":
            return "Y"
        elif desired_outcome == "Z":
            return "Z"
    if opponent_play == "C":
        if desired_outcome == "X":
            return "Y"
        elif desired_outcome == "Y":
            return "Z"
        elif desired_outcome == "Z":
            return "X"


if __name__ == "__main__":
    input_file = read_input_of_day(2)
    rounds = input_file.readlines()
    value_of_rounds = map(value_of_round_part_1, rounds)
    sum_of_values = sum(value_of_rounds)
    print("Part 1: {}".format(sum_of_values))
    value_of_rounds = map(value_of_round_part_2, rounds)
    sum_of_values = sum(value_of_rounds)
    print("Part 2: {}".format(sum_of_values))