import os


def read_input_of_day(day: int):
    this_path = os.path.dirname(__file__)
    src_path = os.path.dirname(this_path)
    day_path = os.path.join(src_path, "day{}".format(day))
    input_of_day = os.path.join(day_path, "input.txt")
    return open(input_of_day)
