#!/usr/bin/env python
import string
import re
import sys
import locale

# Read lines from log file and return logins and logout as event objects
class Parser:
	def __init__(self, file):
		self.source = open(file, "r")
	def parse_line(self):
		line = self.source.readline()
		while line:
			if re.search('Start', line):
				# 20040513 14:52:12 Start session for user johndoe from IP 192.168.1.10.
				pattern = '(\d+) (\d+):(\d+):(\d+) Start session for user ([\w ]+) from IP (\d+)\.(\d+)\.(\d+)\.(\d+)\.'
				type = "opened"
			elif re.search('End', line):
				# 20040513 14:52:12 End session for user johndoe from IP 192.168.1.10.
				pattern = '(\d+) (\d+):(\d+):(\d+) End session for user ([\w ]+) from IP (\d+)\.(\d+)\.(\d+)\.(\d+)\.'
				type = "closed"
			else:
				line = self.source.readline()
				continue
			# result[0][0]: date, result[0][1]: hours, result[0][2]: minutes, result[0][3]: seconds,
			# result[0][4]: user, result[0][5]: IP1, result[0][6]: IP2, result[0][7]: IP3, result[0][8]: IP4
			re_es = re.compile(pattern, re.LOCALE)
			result = re_es.findall(line);
			if result:
				item = Event(type, result[0])
				return item
			line = self.source.readline()

# Holds one login or logout
class Event:
	def __init__(self, type = "any", data = ['?', '?', '?', '?', '?', '?', '?', '?', '?']):
		self.type = type
		self.date = data[0]
		self.time = string.join((str(data[1]), str(data[2]), str(data[3])), ':')
		self.user = data[4]
		self.ip = string.join((str(data[5]), str(data[6]), str(data[7]), str(data[8])), '.')
		self.id = 0
		self.closed = 0

# Holds a list of login events and a list of logout events
class Sessions:
	def __init__(self):
		self.id = 0
		self.opened = {}
		self.closed = {}
	def add(self, event):
		if event.type == "opened":
			self.id = self.id + 1
			self.opened[self.id] = event
		elif event.type == "closed":
			corresponding_id = self.locate_login(event.user, event.ip, event.date)
			if corresponding_id > 0:
				self.closed[corresponding_id] = event
		else:
			return
	def locate_login(self, user, ip, date):
		for id, event in self.opened.iteritems():
			if event.user == user and event.ip == ip and event.date == date and event.closed == 0:
				event.closed = 1
				return id
		return 0
	def display(self, sep):
		result = ""
		for event_id in self.opened:
			open_event = self.opened[event_id]
			line = string.join((open_event.date, open_event.time, open_event.user, open_event.ip), sep)
			if self.closed.has_key(event_id):
				close_event = self.closed[event_id]
				line = line + sep + string.join((close_event.date, close_event.time), sep)
			else:
				line = line + sep + "?" + sep + "?"
			result = result + line + "\n"
		return result

locale.setlocale(locale.LC_ALL, '')

if (len(sys.argv) > 2):
	parser = Parser(sys.argv[1])
	medusa = Sessions()
	event = parser.parse_line()
	while (event):
		medusa.add(event)
		event = parser.parse_line()
	f_dest = open(sys.argv[2], "w")
	f_dest.write(medusa.display(";"))
	f_dest.close()
