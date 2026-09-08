inputs
- speed and shit over time
- currently at 1 data per second, expecting dramatic increase

outputs
- display clearly the different drivers based on starts and stops
- display max and average velocity per driver period

Easy initial implementation
- excel input and output with
    - color coding per driver period
    - inserted lines with max and average speed
    - color coding on max speed lines

shoot the moon implementation
- nice gui
- file selection input
    - mass file selection and operation
- graphical interpretation alongside different output options

genuinely not very achievable:
- integrate with gps-based position view
- full replays based on input data with corresponding mapping to 3d view of simulated time position

remaining questions:
- what would be most helpful for the team as far as interpretation
- how matlab work? integration?




## Desired main grid:

| select input file | export as xlsx with options* |
for each segment:
| graph over time | stats (avg speed, max speed) | set label

### xlsx export options:
- only active periods
- select periods to include
- export as all one file or file per period
- 


## To do
- [ ] graph display of periods
- [X] auto start for debugging
- [ ] more robust data importing (~xlsx~, handle header rows being included)
- [ ] pretty up graphs, better display of time values (custom graphs rather than default pyplot?)
- [ ] use pandas-accelerated processing instead of current bs
- [ ] merged data from active periods


Notes:
- time is 2080 before gps bootup
- time is always in GT-0