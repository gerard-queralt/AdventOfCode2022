from fileReader.PythonFileReader import read_input_of_day
from enum import Enum


class Play(Enum):
    Rock = 1
    Paper = 2
    Scissors = 3


class Outcome(Enum):
    Loss = 0
    Draw = 3
    Win = 6


# first is opponent play, second is your play
result_of_match = {
    (Play.Rock, Play.Rock): Outcome.Draw,
    (Play.Rock, Play.Paper): Outcome.Win,
    (Play.Rock, Play.Scissors): Outcome.Loss,

    (Play.Paper, Play.Rock): Outcome.Loss,
    (Play.Paper, Play.Paper): Outcome.Draw,
    (Play.Paper, Play.Scissors): Outcome.Win,

    (Play.Scissors, Play.Rock): Outcome.Win,
    (Play.Scissors, Play.Paper): Outcome.Loss,
    (Play.Scissors, Play.Scissors): Outcome.Draw
}

translate_play = {
    "A": Play.Rock,
    "X": Play.Rock,
    "B": Play.Paper,
    "Y": Play.Paper,
    "C": Play.Scissors,
    "Z": Play.Scissors
}

translate_outcome = {
    "X": Outcome.Loss,
    "Y": Outcome.Draw,
    "Z": Outcome.Win
}


def value_of_round_part_1(game_round):
    opponent_play, your_play = map(translate_play.get, game_round.split())
    outcome = result_of_match.get((opponent_play, your_play))
    return your_play.value + outcome.value


def value_of_round_part_2(game_round):
    total_value = 0
    opponent_play, desired_outcome = game_round.split()
    opponent_play = translate_play.get(opponent_play)
    desired_outcome = translate_outcome.get(desired_outcome)
    for (play1, play2), outcome in result_of_match.items():
        if play1 == opponent_play and outcome == desired_outcome:
            your_play = play2
            return your_play.value + desired_outcome.value


if __name__ == "__main__":
    input_file = read_input_of_day(2)
    rounds = input_file.readlines()
    value_of_rounds = map(value_of_round_part_1, rounds)
    sum_of_values = sum(value_of_rounds)
    print("Part 1: {}".format(sum_of_values))
    value_of_rounds = map(value_of_round_part_2, rounds)
    sum_of_values = sum(value_of_rounds)
    print("Part 2: {}".format(sum_of_values))
