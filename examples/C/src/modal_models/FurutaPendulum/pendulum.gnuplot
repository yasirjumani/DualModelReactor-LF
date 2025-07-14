#! gnuplot
# Gnuplot commands for the FurutaPendulum.lf program.

set title 'Pendulum'            # Set graph title

set xlabel "Time (seconds)"     # Set x axis label

set terminal pdf size 5, 3.5    # Set the output format to PDF
set output 'pendulum.pdf'       # Set output file.

# Add mode labels
set label "SwingUp" at 0.2, -1.2
set label "Catch" at 1.1, -0.2
set label "Stabilize" at 1.2, 1.1

set datafile separator ','      # Set CSV input format
set key autotitle columnhead    # Set y axis labels based on column headers

plot 'pendulum.csv' using 1:2 with lines linetype 1 linewidth 2, \
     ''             using 1:3 with lines linetype 2 linewidth 2, \
     ''             using 1:4 with lines linetype 3 linewidth 2, \
     ''             using 1:5 with lines linetype 4 linewidth 2
