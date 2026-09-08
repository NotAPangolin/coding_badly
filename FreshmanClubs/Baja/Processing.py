import pandas as pd

import matplotlib.pyplot as plt

from DriverPeriod import DriverPeriod

class FileProcessor:
    debug = False

    names = ["Time","Latitude","Longitude","Altitude","AccelX","AccelY","AccelZ","GyroX","GyroY","GyroZ","MagX","MagY","MagZ","GC Temp","Speed","Box Temp","Batt Volt"]

    def __init__(self, path:str):
        if path.endswith(".csv"):
            self.data = pd.read_csv(path, names=self.names, parse_dates=["Time"], date_format="%Y-%m-%d %H:%M:%S" )
        elif path.endswith(".xlsx"):
            self.data = pd.read_excel(path, names=self.names, parse_dates=["Time"], date_format="%Y-%m-%d %H:%M:%S")
        else:
            raise Exception("idk what to do with that, gimme a csv or xlsx")

        # Clean up rows with null values (typically its on Time, in current data)
        self.data.dropna(axis='index', how='any', inplace=True)

        self.periods:list[DriverPeriod] = []

    def run_data(self):
        self.split_by_driver_period()

    ## Shitty iteration-based version
    def split_by_driver_period(self):
        prev_was_0vel = None
        for index, row in self.data.iterrows():
            # is there motion on this row?
            this_0vel = (row["Speed"] == 0)

            # if motion -> no motion or vice versa, make a new period
            if prev_was_0vel != this_0vel:
                self.periods.append(DriverPeriod(names=self.names))

            self.periods[-1].append_row(row)
            prev_was_0vel = this_0vel

        # if self.debug:
        #     print("\n\nPeriods:\n")
        #     for dperiod in self.periods:
        #         # print(f'speedes: {dperiod.data["Speed"]}')
        #         # print(f'[EXTERN] len: {dperiod.len}, first item: {dperiod.data["Speed"][0]}, first time: {dperiod.data["Time"][0]}, last time: {dperiod.data["Time"][max(0, dperiod.data.index[-1])]},')# max speed: {self.max_speed}, avg speed: {self.avg_speed}, time dif: {self.duration}')
        #         dperiod.debug_print()
        #         print(dperiod.data.head(5))
        #         print("-------------------------------------------------------------------------\n-------------------------------------------------------------------------\n")