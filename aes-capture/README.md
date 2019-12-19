AES Capture
===========

A demo of capturing AES-128 power traces using the ChipWhisperer Lite with the XMEGA target board.

Building
--------

To build the firmware for the ChipWhisperer board and target board, a docker-compose file has been provided. You will need to install Docker and docker-compose on your machine for the build. Run the following command to build the firmware:

```shell
$ docker-compose up
```

The container will automatically exit once the build is complete.

Next, the python requirements must be installed. It is highly recommended that you install the requirements in a virtual environment. The following commands can be used to set up a new virtual environment, activate it, and install the required python packages:

```shell
$ python3 -m venv venv  # For some distros this will be "python"
$ source venv/bin/activate
$ pip install -r requirements.txt
```

Usage
-----

Once you have hooked up the ChipWhisperer Lite to your laptop and the target board, use the `capture.py` script to capture some traces.

```shell
$ ./capture.py --help
usage: capture.py [-h] [-o OUTPUT] [-t TRACES]

optional arguments:
  -h, --help            show this help message and exit
  -o OUTPUT, --output OUTPUT
                        The name of the zipfile to write the traces to. Defaults to 'traces.zip'.
  -t TRACES, --traces TRACES
                        The number of traces to capture. Defaults to 5000.
```

The output zipfile can be passed to the `attack.py` scripts for the correlation power analysis and differential power analysis attacks found in this repository.