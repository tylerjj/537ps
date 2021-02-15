Program: 537ps
Author: Tyler Johnston
cs_username: tjohnston
email: tjjohnston2@wisc.edu

Contribution:
	- This project was done by myself, as an individual.
	
	- I heavily utilized tutorials, man files, piazza, etc in 
	order to shore up my lack of familiarity with C. I tried to be 
	dilligent about posting links to the sites referenced.
	Much of what went into this project had been long forgotten
	(such as pointers, structs, C file parsing, compiling, etc.)
	
	- An area I know I'm clearly lacking is [Error Management]. This
	is the singlemost neglected area of my program from both a design
	and implementation point of view. This was put off to the end due
	to uncertainty about how to implement, and then never returned to
	due to time constraints. 
	
Program Description: 
	- http://pages.cs.wisc.edu/~bart/537/programs/program1.html
	- ^ Dead Link. See PDF PA01 containing project specs in project 
	folder.
	- General Summary:
		a simple version of the ps command. Your version of ps,
		called 537ps be executed from a command line. It will read a variety 
		of information about one or more running programs (processes) on the 
		computer, and then display that information. 
		
		As an example of what your program will do, consider a command 
		such as:
				537ps -p 1234 -s -U -c

		This runs your ps command, and displays the status letter (in this 
		case, running), amount of user time, and the command line for process 
		1234. 
		
		You might expect the output to look like:
			1234: R utime=150 [myprog -x -y file1 myoption]

Design Structure:

	PRIMARY CONTROLLER
		ps537(main.c)
			- Takes in command line information. 
			- Gets inputsettings data from optionhandler. 
			- Gets process data from prochandler. 
			- Calls outputprinter to display our process data 
			according to user specified input.
		
	MODEL MODULE
		inputsettings.c
			- primary data structure for data passing from the 
			optionhandler to ps537 and ps537 to outputprinter.
		processdata.c
			- primary data structures for data passing from the
			prochandler to ps537 and from ps537 to outputprinter.
		buffer.c
			- This object is mostly a helper structure to pass more
			information from processcmdline to the prochandler.
	INPUT MODULE
		optionhandler.c
			- Parses commandline arguments from ps537 and returns
			inputsettings data to ps537.
	
	PROC MODULE			
		prochandler.c
			- outermost handler of all /proc directory navigation
			and calls to within the module.
			- Takes in a list of pids and a count. If (count > 0),
			get a list of processes with the specified pid. Otherwise
			get a list of all processes containing this user's uid.
			- Returns a list of processes (data included) to ps537.
		processstatus.c
			- Given a pid, returns the uid for that process.
			(This parsing is done in the /proc/[pid]/status filepath,
			hence the file naming.)
		processstat.c
			- Given a pid, returns a ProcessStat object with data
			for the specified process from /proc/[pid]/stat back to
			the prochandler. 
			- (NOTE: Failed implementation beyond bare requirements
			for this project. The only values ProcessStat will set 
			are pid, stat, utime, and stime. Any other values are not
			updated.)
		processstatm.c
			- Given a pid, returns a ProcessStatm object with data
			for the specified process from /proc/[pid]/statm back to
			the prochandler.
		processcmdline.c
			- Given a pid, returns a Buffer object with cmdline data
			for the specified process from /proc/[pid]/cmdline
	OUTPUT MODULE
		outputprinter.c
			- (Note: outputhandler might've been a better and more
			consistent naming strategy.)
			- Takes the inputsettings and processdata from ps537 and
			outputs proccessdata values to the console based upon the
			flags set in inputsettings.	
