# Downscaled three-phase half-bridge inverter
This project is an inverter framework for students and researches to learn, test and research state-of-the-art phase-lock-loops and control algorithms.
The inverters manly uses jellybean components, found free at the electronic laboratory for electrical engineers at Aarhus University(AU) for their students.
The purpose is to make an inexpensive and save platform instead of having to work with line voltages. 
This means all the components can be downscaled to work with 5 volt.
Here the inverter can be powered by a USB and supply its own grid.

This is an accumulative project, this means it's going to improve over time. 
There's a limited number of people working on this which means updates somethimes takes sometime.
If you want to help improve, collaborate or have something in your back pocket you want to integrate, you are very welcome to contact me!
The more the merrier!

There're some restrictions!
Since this is an open-source, student use it and research need to be understood and replicated, the code needs to be written in such a way that other prople can understand it.
Even if the person isn't an expert.
That is importent!


## University Teaching

### Phase-Lock-Loop(PLL)
Many students at AU before this project have worked in PLLs for their bachelor thesis that meant a large part of the project was making an inverter from scratch.
This allows students not to reinvent the wheel if they are interested in other aspects than the hardware side.
With this the students can generate the grid and test their PLL on the some PCB, which lowest the bar of entre and in turn makes student projects and bachelor thesis more focused.

### Control
The students have the ability to develop control methods and test it only with a one inverter and output impedances.
Here different filter configuration or switching methods can also influence the THD which the students new have a direct way to interacting with.

### Power Factor Correction(PFC)
This PCB also allows to make it work as a PFC where control, THD and other aspects can be looked into.
Here a PFC input with a inverter output can also be pursued.


## Research Projects
Even if grid impedances does not downscale well, control algorithms, stability and many other advanced concept can be tested.
In the future, a new version of the PCB will be made for increasing the DC Link voltage to accommodate some of the downsides of the downscaled grid impedances.
As the time of writing the increase of DC Link voltage would be around 24V.
Now multiply inverters can be chained to a common grid to research stability.
Here the goal is not only to use the same micro-controller and control but to use different kinds of controls, PLLs, micro-controller, changing grid impedances, short-circuits and much more.
This will also include black start, synchronisation and much more.

## Collaborators
This project was initially an idea developed under [Associate Professor Uffe Jakobsen](https://pure.au.dk/portal/en/persons/uja%40ece.au.dk) for his classes and research into inverter control.
He also has students doing their project and bachelor thesis helping expand on this project.

A contributor [Christian Lind Vie Madsen](https://www.linkedin.com/in/christian-karl-oscar-lind-vie-madsen-11606a9b/) helps optimising written code for better performance.

Owner of project- Me! [Michelle Bausager](https://www.linkedin.com/in/michelle-bausager/) A former student and research assistance at AU who likes to work with all aspects of inverters.
