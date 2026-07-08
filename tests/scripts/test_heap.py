import subprocess


def run_heap_test(args: list[str]) -> str:
    cmd = ["./execs/test_heap"] + args
    result = subprocess.run(cmd, capture_output=True, text=True)
    assert result.returncode == 0
    return result.stdout.strip()


def test_heap_sort_basic() -> None:
    args = ["100", "17", "36", "25", "19", "7", "3", "2", "1"]
    out = run_heap_test(args)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()
    assert out == "1 2 3 7 17 19 25 36 100"


def test_heap_sort_duplicates() -> None:
    args = ["5", "5", "1", "1", "3"]
    out = run_heap_test(args)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()
    assert out == "1 1 3 5 5"


def test_heap_already_sorted() -> None:
    args = ["1", "2", "3", "4"]
    out = run_heap_test(args)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()
    assert out == "1 2 3 4"


def test_heap_reverse_sorted() -> None:
    args = ["4", "3", "2", "1"]
    out = run_heap_test(args)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()
    assert out == "1 2 3 4"


def test_heap_single_element() -> None:
    args = ["42"]
    out = run_heap_test(args)
    print(f"\nArgs:    {' '.join(args)}")
    print(f"Output:  {out}")
    print()
    assert out == "42"
