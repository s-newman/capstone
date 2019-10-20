AES Demo
========

A demo of cracking AES-128 with differential power analysis.

Building
--------

To build the firmware (I think it's firmware?) for this, a docker-compose file
has been provided. Run the following command to build the stuff:

```shell
docker-compose up
```

The container will automatically exit once the build is complete.

Then, install the python requirements:

```shell
pip install -r requirements.txt
```

Now you can hack.