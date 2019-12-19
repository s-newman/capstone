RSA Demo
========

A demo of simple power analysis with RSA.

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

Now you can hack.