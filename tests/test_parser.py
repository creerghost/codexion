from ctypes import (CDLL, Structure,
                    POINTER, byref,
                    c_int, c_long, c_char_p, c_byte,
                    Array)
import os
import pytest
import sys

# Load the shared library
lib_path = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                        "libcodexion.so"))
lib = CDLL(lib_path)


class t_sim(Structure):
    _fields_ = [
        ("num_coders", c_int),
        ("time_to_burnout", c_long),
        ("time_to_compile", c_long),
        ("time_to_debug", c_long),
        ("time_to_refactor", c_long),
        ("num_compiles_req", c_int),
        ("dongle_cooldown", c_long),
        ("scheduler", c_int),
        ("padding", c_byte * 256),
        # Padding to ensure enough memory for the rest of the struct
    ]


lib.parse_args.argtypes = [c_int, POINTER(c_char_p), POINTER(t_sim)]
lib.parse_args.restype = c_int


def run_test(args: list[str], expected_exit_code: int) -> None:
    full_args: list[str] = ["./codexion"] + args
    ac: int = len(full_args)

    av: Array[c_char_p] = (c_char_p * ac)()
    for i, arg in enumerate(full_args):
        av[i] = arg.encode('utf-8')

    sim: t_sim = t_sim()
    result: int = lib.parse_args(ac, av, byref(sim))

    # parse_args returns 1 on success, 0 on failure
    # expected_exit_code is 1 for failure, 0 for success
    expected_result = 0 if expected_exit_code == 1 else 1
    assert result == expected_result


def test_missing_arguments() -> None:
    run_test(["4", "800"], 1)


def test_too_many_arguments() -> None:
    run_test(["4", "800", "200", "200", "200", "3", "50", "fifo", "extra"], 1)


def test_negative_coders() -> None:
    run_test(["-1", "800", "200", "200", "200", "3", "50", "fifo"], 1)


def test_zero_coders() -> None:
    run_test(["0", "800", "200", "200", "200", "3", "50", "fifo"], 1)


def test_negative_compile_required() -> None:
    run_test(["4", "800", "200", "200", "200", "-3", "50", "fifo"], 1)


def test_zero_compile_required() -> None:
    run_test(["4", "800", "200", "200", "200", "0", "50", "fifo"], 1)


def test_negative_cooldown() -> None:
    run_test(["4", "800", "200", "200", "200", "3", "-50", "fifo"], 1)


def test_invalid_characters() -> None:
    run_test(["4", "800a", "200", "200", "200", "3", "50", "fifo"], 1)


def test_invalid_scheduler() -> None:
    run_test(["4", "800", "200", "200", "200", "3", "50", "bad"], 1)


def test_valid_fifo() -> None:
    run_test(["4", "800", "200", "200", "200", "3", "50", "fifo"], 0)


def test_valid_fifo_upper() -> None:
    run_test(["4", "800", "200", "200", "200", "3", "50", "FIFO"], 0)


def test_valid_edf() -> None:
    run_test(["4", "800", "200", "200", "200", "3", "50", "edf"], 0)


if __name__ == "__main__":
    # If run directly by `python test_parser.py`, run pytest programmatically
    sys.exit(pytest.main(["-v", __file__]))
