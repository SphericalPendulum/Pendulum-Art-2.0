import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# ask user for filenames and necessary inputs
trajectory = input("Please enter the filename of the file storing the pendulum trajectory: ")
paintdrops = input("Please enter the filename of the file storing the path of the paint: ")
height = float(input("Enter height of pendulum attachment point from the ground: "))
print()

# set up plot axes and view
fig,ax = plt.subplots(figsize=(10,10))
ax = plt.axes(projection='3d')

# load data
time, x, y, z, vx, vy, vz = np.loadtxt(trajectory,usecols=(0,1,2,3,4,5,6),unpack=True)
droptime, dropx, dropy = np.loadtxt(paintdrops,usecols=(0,1,2),unpack=True)

# axis limits for plot
x_lower, x_higher = (min(dropx)-0.5, max(dropy)+0.5)
y_lower, y_higher = (min(dropy)-0.5, max(dropy)+0.5)
z_lower, z_higher = (0, height+0.5)

def animate(t):
  ''' function to describe animation '''
  ax.clear()
  #Set up Axes
  ax.set_xlim(x_lower, x_higher)
  ax.set_ylim(y_lower, y_higher)
  ax.set_zlim(z_lower, z_higher)
  #Shapes
  ax.plot3D((0,x[t]),(0,y[t]),(height,z[t]), color='black', linewidth=2)
  ax.scatter3D(0,0,height, color='black')
  ax.scatter3D(x[t], y[t], z[t], s=300, color="grey")
  #Plots
  ax.plot3D(x[0:t], y[0:t], z[0:t], 'blue', linewidth=0.25)
  ax.plot3D(dropx[0:t],dropy[0:t],0,'green', linewidth=0.4)
  #ax.plot3D(x,y,0,"orange")
  ax.scatter3D(0,0,0, color='grey', s=2)
  #Time
  ax.text2D(0.6, 0.9, f'Time = {time[t]} seconds', transform=ax.transAxes, size = 15)

print("Animating...")

# animate the plot
Ntimes = range(0,len(time),40)  # change animation speed by changing the number 40
anim = animation.FuncAnimation(fig, animate,frames=Ntimes,interval=1,blit=False,repeat=True) 
plt.show()