import subprocess


def test_dongle_acquisition() -> None:
    cmd = ["./execs/test_dongle"]
    result = subprocess.run(cmd, capture_output=True, text=True)

    assert result.returncode == 0
    output = result.stdout.strip()
    print()
    print(output)

    # We expect 3 requests, 3 acquires, and 3 releases
    assert "Coder 1 requesting dongle" in output
    assert "Coder 1 ACQUIRED dongle" in output
    assert "Coder 1 releasing dongle" in output

    assert "Coder 2 requesting dongle" in output
    assert "Coder 2 ACQUIRED dongle" in output
    assert "Coder 2 releasing dongle" in output

    assert "Coder 3 requesting dongle" in output
    assert "Coder 3 ACQUIRED dongle" in output
    assert "Coder 3 releasing dongle" in output

    # Since they have staggered start times (10ms, 20ms, 30ms),
    # Coder 1 should acquire first
    assert output.find("Coder 1 ACQUIRED") < output.find("Coder 2 ACQUIRED")
    assert output.find("Coder 2 ACQUIRED") < output.find("Coder 3 ACQUIRED")
