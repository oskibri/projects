import mylib.module as mod

def testhello():
    res = mod.testing("Oskar")
    assert res == "Hello, Oskar!"
