import os
import subprocess
import sys
from typing import List, Optional, Tuple


class CodexionTestSuite:
    """
    A comprehensive test suite for the Codexion simulation.
    Manages test execution, log rotation, and edge case validation.
    """

    def __init__(self) -> None:
        """
        Initializes the test suite.
        Sets up absolute directories for the test outputs and
        clears the previous log file.
        """
        self.script_dir = os.path.dirname(os.path.abspath(__file__))
        self.output_dir = os.path.abspath(
            os.path.join(self.script_dir, "..", "output")
        )
        os.makedirs(self.output_dir, exist_ok=True)
        self.log_file = os.path.join(self.output_dir, "test_results.txt")
        self.success = 0
        self.total = 0

        # Clear the log file at the start of each test suite run
        with open(self.log_file, "w") as f:
            f.write("")

    def log_output(self, cmd: List[str], output: str) -> None:
        """
        Appends the standard output and standard error of a simulation run
        to the global test_results.txt log file.

        Args:
            cmd (List[str]): The exact bash command array that was executed.
            output (str): The combined stdout and stderr of the command.
        """
        with open(self.log_file, "a") as f:
            f.write(f"=== Command: {' '.join(cmd)} ===\n")
            f.write(output)
            f.write("\n" + "=" * 40 + "\n\n")

    def run_codexion(
        self,
        args: List[str],
        expected_exit: int = 0,
        expect_burnout: bool = False,
        timeout: Optional[float] = None,
    ) -> bool:
        """
        Executes a single simulation test run with the given arguments.

        Args:
            args (List[str]): The arguments to pass to the ./codexion binary.
            expected_exit (int): The expected exit code of the binary
            (0 for success, 1 for errors).
            expect_burnout (bool): Whether the simulation is expected to log
            "burned out".
            timeout (Optional[float]): Maximum execution time in seconds
            before sending SIGTERM.

        Returns:
            bool: True if the test matches expected outcomes, False otherwise.
        """
        cmd = ["../codexion"] + [str(a) for a in args]
        print(f"Running: {' '.join(cmd)} ...", flush=True)
        try:
            result = subprocess.run(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=timeout,
            )
            output = result.stdout + result.stderr
            self.log_output(cmd, output)

            if result.returncode != expected_exit:
                print(
                    f"FAIL: Expected exit code {expected_exit}, "
                    f"got {result.returncode}\nOutput: {output}",
                    flush=True,
                )
                return False
            has_burnout = "burned out" in output
            if expect_burnout and not has_burnout:
                print("FAIL: Expected burnout, but none found.", flush=True)
                return False
            if not expect_burnout and has_burnout:
                print(
                    "FAIL: Expected NO burnout, but someone died.", flush=True
                )
                return False

            print("PASS", flush=True)
            return True
        except subprocess.TimeoutExpired as e:
            output = e.stdout.decode() if e.stdout else ""
            if e.stderr:
                output += e.stderr.decode()

            self.log_output(cmd, output + "\n(Timeout Reached)")

            if expect_burnout:
                print("FAIL: Timed out waiting for burnout.", flush=True)
                return False
            has_burnout = "burned out" in output
            if has_burnout:
                print("FAIL: Someone died before timeout.", flush=True)
                return False
            print("PASS (Timeout)", flush=True)
            return True

    def run_suite(self) -> bool:
        """
        Main execution loop for the test suite.
        Runs all predefined validation, survival, death, and infinite
        test scenarios.

        Returns:
            bool: True if all tests passed (success == total), False otherwise.
        """
        print("--- Input Validation Tests ---", flush=True)
        tests: List[Tuple[List[str], int, bool, Optional[float]]] = [
            # Wrong args count
            (["5", "800", "200"], 1, False, None),
            (
                ["5", "800", "200", "200", "200", "7", "0", "FIFO", "EXTRA"],
                1,
                False,
                None,
            ),
            # Bad characters
            (
                ["five", "800", "200", "200", "200", "7", "0", "FIFO"],
                1,
                False,
                None,
            ),
            (
                ["5", "-800", "200", "200", "200", "7", "0", "FIFO"],
                1,
                False,
                None,
            ),
            # Zeros for positive-only args (coders, requires at least 1)
            (
                ["0", "800", "200", "200", "200", "7", "0", "FIFO"],
                1,
                False,
                None,
            ),
            (
                ["5", "800", "200", "200", "200", "0", "0", "FIFO"],
                1,
                False,
                None,
            ),
            # Invalid scheduler
            (
                ["5", "800", "200", "200", "200", "7", "0", "RR"],
                1,
                False,
                None,
            ),
        ]

        for t in tests:
            if self.run_codexion(*t):
                self.success += 1
            self.total += 1

        print("\n--- Death Edge Cases ---", flush=True)
        tests = [
            (
                ["1", "800", "200", "200", "200", "7", "0", "FIFO"],
                0,
                True,
                2.0,
            ),
            (["2", "310", "200", "100", "0", "7", "0", "FIFO"], 0, True, 2.0),
            (["3", "310", "200", "100", "0", "7", "0", "FIFO"], 0, True, 2.0),
            (
                ["5", "100", "200", "200", "200", "7", "0", "FIFO"],
                0,
                True,
                2.0,
            ),
            (["4", "310", "200", "100", "0", "7", "0", "FIFO"], 0, True, 2.0),
            (
                ["5", "800", "400", "400", "100", "7", "0", "FIFO"],
                0,
                True,
                2.0,
            ),
        ]

        for t in tests:
            if self.run_codexion(*t):
                self.success += 1
            self.total += 1

        print("\n--- Survival Scenarios ---", flush=True)
        tests = [
            (
                ["2", "800", "200", "200", "200", "7", "0", "FIFO"],
                0,
                False,
                5.0,
            ),
            (
                ["3", "800", "200", "200", "200", "7", "0", "FIFO"],
                0,
                False,
                5.0,
            ),
            (
                ["5", "800", "200", "200", "200", "7", "0", "FIFO"],
                0,
                False,
                5.0,
            ),
            (
                ["5", "800", "200", "200", "200", "7", "0", "EDF"],
                0,
                False,
                5.0,
            ),
            (["4", "410", "200", "200", "0", "7", "0", "FIFO"], 0, False, 5.0),
            (
                ["10", "800", "200", "200", "200", "2", "0", "EDF"],
                0,
                False,
                5.0,
            ),
            (
                ["50", "800", "200", "200", "200", "1", "0", "FIFO"],
                0,
                False,
                5.0,
            ),
            (
                ["100", "800", "200", "200", "200", "1", "0", "EDF"],
                0,
                False,
                10.0,
            ),
        ]

        for t in tests:
            if self.run_codexion(*t):
                self.success += 1
            self.total += 1

        print("\n--- Infinite Scenarios ---", flush=True)
        tests = [
            (
                ["5", "800", "200", "200", "200", "1000", "0", "FIFO"],
                0,
                False,
                2.0,
            ),
            (
                ["4", "410", "200", "200", "0", "1000", "0", "EDF"],
                0,
                False,
                2.0,
            ),
        ]

        for t in tests:
            if self.run_codexion(*t):
                self.success += 1
            self.total += 1

        print(
            f"\nFinal Result: {self.success}/{self.total} tests passed.",
            flush=True,
        )
        return self.success == self.total


if __name__ == "__main__":
    suite = CodexionTestSuite()
    if not suite.run_suite():
        sys.exit(1)
