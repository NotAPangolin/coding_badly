import pandas as pd

from PyQt6.QtWidgets import *
from PyQt6.QtCore import Qt

import matplotlib.pyplot as plt

from Plotting import TableModel, MplCanvas

class DriverPeriod:
    def __init__(self, data:pd.DataFrame|None = None, names:list[str]|None=None):
        if data is None:
            self.data = pd.DataFrame(columns=names)
        else:
            self.data = data

        self.index:int = None

        self.checkbox:QCheckBox = None
        self.button:QPushButton = None
        self.plot:MplCanvas = None
        self.labelsWidget:QWidget = None

    def aggregate_from_frames(self, frames:list[pd.DataFrame]):
        self.data = pd.concat(frames, ignore_index=True)

    def genDisplayElements(self, gridLayout:QGridLayout, setIndex:int|None=None):
        if setIndex is not None: self.index = setIndex

        # Create Checkbox
        self.checkbox = QCheckBox()
        
        # Create Button
        self.button = QPushButton(f"open period {self.index+1}, is drive: {self.is_real_drive()}")
        self.button.setStyleSheet("background-color: rgb(94, 196, 218)" if self.is_real_drive() else "background-color: gray")
        self.button.pressed.connect(self.open_data_pyplot_win)

        # Plot
        if self.is_real_drive():
            self.plot = MplCanvas()
            self.plot.plot_df(self.data)
        # self.period_open_buttons[-1].setMinimumHeight(50)

        # labels
        self.textEdit = QTextEdit()
        self.textEdit.setMaximumSize(100,30)
        self.textEdit.setPlaceholderText("Enter Name...")
        self.textEdit.setLineWrapMode(QTextEdit.LineWrapMode.NoWrap)

        labelLayout = QVBoxLayout()
        labelLayout.setAlignment(Qt.AlignmentFlag.AlignTop)
        labelLayout.addWidget(self.textEdit)
        labelLayout.addWidget(QLabel(f"Max Speed: {self.max_speed}"))
        labelLayout.addWidget(QLabel(f"Avg Speed: {self.avg_speed}"))
        self.labelsWidget = QWidget()
        self.labelsWidget.setLayout(labelLayout)
        self.labelsWidget.setMinimumHeight(300)


        ##Assign
        # Create Checkbox
        gridLayout.addWidget(self.checkbox, self.index+1, 0)

        # Button 
        gridLayout.addWidget(self.button, self.index+1, 1)

        # Labels
        gridLayout.addWidget(self.labelsWidget, self.index+1, 3)

        # Create Plot
        gridLayout.addWidget(self.plot, self.index+1, 2)

    def setName(self, val:str):
        self.textEdit.setText(val)

    def getName(self):
        if self.textEdit.toPlainText():
            return self.textEdit.toPlainText()
        else:
            return str(self.index + 1)

    def showGui(self):
        self.checkbox.show()
        self.button.show()
        # self.plot.
        self.labelsWidget.show()
    def hideGui(self):
            self.checkbox.hide()
            self.button.hide()
            # self.plot.
            self.labelsWidget.hide()

    def append_row(self, row:pd.Series):
        # print(f'before: {self.data}')
        self.data.loc[self.len] = row
        # print(f'after: {self.data}\n\n')

    def open_data_pyplot_win(self):
        # print('plotting...')
        # print(self.data)
        self.data.plot(x = 'Time', y='Speed')

        plt.show()

        # sc = MplCanvas()
        # sc.axes.plot(data["Time"].to_numpy(),data["Speed"].to_numpy())
        # # self.main_layout.addWidget(sc, 1,1)
        # sc.show()
        # self.plots.append(sc)

    def open_table_view_win(self):
        self.tablev = QTableView()
        self.tablev.setModel(TableModel(self.tablev, self.data))
        self.tablev.setGeometry(100,100,500,500)
        self.tablev.show()

    def debug_print(self):
        print(f'is real drive?: {self.is_real_drive()} len: {self.len}, first item: {self.data["Speed"][0]}, first time: {self.data["Time"][0]}, last time: {self.data["Time"][max(0, self.data.index[-1])]}, max speed: {self.max_speed}, avg speed: {self.avg_speed}, time dif: {self.duration}')

    def isSelected(self):
        return self.checkbox.isChecked()

    def is_real_drive(self):
        '''
        determines whether this Period is *probably* a real drive instance or not

        :return: false when speeds are 0 or time period is less than 5 seconds
        '''
        # print(f"first speed: {(self.first_speed())} - {type(self.first_speed())} duration: {self.duration} - {type(self.duration)}-----------------")
        # firstSpeed = (self.data["Speed"].get(0) != 0)
        # duration = (self.data["Time"].max() - self.data["Time"].min())
        # min_dur = pd.Timedelta(5, unit="second")
        # is_dur = (duration >= min_dur)
        # return firstSpeed and is_dur
        return (self.first_speed() != 0) and (self.duration >= pd.Timedelta(5, unit="second"))

    def first_speed(self) -> float:
        return self.data["Speed"][0]
        
    @property
    def len(self) -> int:
        return self.data.__len__()

    @property
    def duration(self) -> pd.Timedelta:
        return self.data["Time"].max() - self.data["Time"].min()

    @property
    def max_speed(self):
        return self.data["Speed"].max()
    @property
    def avg_speed(self):
        return self.data["Speed"].mean()
