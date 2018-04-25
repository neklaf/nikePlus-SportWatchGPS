#! /usr/bin/python2
def __init__(self) :
	pass

#Opcode to text mapping
opcode_mapping = {
'E1' : 'serial', 'E0' : 'model',
'E3' : 'emped−setup', 'E2' : 'hwrevision',
'EE' : 'test−reminders', 'ED' : 'test−lcd',
'EA' : 'test−adc', 'EC' : 'test−sflash',
'EB' : 'test−accel', '38' : 'hrs−info',
'E7' : 'test−buzzer', '4A' : 'option−fuel',
'11' : 'eeprom−erase', '10' : 'readWorkouts',
'13' : 'battery', '12' : 'eeprom−query',
'15' : 'desktop−write', '14' : 'desktop−read',
'33' : 'option−weigth', '32' : 'option−metric',
'31' : 'option−24hour', '37' : 'emped−info',
'36' : 'option−gender', '35' : 'option−age',
'52' : 'ephemeris−update', '48' : 'option−lap−metric',
'44' : 'option−clockset−mode', '54' : 'gpspatch−update',
'51' : 'ephemeris−query', '53' : 'gpspatch−query',
'3C' : 'option−clock', '3E' : 'option−reminder−mode',
'3D' : 'option−laps', '02' : 'restore−defaults',
'03' : 'latchup', '26' : 'flags−sync',
'01' : 'Unknown', '21' : 'time',
'04' : 'bootblock', '05' : 'console−write',
'46' : 'option−speed', '47' : 'option−ui−mode',
'08' : 'version', '09' : 'upgrade',
'42' : 'option−records', '40' : 'option−sounds',
'41' : 'writeAttaboy', 'E9' : 'test−button',
'E8' : 'test−backlight', 'E5' : 'test−nordic',
'E4' : 'test−gps', '3A' : 'wo−loop',
'E6' : 'test−power', '45' : 'wo−loop−auto'
}

opcode_ints = {}
for (k, v) in opcode_mapping.items():
	val = int(k, base=16)
	opcode_ints[val] = v