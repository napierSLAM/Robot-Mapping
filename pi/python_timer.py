#!/usr/bin/env python3
# basic timer for redrawing map

starttime=time.time()
while True:
  print "tick"
  time.sleep(60.0 - ((time.time() - starttime) % 60.0))
