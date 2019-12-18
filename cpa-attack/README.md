Correlation Power Analysis
==========================

This section is used to perform correlation power analysis attacks against previously-captured traces. It is recommended to capture 50 traces for this attack. Any fewer, and the attack may not work. Too many traces, and the attack will work, but will probably take quite a long time.

Usage
-----

Before running the attack, the python requirements must first be installed. It is recommended that you perform this step in a virtual environment. The following commands can get you set up and working in most environments:

```shell
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

Then, the attack can be run with `./attack.py filename`. For more information, see the helptext in the output of `./attack.py --help`.

Resources
---------

- https://wiki.newae.com/Correlation_Power_Analysis
- https://advancedpersistentjest.com/2018/08/02/correlation-power-analysis-vs-aes/
- https://en.wikipedia.org/wiki/Pearson_correlation_coefficient#For_a_sample
- https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.pearsonr.html#scipy.stats.pearsonr