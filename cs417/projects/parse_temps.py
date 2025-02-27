#! /usr/bin/env python3


# Found from Thomas Kennedy: https://github.com/cstkennedy/cs417-examples/blob/master/SemesterProject-CPU-Temps/python3/parse_temps.py
"""
This module is a collection of input helpers for the CPU Temperatures Project.
All code may be used freely in the semester project, iff it is imported using
``import parse_temps`` or ``from parse_temps import {...}`` where ``{...}``
represents one or more functions.
"""

import re
from typing import Generator, TextIO


def parse_raw_temps(
    original_temps: TextIO, step_size: int = 30
) -> Generator[tuple[float, list[float]], None, None]:
    """
    Take an input file and time-step size and parse all core temps.

    Args:
        original_temps: an input file

        step_size: time-step in seconds

    Yields:
        A tuple containing the next time step and a List containing _n_ core
        temps as floating point values (where _n_ is the number of CPU cores)
    """

    split_re = re.compile(r"[^0-9]*\s+|[^0-9]*$")

    for step, line in enumerate(original_temps):
        yield (step * step_size), [
            float(entry) for entry in split_re.split(line) if len(entry) > 0
        ]