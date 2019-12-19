#!/usr/bin/env python
import argparse
import json
import time
from zipfile import ZipFile

import chipwhisperer

FIRMWARE_PATH = "simpleserial-aes-CWLITEXMEGA.hex"


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-o",
        "--output",
        help="The name of the zipfile to write traces to. Defaults to 'traces.zip'.",
        default="traces.zip",
    )
    parser.add_argument(
        "-t",
        "--traces",
        type=int,
        help="The number of traces to capture. Defaults to 5000.",
        default=5000,
    )
    return parser.parse_args()


def reset_target(scope):
    scope.io.pdic = "low"
    time.sleep(0.05)
    scope.io.pdic = "high_z"
    time.sleep(0.05)


def initialize():
    # ChipWhisperer Lite setup
    scope = chipwhisperer.scope()
    scope.default_setup()

    # Program the target board
    target = chipwhisperer.target(scope)
    prog = chipwhisperer.programmers.XMEGAProgrammer
    chipwhisperer.program_target(scope, prog, FIRMWARE_PATH)

    # Prepare scope for capturing
    scope.gain.db = 34  # works best with this gain for some reason
    scope.adc.samples = 1700 - 170
    scope.adc.offset = 500 + 700 + 170

    # Return the scope and target handles
    return scope, target


def main():
    args = parse_args()

    # Set up boards
    scope, target = initialize()

    # Capture traces
    traces = []
    keygen = chipwhisperer.ktp.Basic()
    keygen.fixed_key = True
    keygen.fixed_plaintext = False
    while len(traces) <= args.traces:
        # Get next key and plaintext
        key, text = keygen.next()

        trace = chipwhisperer.capture_trace(scope, target, text, key)
        if trace is None:
            continue
        traces.append(trace)

    # Pull out the data that we want from the traces
    trace_array = [trace.wave for trace in traces]
    plaintext_array = [trace.textin for trace in traces]

    # Save to json in zip
    with ZipFile(args.output, "w") as zipfile:
        with zipfile.open("traces.json", "w") as tracefile:
            traces = {
                "traces": trace_array,
                "plaintexts": plaintext_array,
            }
            json.dump(tracefile)


if __name__ == "__main__":
    main()
