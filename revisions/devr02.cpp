/*==============================================================================

	devR version 0.2
	COPYRIGHT (c) 2013 NAVEEN VENKAT
	ALL RIGHTS RESERVED

================================================================================

	WARNING: UNAUTHORISED COPYING, REPRODUCTION, RENTAL, SALE, MODIFICATION,
				FRAGMENTATION,	COMPILATION, DISASSEMBLY, PUBLICATION, DERIVATIVE
				WORKS, REVERSE	ENGINEERING,  OF ANY KIND OF ANY PART OF THIS
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
			Pentium 4 @ 2.0 GHz
			512 MB RAM
			64 MB Video Card
			104 KB Hard Disk Space (for devr.exe alone)
			Keyboard

================================================================================

	WHAT'S NEW?

			- ICOGNITO MODE

==============================================================================*/

#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <process.h>

float version=0.2;
fstream REGISTRY;
fstream HISTORY("core",fstream::app);


char INPUT[128];
char RAM[128];
char USER[40];

int INIT=0;
int ICOGNITO=0;

void CALL_HELP();
void CALL_INIT();
void CALL_CLOSE();
void CALL_OPEN();
void CALL_ERASE();
void CALL_ICOGNITO(int);
void login();

void check(char input[])
{
		if(ICOGNITO==0)
		{HISTORY << "[" << INIT << "] " << input << endl;}
		else
      {HISTORY << "[" << INIT << "] " << "ICOGNITO" << endl;}

		if(!strcmp(input,"_CLR"))
		{	clrscr();	}

		else if(!strcmp(input,"_ICOGNITO_1"))
		{	CALL_ICOGNITO(1);	}

		else if(!strcmp(input,"_ICOGNITO_0"))
		{	CALL_ICOGNITO(0);	}

		else if(!strcmp(input,"_INIT"))
		{	CALL_INIT();	}

		else if(!strcmp(input,"_OPEN"))
		{	CALL_OPEN();	}

		else if(!strcmp(input,"_CLOSE"))
		{	CALL_CLOSE();	}

		else if(!strcmp(input,"_HELP"))
		{	CALL_HELP();	}

		else if(!strcmp(input,"_ERASE"))
		{	CALL_ERASE();	}

		// WRITE OTHER COMMANDS IN else if STATEMENT ONLY! OTHERWISE THEY WILL
		// BE WRITTEN INTO THE FILE

		else
		{
			if(INIT==1)
			{	REGISTRY << input << endl;	}
		}
}

int main()
{
	login();
	clrscr();
	HISTORY << endl << "\t[STARTED BY: " << USER << "]\n";
	cout << "DEVR - Developer Redefined | version " << version << endl << "Copyright (c) 2013 Naveen Venkat" << endl;
	cout << "Type _HELP for help." << endl << "--------------------------------------------------------------------------------" << endl;

	do
	{
		cout << INIT << " >> ";
		gets(INPUT);
		check(INPUT);
	} while(strcmp(INPUT,"_EXIT"));

	HISTORY.close();
	if(INIT==1){REGISTRY.close();}
	exit(0);
	return 0;
}

void CALL_INIT()
{

	if(INIT==1)
	{
		cout << "- ERR: Please close the existing file before initialising a new file!";
		cout << endl;
	}
	else
	{
		cout << "- Enter the path of the file: ";
		gets(INPUT);
		HISTORY << "[" << INIT << "] " << INPUT << endl;

		if(!strcmp(INPUT,""))
		{
			cout << "- ERR: Please enter a valid file path!";
			cout << endl;
		}
		else
		{
			cout << endl;

			REGISTRY.open(INPUT,fstream::app);
			cout << "- INITIALISATION SUCCESSFUL!";
			cout << endl << "- WORKING ON FILE: " << INPUT << endl << endl;
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
	cout << "_ERASE: Erase a file (clear all the data written in it)." << endl;
	cout << "_ICOGNITO_1: Enable icognito mode (nothing will be saved in history)." << endl;
	cout << "_ICOGNITO_0: Disable icognito mode." << endl;
	cout << "_CLR: Clear the screen." << endl;
	cout << "_HELP: Display this help screen." << endl << endl;
	cout << "devR version " << version << "\nCreated and Developed by Naveen Venkat\nwww.devr.webs.com\nnmakes@outlook.com\n\n";
}

void CALL_OPEN()
{
	if(INIT==1)
	{
		cout << "- ERR: Please close the existing file before opening a new file!";
		cout << endl;
	}
	else if(INIT==0)
	{
		cout << "- Enter the path of the file: ";

		gets(INPUT);
		HISTORY << "[" << INIT << "] " << INPUT << endl;

		if(!strcmp(INPUT,""))
		{
			cout << "- ERR: Please enter a valid file path!";
			cout << endl;
		}

		else
		{
			REGISTRY.open(INPUT,fstream::in);
			INIT = 1;

			clrscr();

			if(!REGISTRY.eof())
			{
				while(REGISTRY.eof()!=1)
				{
					REGISTRY.getline(RAM,128);
					cout << RAM << endl;
				}
			}
			else
			{
				cout << "- The file is empty!";
			}

			REGISTRY.close();
			INIT = 0;
		}
	}
}

void CALL_ERASE()
{
	if(INIT==1)
	{
		cout << "- ERR: Please close the existing file before erasing a file!";
		cout << endl;
	}
	else
	{
		cout << "- Enter the path of the file: ";
		gets(RAM);
				HISTORY << "[" << INIT << "] " << RAM << endl;

		if(!strcmp(RAM,""))
		{
			cout << "- ERR: Please enter a valid file path!";
			cout << endl;
		}
		if(!strcmp(RAM,"core"))
		{
			cout << "- ERR: Cannot erase the core file!";
			cout << endl;
		}
		else
		{
			REGISTRY.open(RAM,fstream::app);
			INIT=1;
			REGISTRY >> RAM;

			if(REGISTRY.eof()==1)
			{
				cout << "-ERR: File does not exist. By default, an empty file has been created.";
				cout << endl;
				REGISTRY.close();
				INIT=0;
			}
			else
			{
				REGISTRY.clear();

				cout << "- Successfully Erased!";
				cout << endl;

				REGISTRY.close();
				INIT=0;
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
		cout << "- ICOGNITO MODE OFF. Text and commands that you type WILL BE saved in the history.\n";
	}
}
