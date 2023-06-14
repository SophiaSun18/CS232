""" CS232 Project2 - A Command Shell

This program runs a command shell implemented with Python.

Student Name: ZeAi Sun (zs35)
Date: Jan 27, 2023
"""
import os
from PathParser import PathParser
from CmdLineParser import CmdLineParser
from Cmd_cd import Cmd_cd
from NonBuiltInCmd import Non_Built_In_Cmd

""" The main program. """
while True:
    
    # Print the current working directory as the prompt and ask for the command.
    prompt = input(os.getcwd() + "/$ ")
    
    # If command is [exit], break the loop and end the program.
    if prompt == "exit":
        break
    
    # If the program doesn't end, read and run the command.
    else:
        cmd_line = CmdLineParser(prompt)
        cmd = cmd_line.cmd_list[0]
        
        # If the command is [pwd], print the current working directory.
        if cmd == "pwd":
            print(os.getcwd())
        # If the command is [cd], change the cwd to the given directory.
        elif cmd == "cd":
            cd = Cmd_cd(cmd_line.cmd_list)
        # If the command is none of the above, handle it as a non-built-in command.
        else:
            NBI_cmd = Non_Built_In_Cmd(cmd_line)


