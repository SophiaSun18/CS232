""" CS232 Project2 - Cmd_cd.py

This class implements methods related to the cd command.

Student Name: ZeAi Sun (zs35)
Date: Jan 28, 2023
"""
import os

class Cmd_cd:
    
    """ The construtor receives a command list and check if the command is valid. """
    """ If so, change the directory. """
    def __init__(self, cmd_list):
        self.cmd_line = cmd_list
        
        if self.check_path_legal() == True:			# Check if the path is legal (eg: have one and only one string for the path.)
            self.path = self.cmd_line[1]
            self.change_dir(self.path)
    
    """ Check if the command line includes a legal path. """
    def check_path_legal(self):
        if len(self.cmd_line) == 2:					# If the command list include exact 2 elements, it's a legal cd command.
            return True
        else:
            print("Error: invalid path in the command.")			# If not, print an error.

    """ Change the directory to the input path. """
    def change_dir(self, path):
        try:
            os.chdir(path)
        except FileNotFoundError:					# If the directory doesn't exist, handle the error.
            print("Error: No such file or directory.")