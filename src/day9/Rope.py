import numpy

from fileReader.PythonFileReader import read_input_of_day
from math import sqrt, floor

rope_position = {"x": 0, "y": 0}
tail_position = rope_position.copy()
tail_visited = {(0, 0)}


def adjust_tail_position():
    same_row = rope_position["x"] == tail_position["x"]
    same_col = rope_position["y"] == tail_position["y"]
    if not (same_row and same_col):
        if same_row:
            distance = rope_position["y"] - tail_position["y"]
            if 1 < abs(distance):
                tail_position["y"] += 1 * numpy.sign(distance)
        elif same_col:
            distance = rope_position["x"] - tail_position["x"]
            if 1 < abs(distance):
                tail_position["x"] += 1 * numpy.sign(distance)
        else:
            distance_x = rope_position["x"] - tail_position["x"]
            distance_y = rope_position["y"] - tail_position["y"]
            distance = sqrt(distance_x ** 2 + distance_y ** 2)
            if 1 < floor(distance):
                tail_position["x"] += 1 * numpy.sign(distance_x)
                tail_position["y"] += 1 * numpy.sign(distance_y)


def move_rope_count_tail_movements():
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
            rope_position[axis] += step
            adjust_tail_position()
            tail_visited.add((tail_position["x"], tail_position["y"]))
            # print("Head: {}".format(rope_position))
            # print("Tail: {}".format(tail_position))
    return len(tail_visited)


if __name__ == "__main__":
    input_file = read_input_of_day(9)
    movements = input_file.readlines()
    direction_distance = map(lambda move: move.split(), movements)
    unique_tail_positions = move_rope_count_tail_movements()
    print("Part 1: {}".format(unique_tail_positions))
