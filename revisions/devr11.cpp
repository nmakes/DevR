/*==============================================================

	DEVR version 1.1
	COPYRIGHT (c) February 2013 - September 2013 NAVEEN VENKAT
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

	WEBSITE: www.devr.webs.com [BETA]
	EMAIL: nmakes@outlook.com

================================================================================

	RECOMMENDED MINIMUM SYSTEM REQUIREMENTS:

			OS: Windows Platform
			CPU: 1.0 GHz (16bit, 32bit and 64bit supported)
			RAM: 512 MB (Windows XP and lower), 1GB (Windows Vista and higher)
			VIDEO: Standard VGA Monitor
			STORAGE: 200 KB
			PERIPHERAL: Keyboard

================================================================================

	WHAT'S NEW?

         - Shifted the _MEMORY and _UNINSTALL devr commands to console
         - Fixed the encrypt / decrypt bug
         - Updated exe name

==============================================================================*/

#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>
#include <ctype.h>

float version=1.1; // UPDATE THIS EVERY TIME!!!
fstream REGISTRY;
fstream HISTORY("core",fstream::app);

char INPUT[128];
char USER[32];
char EXE[11]="devr11.exe"; // UPDATE THIS EVERY TIME!!!
char APP_NAME[4]="devr";
int CONSOLE_WIDTH = 80;
char CONSOLE_COLOR[9] = "Color 1F";

int INIT=0;
int INCOGNITO=0;
int HIST=1;
int CRYPT=0;

void CALL_CLR();
void CALL_HELP();
void CALL_INIT();
void CALL_CLOSE();
void CALL_OPEN();
void CALL_DELETE();
void CALL_INCOGNITO(int);
void CALL_REBOOT();
void CALL_COPY();
void CALL_MEMORY();
int CALL_UNINSTALL_DEVR();
void CALL_SWITCH_USER();
void CALL_ENCRYPT();
void CALL_DECRYPT();
void CALL_CONSOLE();
void CALL_COLOR();
void CALL_REFRESH();
int encrypt(char&);
void decrypt(int, char&);
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
		{	CALL_CLR();	}

		else if(!strcmp(INPUT,"_INCOGNITO_1"))
		{	CALL_INCOGNITO(1);	}

		else if(!strcmp(INPUT,"_INCOGNITO_0"))
		{	CALL_INCOGNITO(0);	}

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

		else if(!strcmp(INPUT,"_SWITCH_USER"))
		{	CALL_SWITCH_USER();	}

      else if(!strcmp(INPUT,"_ENCRYPT"))
      {	CALL_ENCRYPT();	}

      else if(!strcmp(INPUT,"_DECRYPT"))
      {	CALL_DECRYPT();	}

      else if(!strcmp(INPUT,"_CONSOLE"))
      {	CALL_CONSOLE();	}

      else if(!strcmp(INPUT,"_COLOR"))
      {	CALL_COLOR();	}

      else if(!strcmp(INPUT,"_REFRESH"))
      {	CALL_REFRESH();	}

		// WRITE OTHER COMMANDS IN else if STATEMENT ONLY! OTHERWISE THEY WILL
		// BE WRITTEN INTO THE FILE

		else
		{
			if(INIT==1)
			{
         	REGISTRY << INPUT << endl;
         }
		}
}

int main()
{
	login();
	CALL_CLR();

	HISTORY << endl << "\t[STARTED BY: " << USER << "]\n";
	cout << "DevR - Development Redefined | version " << version << endl
		  << "Copyright (c) Feb 2013 - Sep 2013 | Naveen Venkat" << endl;
	cout << "Type _HELP for help.";
   cout << endl;
   for(int i=1; i<=CONSOLE_WIDTH; i++)
   {
     	cout << '-';
   }
	cout << endl;

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
   
   CALL_REFRESH();
   system("color 07");
	return(0);
}

void CALL_INIT()
{

	if(INIT==1)
	{
		cout << "*ERROR* Please close the current file before initialising a new file!\a";
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
	CALL_CLR();
	cout << "_INIT: Initialise a file (write data into it)." << endl;
	cout << "_CLOSE: Close an initialised file." << endl;
	cout << "_OPEN: Open a file to read data from it." << endl;
	cout << "_COPY: Copy a file into another file." << endl;
	cout << "_DELETE: Delete a file (clear all the data written in it)." << endl;
   cout << "_ENCRYPT: Encrypt a file." << endl;
   cout << "_DECRYPT: Decrypt an encrypted file." << endl;
	cout << "_CLR: Clear the screen." << endl;
   cout << "_REFRESH: Refresh the console." << endl;
	cout << "_INCOGNITO_1: Enable INCOGNITO mode (nothing will be saved in history)." << endl;
	cout << "_INCOGNITO_0: Disable INCOGNITO mode." << endl;
   cout << "_CONSOLE: View Console related commands (Color, About, Updates)." << endl;
	cout << "_SWITCH_USER: Change the current user." << endl;
	cout << "_HELP: Display this help screen." << endl;
	cout << "_EXIT: Exit devr." << endl << endl;
	cout << "DevR version " << version << "\nCreated and Developed by Naveen Venkat\nWebsite: www.devr.webs.com\nEmail: nmakes@outlook.com\n\n";
}

void CALL_OPEN()
{

	if(INIT==1)
	{
		cout << "*ERROR* Please close the current file before opening a new file!\a";
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
		else if(corecheck(INPUT)&&(strcmp(USER,"_DEBUG")))
		{
			cout << "*ERROR* Protected Command!\a";
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
				CALL_CLR();
				while(REGISTRY.eof()!=1)
				{
					char ch;
					REGISTRY.get(ch);
					cout << ch;
				}
            cout << endl;
            for(int i=1; i<=CONSOLE_WIDTH; i++)
            {
            	cout << '-';
            }
				cout << endl;
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
		cout << "*ERROR* Please close the current file before deleting a file!\a" << endl;
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
	CALL_CLR();
	cout << "\n   devr " << version;
	cout << "\n   Created and Developed by Naveen Venkat";
	cout << "\n   nmakes@outlook.com";
	cout << "\n\n\n\n\n\n\n\n\n\t\t\tLOGIN USERNAME: ";
	gets(USER);
}

void CALL_INCOGNITO(int x)
{
	if(x)
	{
   	if(INCOGNITO==1)
      {
      	cout << "*ERROR* INCOGNITO MODE is already activated!\a" << endl;
      }
      else
      {
			INCOGNITO=1;
			cout << "\n- INCOGNITO MODE ACTIVATED. \n- Text and commands that you type WILL NOT BE saved anywhere in the history.";
			cout << "\n- However, it will not affect the files that you edit.";
			cout << "\n- Be wary of:";
			cout << "\n\tMalicious software that tracks your keystrokes";
			cout << "\n\tSurveillance by secret agents";
			cout << "\n\tPeople standing behind you\n\n";
      }
	}
	else
	{
		INCOGNITO=0;
		cout << "\n- INCOGNITO MODE OFF." << endl;
		cout << "- Text and commands that you type WILL BE saved in the history.\n\n";
	}
}

void CALL_COPY()
{
	fstream TEMPFILE; char RAM[128];

	if(INIT==1)
	{
		cout << "*ERROR* Please close the current file before copying a file!\a";
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
	cout << "\n*RAM INFO*" << endl;
	cout << "- [" << sizeof(version) << "B] version: " << version;
	cout << "\n- [" << sizeof(INPUT) << "B] INPUT: " << INPUT;
	cout << "\n- [" << sizeof(USER) << "B] USER: " << USER;
	cout << "\n- [" << sizeof(INIT) << "B] INIT: " << INIT;
	cout << "\n- [" << sizeof(INCOGNITO) << "B] INCOGNITO: " << INCOGNITO;
   cout << "\n- [" << sizeof(CONSOLE_COLOR) << "B] CONSOLE_COLOR: " << CONSOLE_COLOR;
	cout << endl << endl << "\a";
}

int CALL_UNINSTALL_DEVR()
{
	char ch;
	cout << "\n- ARE YOU SURE TO UNINSTALL DEVR? (Y/N): ";
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
		cout << endl << endl;
      cout << "You can continue working. When you want to stop type _EXIT";
      cout << endl;
	}
	return(0);
}

void core(char a[])
{
	if(!INCOGNITO)
	{
		HISTORY << "[" << INIT << "] " << a << endl;;
	}
	else
	{
		HISTORY << "[" << INIT << "] " << "<{[INCOGNITO]}>" << endl;
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

void CALL_SWITCH_USER()
{
	char *RAM = new char[32];
	cout << "- Enter the new user name: ";
	strcpy(RAM,USER);
   gets(USER);
   core(USER);
   cout << "- User successfully changed from '" << RAM << "' to '" << USER << "'" << endl;
}

void CALL_ENCRYPT()
{
	if(INIT==1)
	{
		cout << "*ERROR* Please close the current file before encrypting a file!\a";
		cout << endl;
	}
	else if(INIT==0)
	{
		cout << "- Enter the path of the file to encrypt: ";
		gets(INPUT);
		core(INPUT);

		if(!strcmp(INPUT,""))
		{
			cout << "*ERROR* Please enter a valid file path!\a";
			cout << endl;
		}
		else if(corecheck(INPUT)&&(strcmp(USER,"_DEBUG")))
		{
			cout << "*ERROR* Protected Command!\a";
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
         	char LOC[128];
            cout << "- Enter the path to save the encrypted file: ";
            gets(LOC);
            core(LOC);

         	ofstream TEMPexh(LOC, fstream::binary);

            if (TEMPexh.bad())
            {
            	cout << "*ERROR* The path does not exist!\a" << endl;
               TEMPexh.close();
            }
            else
            {
            	int l=0;
            	struct EXPRESS
	            {
	               int no;
	            	char ch;
	            } XT;

               while(REGISTRY.eof()!=1)
					{
	            	REGISTRY.get(XT.ch);

                  if (REGISTRY.eof()==0)
                  {
	                  randomize();
			            XT.no = random(64);
							XT.ch = XT.ch + XT.no;
			            TEMPexh.write((char*)&XT, sizeof(XT));
	      	         l++;
                  }
	            }

	            TEMPexh.close();
               cout << "- Encrypted successfully! " << l << " bytes of information translated!" << endl;
	        	}

      	}

         REGISTRY.close(); INIT = 0;
		}
	}
}

void CALL_DECRYPT()
{
	if(INIT==1)
	{
		cout << "*ERROR* Please close the current file before decrypting a file!\a";
		cout << endl;
	}
	else if(INIT==0)
	{
		cout << "- Enter the path of the file to decrypt: ";
		gets(INPUT);
		core(INPUT);

		if(!strcmp(INPUT,""))
		{
			cout << "*ERROR* Please enter a valid file path!\a";
			cout << endl;
		}
		else if(corecheck(INPUT)&&(strcmp(USER,"_DEBUG")))
		{
			cout << "*ERROR* Protected Command!\a";
			cout << endl;
		}
		else
		{
			REGISTRY.open(INPUT,fstream::in|fstream::binary);
			INIT = 1;

			if(!REGISTRY.good())
			{
				cout << "*ERROR* The file does not exist!\a" << endl;
			}
			else
			{
         	char LOC[128];
            cout << "- Enter the path to save the decrypted file: ";
            gets(LOC);
            core(LOC);

         	ofstream TEMPexh(LOC);

            if (TEMPexh.bad())
            {
            	cout << "*ERROR* The path does not exist!\a" << endl;
               TEMPexh.close();
            }
            else
            {
            	int l;

            	struct EXPRESS
	            {
	               int no;
	            	char ch;
	            } XT;

	            randomize();

					while(REGISTRY.eof()!=1)
					{
	            	REGISTRY.read((char*)&XT, sizeof(XT));

                  if(REGISTRY.eof()==0)
                  {
							XT.ch = XT.ch - XT.no;
	                  TEMPexh.put(XT.ch);
	                  l++;
                  }
	            }

	            TEMPexh.close();
               cout << "- Decrypted successfully! " << l << " bytes of information translated!" << endl;
	        	}

			   REGISTRY.close(); INIT = 0;
      	}
		}
	}
}

void CALL_CLR()
{
	clrscr();
   system(CONSOLE_COLOR);
}

void CALL_CONSOLE()
{
	cout << "\n";
	cout << "- SELECT A COLOR SCHEME FOR THE CONSOLE (_COLOR)." << endl;
   cout << "- SHOW THE CURRENT RAM USAGE (_MEMORY)." << endl;
   cout << "- KNOW ABOUT DEVR CONSOLE (_ABOUT)." << endl;
   cout << "- UPDATE (_UPDATE)." << endl;
   cout << "- UNINSTALL DEVR - say goodbye forever (_UNINSTALL_DEVR)." << endl << endl;
}


void CALL_COLOR()
{

	cout << endl;
	char TEMPest[3]; int flag=0;
   cout << "- Enter a combination of two charecters." << endl;
   cout << "- The first charecter: Background color." << endl;
   cout << "- The second charecter: Text color." << endl;
	cout << "\n\t0 = Black\t\t8 = Gray";
   cout << "\n\t1 = Blue\t\t9 = Light Blue";
   cout << "\n\t2 = Green\t\tA = Light Green";
   cout << "\n\t3 = Aqua\t\tB = Light Aqua";
   cout << "\n\t4 = Red\t\t\tC = Light Red";
   cout << "\n\t5 = Purple\t\tD = Light Purple";
   cout << "\n\t6 = Yellow\t\tE = Light Yellow";
   cout << "\n\t7 = White\t\tF = Bright White";
   cout << "\n\nFor example, the blue-white combination is 1F";
   cout << endl << endl << "Enter a combination: ";
   gets(TEMPest);
   core(TEMPest);

	if( isdigit(TEMPest[0]) || (TEMPest[0]>='A'&&TEMPest[0]<='F') || (TEMPest[0]>='a'&&TEMPest[0]>='f') )
   {
   	CONSOLE_COLOR[6] = TEMPest[0];
      flag=1;
   }
   else
   {
      flag=0;
   }

   if( isdigit(TEMPest[1]) || (TEMPest[1]>='A'&&TEMPest[1]<='F') || (TEMPest[0]>='a'&&TEMPest[0]>='f') )
   {
   	CONSOLE_COLOR[7] = TEMPest[1];
      flag=1;
   }
   else
   {
		flag=0;
   }

   if(flag==1)
   {
   	cout << "\n- Press any key to change the color... ";
      getch();
		CALL_CLR();
   }
   else
   {
   	cout << "*ERROR* Please enter a valid combination ranging from 0-9 and A-F!\a" << endl;
   }
}

void CALL_REFRESH()
{
	gotoxy(1,1);
   for(int i=1; i<=24000; i++)
   {
   	cout << ' ';
   }
   gotoxy(1,1);
   CALL_CLR();
}

