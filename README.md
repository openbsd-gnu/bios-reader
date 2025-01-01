How Does this work?

Well it first of reads your filesystem /usr/sbin/dmidecode and checks if dmidecode is working and available on your Operating System.
The program uses popen to execute dmidecode commands and retrieve output.
The program checks for the presence of dmidecode before attempting to execute it.
This code assumes dmidecode is installed and accessible. If not, instruct the user to install or locate it manually.
