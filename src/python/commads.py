#!/usr/bin/python2
# -*- coding: utf-8 -*-
#Look for start to end, dump the snippet if found
sts="<commands>"
eds="</commands>"
import sys
print ("Run as %s INPUT1 [INPUT2] [...]"%sys.argv[0])
for fn in sys.argv[1:]:
	print ("Processing %s "%fn)
	of = "%s_output_commands.xml"%fn
	infile = open(fn, "rb")
	indata = infile.read()
	infile.close()
	print ("File read, looking for payload ")
	st = indata.find(sts)
	fs = indata.count(sts)
	print("marker at %d, found %d"%(st, fs))
	if fs == 1:
		ndm = indata.find(eds)
		ndm += len ( e d s )
		print ("end marker at %d"%ndm)
		comdata = indata[st:ndm]
		off = open(of, "wb")
		off.write(comdata)
		off.close()
		print("Wrote%s, %d bytes "%(of, len(comdata)))
	else:
		print ("failure... ’%s’ %d"%(fn, fs))