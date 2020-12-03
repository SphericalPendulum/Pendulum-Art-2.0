import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

num_layers = int(input("Enter the number of paint layers you plan to add: "))

# get filenames
filenames = []
for i in range(num_layers):
  filename = input(f'Enter the name of data file #{i+1}: ')
  filenames.append(filename)
  
# load data from files
times, xs, ys = [], [], []
for i in range(num_layers):
  droptime, dropx, dropy = np.loadtxt(filenames[i],usecols=(0,1,2),unpack=True)
  times.append(droptime)
  xs.append(dropx)
  ys.append(dropy)

# get colors for each curve 
colors = []
for i in range(num_layers):
  color = input(f'Enter the color of line number #{i+1} (ex: white or #ddeeff): ')
  colors.append(color)

# get information about background
bg_color = input("Enter the background color of the painting (ex: black or #221100): ")
x_width = float(input("Enter horizontal width of art: "))
y_width = float(input("Enter vertical height of art: "))

# let user show or hide the axis
hide_axis = input("Do you want to hide the axis? [y/n] ")
while hide_axis not in ['y', 'Y', 'n', 'N']:
  hide_axis = input("Do you want to hide the axis? [y/n] ")

if hide_axis in ['y', 'Y']:
  axis_off = True
else:
  axis_off = False

# function to plot the paint paths
def plot_lines(t, xs, ys, colors, bg_color, num_layers, x_width, y_width, off):
  ax.clear()
  ax.set_facecolor(bg_color)
  ax.set_xlim(-x_width/2, x_width/2)
  ax.set_ylim(-y_width/2, y_width/2)
  if off:
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
  for i in range(num_layers):
    ax.plot(xs[i][0:t], ys[i][0:t], color=colors[i])

# handler to animate plot
def animate(t):
  plot_lines(t, xs, ys, colors, bg_color, num_layers, x_width, y_width, axis_off)

# let user choose if they want to see a plot or animation
response = "continue"
while response not in ['P', 'A']:
  response = input("Do you want to plot or animate the results? (Enter P to plot, A to animate): ")

fig,ax = plt.subplots(figsize=(8,8*y_width/x_width)) 

if response == 'P':
  plot_lines(len(times[0]), xs, ys, colors, bg_color, num_layers, x_width, y_width, axis_off)

elif response == 'A':
  Ntimes = range(0,len(times[0]),40)
  anim = animation.FuncAnimation(fig, animate,frames=Ntimes,interval=1,blit=False,repeat=False)

plt.show()
