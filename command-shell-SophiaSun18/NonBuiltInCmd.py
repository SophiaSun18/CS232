""" CS232 Project2 - NonBuiltInCmd.py

This class implements methods used to handle the Non-Built-In command.

Student Name: ZeAi Sun (zs35)
Date: Feb 4, 2023
"""
import os
from PathParser import PathParser
from CmdLineParser import CmdLineParser

class Non_Built_In_Cmd:
    
    """ The constructor receives a command, checks in which mode should the command be run, and runs the command. """
    def __init__(self, cmd):
        
        self.cmd = cmd.cmd_list
        self.path = self.cmd[0]			# Store the first element in the cmd_list to be the path.
        self.args = self.cmd[1:]		# Store all other elements in the cmd_list to be the arguments.
        self.pathname = ""				# Set up an empty pathname for now.
        self.prog_name = self.path.split("/")[-1]		# Set up the last element of the path to be the program name.
        self.if_bg = cmd._runInBg		# Set up the _runInBg variable.
        
        if self.args != [] and self.args[-1] == "&":	# Checks if the argument list includes &. If so, remove it to avoid issues.
            self.args = self.args[:-1]
        
        if (self.check_if_full_pathname() == True):		# Checks if the command includes a full path name.
            if (self.check_if_executable(self.prog_name) == True):		# If so, further check if the program exists and is executable.
                self.run_the_command()			# If so, run the command.
            
        else:											# If the command doesn't have a full path name.
            p = PathParser()							# Create a new PathParser and search for the program.
            
            if (p.find(self.prog_name) == ""):			# If the program is not found, prints an error.
                print("Error: Program not found.")
            
            else:										# If the program is found, update the pathname and run the command.
                self.pathname = p.find(self.prog_name) + "/" + self.prog_name
                self.run_the_command()
            
    """ This method checks if the command has a full pathname. """
    def check_if_full_pathname(self):
        
        for p in self.path.split("/")[:-1]:				# Join the pathname together except the filename.
            self.pathname += "/"
            self.pathname += p
        
        return os.path.isdir(self.pathname)				# Return if the path is an actual directory.
        
    """ This method checks if the command is executable. """
    def check_if_executable(self, program):
    
        cwd = os.getcwd()				# Get and store the current working directory.
    
        os.chdir(self.pathname)			# Go to the directory where the file is stored.
        
        if os.path.isfile(program) and os.access(program, os.X_OK) == True:		# If it's executable, return true. If not, print an error.
            return True
        else:
            print("Error: File not executable.")
        
        os.chdir(cwd)					# Move back to the previous working directory.
    
    """ This part consults http://www.dabeaz.com/python/tutorial/beazley_advanced_python/Slides/SLIDE053.HTM. """
    """ This method actually runs the command. """
    def run_the_command(self):
        
        pid = os.fork()			# Create a child process.
        
        if pid == 0:			# The child process.
            
            if self.args == []:			# If the argument list is empty, append the program name.
                self.args.append(self.prog_name)
            else:						# If the argument list is not empty, insert the program name to be the first element.
                self.args.insert(0, self.prog_name)
            
            try:
                os.execvp(self.prog_name, self.args)		# Run the program and handle any possible errors.
            except:
                print("Error: Something wrong happens.")
                
        else:					# The parent process.
            
            print(f"[Child pid: {pid}]")	# Print the message.
            
            if self.if_bg == 1:				# If the child process needs to be handles in the background, use waitpid().
                os.waitpid(-1, os.WNOHANG)
            else:							# If not, use wait() and pring the message again.
                os.wait()
                print(f"[{pid} -> 0]")