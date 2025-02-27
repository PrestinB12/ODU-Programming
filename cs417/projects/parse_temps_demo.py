# Found from Thomas Kennedy: https://github.com/cstkennedy/cs417-examples/blob/master/SemesterProject-CPU-Temps/python3/parse_temps.py

#! /usr/bin/env python3

import sys

from parse_temps import parse_raw_temps


def main():
    """
    This main function serves as the driver for the demo. Such functions
    are not required in Python. However, we want to prevent unnecessary module
    level (i.e., global) variables.
    """

    input_temps = sys.argv[1]

    with open(input_temps, "r") as temps_file:
        # ----------------------------------------------------------------------
        # Output raw structure
        # ----------------------------------------------------------------------
        for temps_as_floats in parse_raw_temps(temps_file):
            print(temps_as_floats)

    with open(input_temps, "r") as temps_file:
        # ----------------------------------------------------------------------
        # Split data
        # ----------------------------------------------------------------------
        for temps_as_floats in parse_raw_temps(temps_file):
            time, core_data = temps_as_floats
            print(f"{time = } | {core_data = }")

    with open(input_temps, "r") as temps_file:
        # ----------------------------------------------------------------------
        # Split Data
        # ----------------------------------------------------------------------
        times = []
        core_0_data = []
        core_1_data = []
        core_2_data = []
        core_3_data = []
        for time, core_data in parse_raw_temps(temps_file):
            times.append(time)
            core_0_data.append(core_data[0])
            core_1_data.append(core_data[1])
            core_2_data.append(core_data[2])
            core_3_data.append(core_data[3])

        print(f"{times[:4] = }")
        print(f"{core_0_data[:4] = }")
        for time, *temps in list(
            zip(times, core_0_data, core_1_data, core_2_data, core_3_data)
        )[4:]:
            print(f"{time=} {temps=}")

    with open(input_temps, "r") as temps_file:
        # ----------------------------------------------------------------------
        # Split Data, but Better!
        # ----------------------------------------------------------------------
        times = []
        core_data = [[] for _ in range(0, 4)]

        for time, raw_core_data in parse_raw_temps(temps_file):
            times.append(time)
            for core_idx, reading in enumerate(raw_core_data):
                core_data[core_idx].append(reading)

        for time, *temps in list(zip(times, *core_data))[4:]:
            print(f"{time=} {temps=}")


if __name__ == "__main__":
    main()