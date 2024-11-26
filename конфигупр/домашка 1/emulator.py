import os
import zipfile
import csv
import logging
from commands import ShellCommands
from gui import EmulatorGUI

class Emulator:
    def __init__(self, config_file):
        self.load_config(config_file)
        self.setup_logging()
        self.fs = ShellCommands(self.virtual_fs_path, self.username)

    def load_config(self, config_file):
        with open(config_file, 'r') as file:
            reader = csv.DictReader(file)
            config = next(reader)
            self.username = config['username']
            self.virtual_fs_path = config['virtual_fs_path']
            self.log_file = config['log_file']

    def setup_logging(self):
        logging.basicConfig(filename=self.log_file, level=logging.INFO, format='%(message)s')

    def log_action(self, command):
        logging.info(f'{self.username}: {command}')

    def start(self):
        gui = EmulatorGUI(self.fs, self.log_action)
        gui.run()

if __name__ == "__main__":
    emulator = Emulator('config.csv')
    emulator.start()
