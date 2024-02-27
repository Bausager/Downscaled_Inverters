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

New fueatures waiting to be implemented can be found on the github project site [Not a Generator (NaG)](https://github.com/users/Bausager/projects/2)

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

And project maintainer- Me! [Michelle Bausager](https://www.linkedin.com/in/michelle-bausager/) A former student and research assistance at AU who likes to work with all aspects of inverters.

## Git Workflow.
For students or others who want to contribute, a workflow is needed to make sure everything still works in the end.
main.c on the main branch is written in such a way that every function is implementet but commented out.
This means there's a funtional implementation of every feature avaliable ready to use.

To make sure the workflow is allined a smal guide it here presented;

### Download the repository and work on an existing branch
Create of find a folder for the Git project and open your terminal in that folder.
Grab the git link and use the following git commands to download the project
```
git clone https://github.com/Bausager/Git_Tutorial.git
```
It’s good practice to get an overview of the project, especially the branches.
It's also here you would start if you come back to code some more!
```
git pull
git branch -a
```
There’s probably a need to code in a specific branch, if you're not in the right branch you need to select it from the list. 
Now you need to update it localy as follows:
```
git checkout specific_branch
git pull origin specific_branch
```
You can now start to make changes to the code!
To commit it, firstly you need to make sure the branch is up to date.
Then the "git add -A" commits all files and now you have to write some comments on the changes you made
Now you can push it to git!
```
git pull origin specific_branch
git add -A
git commit -m "Head line for changes
>
>
> Discription of what has been done "
git push origin specific_branch
```

### Make a new branch
Firstly make sure you have been invited to be a contributor.
Then starting working on a new feature first pull from the main branch
```
git pull origin main
```
Now you need to create a new branch where you can make your new implementations. Remember to give it a valuable name, such as "UltraCoolNewPLL".
After creating it you need to be in ýour new branch, with the opteration "checkout".
```
git branch new_branch
git checkout new_branch
```
You can now start to make changes to the code!
Since it's a new branch you don't need to make sure it's already updated as you do after you've commitet the branch for the first time.
Then the "git add -A" commits all files and now you have to write some comments on the changes you made.
```
git add -A
git commit -m "Head line for changes
>
>
> Discription of what has been done "
```
First time pushing a new branch you need to push it like this
```
git push -u origin new_branch
```
After that you can simply go to the workflow presented in *Download the repository and work on an existing branch*

### Marge branch to main
When the feature is done and tested, it's time to merge with the main branch.
I 










