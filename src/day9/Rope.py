import numpy

from fileReader.PythonFileReader import read_input_of_day
from math import sqrt, floor


def create_rope_of_given_length(length):
    rope = []
    for x in range(length):
        rope.append({"x": 0, "y": 0})
    return rope


def adjust_tail_position(head_position, tail_position):
    same_row = head_position["x"] == tail_position["x"]
    same_col = head_position["y"] == tail_position["y"]
    if not (same_row and same_col):
        if same_row:
            distance = head_position["y"] - tail_position["y"]
            if 1 < abs(distance):
                tail_position["y"] += 1 * numpy.sign(distance)
        elif same_col:
            distance = head_position["x"] - tail_position["x"]
            if 1 < abs(distance):
                tail_position["x"] += 1 * numpy.sign(distance)
        else:
            distance_x = head_position["x"] - tail_position["x"]
            distance_y = head_position["y"] - tail_position["y"]
            distance = sqrt(distance_x ** 2 + distance_y ** 2)
            if 1 < floor(distance):
                tail_position["x"] += 1 * numpy.sign(distance_x)
                tail_position["y"] += 1 * numpy.sign(distance_y)


def move_rope_count_tail_movements(rope):
    tail_visited = {(0, 0)}
    direction_distance = map(lambda move: move.split(), movements)
    for (direction, distance) in direction_distance:
        if direction == "U":
            axis = "y"
            step = 1
        elif direction == "D":
            axis = "y"
            step = -1
        elif direction == "R":
            axis = "x"
            step = 1
        elif direction == "L":
            axis = "x"
            step = -1
        for i in range(int(distance)):
            rope[0][axis] += step
            for j in range(1, len(rope)):
                adjust_tail_position(rope[j-1], rope[j])
            tail_visited.add((rope[-1]["x"], rope[-1]["y"]))
    return len(tail_visited)


if __name__ == "__main__":
    input_file = read_input_of_day(9)
    movements = input_file.readlines()
    rope_length_2 = create_rope_of_given_length(2)
    part_1_result = move_rope_count_tail_movements(rope_length_2)
    print("Part 1: {}".format(part_1_result))
    rope_length_10 = create_rope_of_given_length(10)
    part_2_result = move_rope_count_tail_movements(rope_length_10)
    print("Part 2: {}".format(part_2_result))
