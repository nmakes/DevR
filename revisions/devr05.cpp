/*==============================================================================

	DEVR version 0.5
	COPYRIGHT (c) February 2013 - March 2013 NAVEEN VENKAT
	ALL RIGHTS RESERVED

================================================================================

	WARNING: UNAUTHORISED COPYING, REPRODUCTION, RENTAL, SALE, MODIFICATION,
				FRAGMENTATION,	COMPILATION, DISASSEMBLY, PUBLICATION, DERIVATIVE
				WORKS, REVERSE	ENGINEERING OF ANY KIND OF ANY PART OF THIS
				SOFTWARE IS A CRIME AND CAN BE PENALISED WITH CRIMINAL CHARGES.
				PLEASE READ THE LICENCE AGREEMENT ATTESTED WITH THE SOFTWARE
				CAREFULLY BEFORE USING THE SOFTWARE. IF YOU DO NOT AGREE WITH ANY OF
				THE ABOVE TERMS AND THE TERMS MENTIONED IN THE LICENCE AGREEMENT,
				DESTROY ANY COPY OF THE SOFTWARE IMMEDIATELY.

================================================================================

	WEBSITE: www.devr.webs.com
	EMAIL: nmakes@outlook.com

================================================================================

	MINIMUM SYSTEM REQUIREMENTS:

			Windows Operating System
			Pentium 4 @ 2.0 GHz Or equivalent
			512 MB RAM
			64 MB Video Card
			116 KB Hard Disk Space (for devr.exe alone)
			Keyboard

================================================================================

	WHAT'S NEW?

			- _MEMORY command to view the current RAM utilisation
			- 128K utilisation of RAM
			- IMPROVED core check function (Non-case sensitive checking)
			- Improved file handling system
			- Improved _DEBUG mode (can delete core file)
			- HIST flag, to check whether the history file is open or not
			  (If True, history is written, Else file remains closed)
			- Alarm Sounds

==============================================================================*/

#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <process.h>

float version=0.5;
fstream REGISTRY;
fstream HISTORY("core",fstream::app);

char INPUT[128];
char USER[16];
char EXE[11]="devr05.exe";

int INIT=0;
int ICOGNITO=0;
int HIST=1;

void CALL_HELP();
void CALL_INIT();
void CALL_CLOSE();
void CALL_OPEN();
void CALL_DELETE();
void CALL_ICOGNITO(int);
void CALL_REBOOT();
void CALL_COPY();
void CALL_MEMORY();
void CALL_UNINSTALL_DEVR();
void login();
void core(char*);
int corecheck(char*);

void check()
{
		if(HIST)
		{
			core(INPUT);
		}

		if(!strcmp(INPUT,"_CLR"))
		{	clrscr();	}

		else if(!strcmp(INPUT,"_ICOGNITO_1"))
		{	CALL_ICOGNITO(1);	}

		else if(!strcmp(INPUT,"_ICOGNITO_0"))
		{	CALL_ICOGNITO(0);	}

		else if(!strcmp(INPUT,"_INIT"))
		{	CALL_INIT();	}

		else if(!strcmp(INPUT,"_OPEN"))
		{	CALL_OPEN();	}

		else if(!strcmp(INPUT,"_CLOSE"))
		{	CALL_CLOSE();	}

		else if(!strcmp(INPUT,"_COPY"))
		{	CALL_COPY();	}

		else if(!strcmp(INPUT,"_HELP"))
		{	CALL_HELP();	}

		else if(!strcmp(INPUT,"_DELETE"))
		{	CALL_DELETE();	}

		else if(!strcmp(INPUT,"_MEMORY"))
		{	CALL_MEMORY();	}

		else if(!strcmp(INPUT,"_UNINSTALL_DEVR"))
		{	CALL_UNINSTALL_DEVR();	}

		// WRITE OTHER COMMANDS IN else if STATEMENT ONLY! OTHERWISE THEY WILL
		// BE WRITTEN INTO THE FILE

		else
		{
			if(INIT==1)
			{	REGISTRY << INPUT << endl;	}
		}
}

int main()
{
	login();
	clrscr();
	HISTORY << endl << "\t[STARTED BY: " << USER << "]\n";
	cout << "DEVR - Developer Redefined | version " << version << endl
		  << "Copyright (c) 2013 Naveen Venkat" << endl;
	cout << "Type _HELP for help." << endl
		  << "--------------------------------------------------------------------------------"
		  << endl;

	do
	{
		cout << INIT << " >> ";
		gets(INPUT);
		check();
	} while(strcmp(INPUT,"_EXIT"));

	HISTORY.close();
	if(INIT==1)
	{
		REGISTRY.close();
	}
	return(0);
   exit(0);
}

void CALL_INIT()
{

	if(INIT==1)
	{
		cout << "*ERROR* Please close the existing file before initialising a new file!\a";
		cout << endl;
	}
	else
	{
		cout << "- Enter the path of the file: ";
		gets(INPUT);
		core(INPUT);

		if(!strcmp(INPUT,""))
		{
			cout << "*ERROR* Please enter a valid file path!\a";
			cout << endl;
		}
		else if(corecheck(INPUT) && (strcmp(USER,"_DEBUG")))
		{
			cout << "*ERROR* Cannot override the core file!\a";
			cout << endl;
		}
		else if(!strcmp(INPUT,EXE) && (strcmp(USER,"_DEBUG")))
		{
			cout << "*ERROR* Cannot override devr!\a";
			cout << endl;
		}
		else
		{
			REGISTRY.open(INPUT,fstream::app);
			cout << "- INITIALISATION SUCCESSFUL!";
			cout << endl << "- WORKING ON FILE: " << INPUT << endl;
			INIT = 1;
		}
	}
}

void CALL_CLOSE()
{
	if(INIT==1){REGISTRY.close();}
	INIT = 0;
}

void CALL_HELP()
{
	clrscr();
	cout << "_INIT: Initialise a file (write data into it)." << endl;
	cout << "_CLOSE: Close an open file." << endl;
	cout << "_OPEN: Open a file to read data from it." << endl;
	cout << "_COPY: Copy a file into another file." << endl;
	cout << "_DELETE: Delete a file (clear all the data written in it)." << endl;
	cout << "_ICOGNITO_1: Enable icognito mode (nothing will be saved in history)." << endl;
	cout << "_ICOGNITO_0: Disable icognito mode." << endl;
	cout << "_CLR: Clear the screen." << endl;
	cout << "_MEMORY: Show the present RAM resource information." << endl;
	cout << "_HELP: Display this help screen." << endl;
	cout << "_UNINSTALL_DEVR: Uninstall devr (Saying goodbye to devr)." << endl << endl;
	cout << "devR version " << version << "\nCreated and Developed by Naveen Venkat\nwww.devr.webs.com\nnmakes@outlook.com\n\n";
}

void CALL_OPEN()
{

	if(INIT==1)
	{
		cout << "*ERROR* Please close the existing file before opening a new file!\a";
		cout << endl;
	}
	else if(INIT==0)
	{
		cout << "- Enter the path of the file: ";
		gets(INPUT);
		core(INPUT);

		if(!strcmp(INPUT,""))
		{
			cout << "*ERROR* Please enter a valid file path!\a";
			cout << endl;
		}

		else
		{
			REGISTRY.open(INPUT,fstream::in);
			INIT = 1;

			if(!REGISTRY.good())
			{
				cout << "*ERROR* The file does not exist!\a" << endl;
			}
			else
			{
				clrscr();
				while(REGISTRY.eof()!=1)
				{
					REGISTRY.getline(INPUT,128);
					cout << INPUT << endl;
				}
				cout << "--------------------------------------------------------------------------------" << endl;
			}

			REGISTRY.close();
			INIT = 0;
		}
	}
}

void CALL_DELETE()
{
	if(INIT==1)
	{
		cout << "*ERROR* Please close the existing file before deleting a file!\a" << endl;
	}
	else if(!strcmp(USER,""))
	{
		cout << "*ERROR* Protected Command!\a" << endl;
	}
	else
	{
		cout << "- Enter the path of the file: ";
		gets(INPUT);
		core(INPUT);

		if(!strcmp(INPUT,""))
		{
			cout << "*ERROR* Please enter a valid file path!\a";
			cout << endl;
		}
		else if( corecheck(INPUT) && strcmp(USER,"_DEBUG") )
		{
			cout << "*ERROR* Cannot delete the core file!\a";
			cout << endl;
		}
		else if(!strcmp(INPUT,EXE) && (strcmp(USER,"_DEBUG")))
		{
			cout << "*ERROR* Please use _UNINSTALL_DEVR command to uninstall devr!\a";
			cout << endl;
		}
		else
		{
			REGISTRY.open(INPUT,fstream::in);
			INIT=1;

			if(!REGISTRY.good())
			{
				cout << "*ERROR* The file does not exist!\a" << endl;
				REGISTRY.close(); INIT = 0;
			}
			else
			{
				REGISTRY.close(); INIT = 0;
				if (corecheck(INPUT) && !strcmp(USER,"_DEBUG"))
				{
					HISTORY.close(); HIST = 0;
				}

				remove(INPUT);

				cout << "- Successfully Deleted!";
				cout << endl;
			}
		}
	}
}

void login()
{
	cout << "USERNAME: "; gets(USER);
}

void CALL_ICOGNITO(int x)
{
	if(x)
	{
		ICOGNITO=1;
		cout << "- ICOGNITO MODE ON. \n- Text and commands that you type WILL NOT BE saved anywhere in the history.";
		cout << "\n- However, it will not affect the files that you edit.";
		cout << "\n- Be wary of:";
		cout << "\n\tMalicious software that tracks your keystrokes";
		cout << "\n\tSurveillance by secret agents";
		cout << "\n\tPeople standing behind you\n";
	}
	else
	{
		ICOGNITO=0;
		cout << "- ICOGNITO MODE OFF." << endl;
		cout << "- Text and commands that you type WILL BE saved in the history.\n";
	}
}

void CALL_COPY()
{
	fstream TEMPFILE; char RAM[128];

	if(INIT==1)
	{
		cout << "*ERROR* Please close the existing file before copying a file!\a";
		cout << endl;
	}
	else if(!strcmp(USER,""))
	{
		cout << "*ERROR* Protected Command!\a" << endl;
	}
	else if(INIT==0)
	{
		cout << "- Enter the path of the source file: ";
		gets(INPUT);
		core(INPUT);


		if(!strcmp(INPUT,""))
		{
			cout << "*ERROR* Please enter a valid file path!\a" << endl;
		}
		else
		{
			REGISTRY.open(INPUT,fstream::in);
			if(!REGISTRY.good())
			{
				cout << "*ERROR* Source file not found!\a" << endl;
				REGISTRY.close(); INIT = 0;
			}
			else
			{
				REGISTRY.close(); INIT = 0;
				cout << "- Enter the path of the destination file: ";
				gets(RAM);
				core(RAM);

				if(!strcmp(RAM,""))
				{
					cout << "*ERROR* Please enter a valid file path!\a";
					cout << endl;
				}
				else
				{
					REGISTRY.open(INPUT,fstream::in); INIT = 1;
					TEMPFILE.open(RAM,fstream::out);

					while(REGISTRY.eof()!=1)
					{
						REGISTRY.getline(INPUT,128);
						TEMPFILE << INPUT << endl;
					}

					cout << "- Successfully Copied!" << endl;

					REGISTRY.close(); INIT = 0;
					TEMPFILE.close();
				}
			}
		}
	}
}

void CALL_MEMORY()
{
	cout << "*RAM INFO*" << endl;
	cout << "- [" << sizeof(version) << "B] version: " << version;
	cout << "\n- [" << sizeof(INPUT) << "B] INPUT: " << INPUT;
	cout << "\n- [" << sizeof(USER) << "B] USER: " << USER;
	cout << "\n- [" << sizeof(INIT) << "B] INIT: " << INIT;
	cout << "\n- [" << sizeof(ICOGNITO) << "B] ICOGNITO: " << ICOGNITO;
	cout << endl;
}

void CALL_UNINSTALL_DEVR()
{
	char ch;
	cout << "- ARE YOU SURE? (Y/N): ";
	cin >> ch;

	if(ch=='y'||ch=='Y')
	{
		cout << "- Initiating Self Destruct Mode";
		REGISTRY.close();
		HISTORY.close();
		cout << "\n- Deleting files: " << endl;
		cout << "\t+ core";
		remove("core");
		cout << "\n\t+ " << EXE;
		remove(EXE);
		cout << "\n\n\t\t\tR.I.P devr\n\tA peaceful goodbye. What else can we say.\n\t  Thank you for using devr, by the way!";
      cout << endl;
	}
	exit(0);
}

void core(char a[])
{
	if(!ICOGNITO)
	{
		HISTORY << "[" << INIT << "] " << a << endl;;
	}
	else
	{
		HISTORY << "[" << INIT << "] " << "<{[ICOGNITO]}>" << endl;
	}
}

int corecheck(char a[])
{
	if(strlen(a)==4)
	{
		if( (a[0]=='c' || a[0]=='C') && (a[1]=='o' || a[1]=='O') &&
			 (a[2]=='r' || a[2]=='R') && (a[3]=='e' || a[3]=='E')   )
		{
			return 1;
		}
		else
		{	return 0;	}
	}
	else
	{	return 0;	}
}
