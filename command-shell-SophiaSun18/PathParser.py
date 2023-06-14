""" CS232 Project2 - PathParser.py

This class implements methods related to PATH.

Student Name: ZeAi Sun (zs35)
Date: Jan 27, 2023
"""
import os

class PathParser:
    
    """ The constructor gets the value of the path and splits it into a list of directories. """
    def __init__(self):
        self.path = os.getenv("PATH")
        self.path_list = self.path.split(":")
    
    """ The find(cmd) method scans through the list of directories and finds the command. """
    def find(self, cmd):
        
        result = ""
        
        for path in self.path_list:			# Scan through all the directories.
            if os.path.exists(path):		# If the path exists, scan it.
                scan = os.scandir(path)
                
                for s in scan:				# Check through each files under each directories.
                    if (cmd == s.name):
                        result = path
            
        return result						# If the command is found, return the path. If not, return an empty string.