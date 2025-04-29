ECE220 Lab 3: “Divide and Conquer”
Winter 2023 • C / CLion

Overview
This project implements Laboratory 3 from the University of Alberta’s ECE 220 “Programming for Engineering” course. Its goal is to demonstrate core C programming concepts—buffer management, modular functions, and control flow—by reading a stream of test data, performing one of six operations on each data set, and validating the results via a built-in tester.

Key Features
Modular design

reading(): fills an input buffer from the provided get_value() stream

transferring(): copies data between buffers

processing(): computes one of six operations (min, max, odd count, even count, min+max, odd+even counts)

submitting(): prints results and calls submit_results() for pass/fail feedback

Buffer inspection

After each stage, prints the contents of the input, local, or output buffer so you can trace data flow

Automatic test harness

Integrates with provided io.c/io.h to validate each test case and display a summary of successes or failures

Clean re-initialization

Clears all buffers before each new cycle to avoid stale data

How It Works
Initialization

Three int [64] buffers (input, local, output) are zeroed out.

Reading

Call get_value() once for an operation ID.

If ID = –1, the program exits. Otherwise, call get_value() to get the data count, then read that many subsequent values into the input buffer.

Transferring to Local

Copy the entire active region ([0..count+1]) from the input buffer into the local buffer.

Processing

Based on operation ID, compute:

MIN → minimum value

MAX → maximum value

ODD → count of odd numbers

EVEN → count of even numbers

MINMAX → both min and max

ODDEVEN → count of odd and even

Overwrite the first two slots of the local buffer with [ID, resultCount] and write the result(s) into the next slot(s).

Transferring to Output & Submitting

Copy the processed region from local to output, then print it.

Call submit_results(outputBuffer) to validate against the hidden test suite; on success/failure a summary table is printed.

Loop

Reset all buffers to zero, then repeat from step 2 until an operation ID of –1 is encountered.
