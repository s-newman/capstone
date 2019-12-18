#!/usr/bin/env python

import time
import chipwhisperer as cw

from bokeh.plotting import figure, show
from bokeh.io import output_notebook
from bokeh.models import CrosshairTool

NUM_TRACES = 2000
fw_path = 'basic-passwdcheck-CWLITEXMEGA.hex'


def reset_target(scope):
    scope.io.pdic = "low"
    time.sleep(0.05)
    scope.io.pdic = "high_z"
    time.sleep(0.05)


def initialize():
    # ChipWhisperer Lite setup
    scope = cw.scope()
    scope.default_setup()

    # Program the target board
    target = cw.target(scope)
    prog = cw.programmers.XMEGAProgrammer
    cw.program_target(scope, prog, fw_path)

    # Prepare scope for capturing
    scope.gain.db = 34  # works best with this gain for some reason
    scope.adc.samples = 1700 - 170
    scope.adc.offset = 500 + 700 + 170

    # Return the scope and target handles
    return scope, target

def graphtrace(trace):
    p = figure()
    x_range = range(0, len(trace))
    p.line(x_range, trace)
    show(p)

def graphtraceoverlay(trace, new_trace):
    x_range = range(0, len(new_trace))
    p = figure()
    p.add_tools(CrosshairTool())
    p.line(x_range, new_trace)
    p.line(x_range, trace, line_color='red')
    show(p)

#guess a password and return trace
def cap_pass_trace(pass_guess, scope, target):
    ret = ""
    reset_target(scope)
    num_char = target.in_waiting()
    while num_char > 0:
        ret += target.read(num_char, 10)
        time.sleep(0.01)
        num_char = target.in_waiting()

    scope.arm()
    target.write(pass_guess)
    ret = scope.capture()
    if ret:
        print('Timeout happened during acquisition')

    trace = scope.get_last_trace()
    return trace

def checkpass(trace, i):
    return trace[121 + 72 * i] > -0.3

def main():
    scope, target = initialize()

    trace = cap_pass_trace("hax0r\n", scope, target)
    new_trace = cap_pass_trace("\n", scope, target)


    trylist = "abcdefghijklmnopqrstuvwxyz0123456789"
    password = ""
    for c in trylist:
        next_pass = password + c + "\n"
        trace = cap_pass_trace(next_pass,scope,target)
        if checkpass(trace, 0):
            print("Success: " + c)
            break




if __name__ == "__main__":
    main()

