import subprocess
import pytest
import sys


def run_test(args: list[str], expected_exit_code: int) -> None:
    cmd = ["./test_parser"] + args
    result = subprocess.run(cmd, capture_output=True, text=True)
    assert result.returncode == expected_exit_code


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
