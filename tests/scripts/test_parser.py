import subprocess
import pytest
import sys


def run_test(args: list[str], expected_exit_code: int) -> str:
    cmd = ["./execs/test_parser"] + args
    result = subprocess.run(cmd, capture_output=True, text=True)
    assert result.returncode == expected_exit_code
    return (result.stdout + result.stderr).strip()


def test_missing_arguments() -> None:
    args = ["4"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_too_many_arguments() -> None:
    args = ["4", "800", "200", "200", "200", "3", "50", "fifo", "extra"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_negative_coders() -> None:
    args = ["-1", "800", "200", "200", "200", "3", "50", "fifo"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_zero_coders() -> None:
    args = ["0", "800", "200", "200", "200", "3", "50", "fifo"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_negative_compile_required() -> None:
    args = ["4", "800", "200", "200", "200", "-3", "50", "fifo"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_zero_compile_required() -> None:
    args = ["4", "800", "200", "200", "200", "0", "50", "fifo"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_negative_cooldown() -> None:
    args = ["4", "800", "200", "200", "200", "3", "-50", "fifo"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_invalid_characters() -> None:
    args = ["4", "800a", "200", "200", "200", "3", "50", "fifo"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_invalid_scheduler() -> None:
    args = ["4", "800", "200", "200", "200", "3", "50", "bad"]
    out = run_test(args, 1)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_valid_fifo() -> None:
    args = ["4", "800", "200", "200", "200", "3", "50", "fifo"]
    out = run_test(args, 0)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_valid_fifo_upper() -> None:
    args = ["4", "800", "200", "200", "200", "3", "50", "FIFO"]
    out = run_test(args, 0)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


def test_valid_edf() -> None:
    args = ["4", "800", "200", "200", "200", "3", "50", "edf"]
    out = run_test(args, 0)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()


if __name__ == "__main__":
    # If run directly by `python test_parser.py`, run pytest programmatically
    sys.exit(pytest.main(["-v", __file__]))
