""" CS232 Project2 - CmdLineParser.py

This class implements the command line parser.

Student Name: ZeAi Sun (zs35)
Date: Jan 27, 2023
"""
import os

class CmdLineParser:
    
    """ The constructor takes the user input and splits the command into separate words. """
    def __init__(self, cmd):
        self.cmd = cmd
        self.cmd_list = self.cmd.split(" ")		# Split the command into words and put into a list.
        self._runInBg = 0						# If _runInBg == 1, the program should be run in the background.
        
        self.check_for_ampersand()				# Check if the command ends in &.
            
    """ Check_for_ampersand() method checks if the command includes & and needs to be handled in background. """
    def check_for_ampersand(self):
        if ("&" not in self.cmd_list):			# If command line doesn't include &, no operation needed.
            pass
        elif (self.cmd_list[-1] == "&"):		# If ends in &, change the _runInBg variable to 1.
            self._runInBg = 1
        else:
            print("Error: Ampersand at the wrong location.")	# If includes & but doesn't end in &, print an error.