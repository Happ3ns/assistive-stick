"""
Reads distance readings from the Arduino over serial and logs them to CSV.
Useful for testing the sensor's range and calibrating the beep thresholds.

Usage:
    python serial_logger.py --port COM3 --duration 60
"""

import argparse
import csv
import time
from datetime import datetime
from pathlib import Path

import serial  # pip install pyserial


def log_serial(port: str, baud: int, duration: int, output: Path) -> None:
    print(f"Opening {port} at {baud} baud for {duration}s...")
    with serial.Serial(port, baud, timeout=2) as ser, \
         output.open("w", newline="") as fh:

        writer = csv.writer(fh)
        writer.writerow(["timestamp", "raw_line"])

        start = time.time()
        count = 0
        while time.time() - start < duration:
            line = ser.readline().decode("utf-8", errors="replace").strip()
            if not line:
                continue
            writer.writerow([datetime.now().isoformat(), line])
            print(f"[{count:04d}] {line}")
            count += 1

    print(f"\nLogged {count} lines to {output}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--port", required=True,
                        help="Serial port (COM3 on Windows, /dev/ttyUSB0 on Linux/Mac)")
    parser.add_argument("--baud", type=int, default=9600)
    parser.add_argument("--duration", type=int, default=60,
                        help="How many seconds to log")
    parser.add_argument("--output", type=Path, default=Path("sensor_log.csv"))
    args = parser.parse_args()

    log_serial(args.port, args.baud, args.duration, args.output)


if __name__ == "__main__":
    main()
